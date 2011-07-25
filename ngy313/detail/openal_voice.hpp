#ifndef NGY313_DETAIL_OPENAL_VOICE_HPP_
#define NGY313_DETAIL_OPENAL_VOICE_HPP_

#include <cassert>
#include <memory>
#include <atomic>
#include <thread>
#include <boost/noncopyable.hpp>
#include <ngy313/sound_format.hpp>
#include <ngy313/ngy313.hpp>

namespace ngy313 { namespace detail {
struct source_delete {
  void operator ()(const ALuint *source) const {
    assert(source);
    alSourceStop(*source);
    alDeleteSources(1, source);
    delete source;
  }
};

typedef std::unique_ptr<ALuint, source_delete> source_handle;

inline
source_handle create_source() {
  source_handle source(new ALuint());
  alGenSources(1, source.get());
  return source;
}

struct buffer_delete {
  void operator ()(const ALuint *buffer) const {
    assert(buffer);
    alDeleteBuffers(1, buffer);
    delete buffer;
  }
};

typedef std::unique_ptr<ALuint, buffer_delete> buffer_handle;

inline
buffer_handle create_buffer() {
  buffer_handle buffer(new ALuint());
  alGenBuffers(1, buffer.get());
  return buffer;
}

struct buffers_delete {
	explicit buffers_delete(int size) : size_(size) {}

  void operator ()(const ALuint *buffer) const {
    assert(buffer);
    alDeleteBuffers(size_, buffer);
    delete[] buffer;
  }

 private:
  int size_;
};

typedef std::unique_ptr<ALuint[], buffers_delete> buffers_handle;

inline
buffers_handle create_buffers(int size) {
  buffers_handle buffers(new ALuint[size], buffers_delete(size));
  alGenBuffers(size, buffers.get());
  return buffers;
}

class source_voice : boost::noncopyable {
 public:
  template <typename Loader>
  explicit source_voice(const Loader &loader) 
      : buffer_(create_buffer()), source_(create_source()) {
    const auto format_data = loader.format();
    ALenum format;
    if (format_data.channels ==  1) {
      format = format_data.bits_per_sample == 8 ? AL_FORMAT_MONO8 : AL_FORMAT_MONO16;
    } else {
      format = format_data.bits_per_sample == 8 ? AL_FORMAT_STEREO8 : AL_FORMAT_STEREO16;
    }
    alBufferData(*buffer_, format, &(*loader.buffer()), loader.size(), format_data.samples_per_sec);
    alSourcei(*source_, AL_BUFFER, *buffer_);
  }
  
  ALuint voice() const {
    return *source_;
  }
 
 private:
  buffer_handle buffer_;
  source_handle source_;
};

template <typename Loader>
class openal_voice : boost::noncopyable {
 public:
  template <typename Device, typename Load>
  explicit openal_voice(const Device &device, Load &&loader)
      : voice_(std::forward<Load>(loader)) {}

  void start() {
    alSourcePlay(voice_.voice());
  }

  void pause() {
    alSourcePause(voice_.voice());
  }

  void stop() {
    alSourceStop(voice_.voice());
  }

  void set_volume(float volume) {
    alSourcef(voice_.voice(), AL_GAIN, volume);
  }

  float volume() const {
    float vol;
    alGetSourcef(voice_.voice(), AL_GAIN, &vol);
    return vol;
  }

 private:
  source_voice voice_;
};

template <typename Loader>
class streaming_source_voice {
 public:
  template <typename Load>
  explicit streaming_source_voice(Load &&loader)
      : end_flag_(false),
        loader_(std::forward<Load>(loader)),
        buffers_(create_buffers(kBufferSize_)),
        source_(create_source()) {
	for (int i = 0; i < kBufferSize_; ++i) {
   	 read(buffers_[i]);
  	}
  	alSourceQueueBuffers(*source_, kBufferSize_, &buffers_[0]);
  }

  void quit() {
  	end_flag_.store(true, std::memory_order_seq_cst);
  }
  
  void start() {
    alSourcePlay(*source_);
  }

  void pause() {
    alSourcePause(*source_);
  }

  void stop() {
    alSourceStop(*source_);
    loader_.reset();
  }

  void set_volume(float volume) {
    alSourcef(*source_, AL_GAIN, volume);
    assert(volume == this->volume());
  }

  float volume() const {
    float vol;
    alGetSourcef(*source_, AL_GAIN, &vol);
    return vol;
  }

  void run() {
  	for (;;) {
      if (end_flag_.load(std::memory_order_seq_cst)) {
         break;
       }
      ALint state;
      alGetSourcei(*source_, AL_SOURCE_STATE, &state);
      if (state == AL_PLAYING) {
        int processed;
        alGetSourcei(*source_, AL_BUFFERS_PROCESSED, &processed);
        while(processed--) {
          ALuint buffer;
          alSourceUnqueueBuffers(*source_, 1, &buffer);
          read(buffer);
          alSourceQueueBuffers(*source_, 1, &buffer);
         }
       }
      sleep(1);
     }
   }

 private:
  void read(ALuint buffer) {
    assert(buffer);
    loader_.start();
    const auto format_data = loader_.format();
    ALenum format;
    if (format_data.channels ==  1) {
      format = format_data.bits_per_sample == 8 ? AL_FORMAT_MONO8 : AL_FORMAT_MONO16;
    } else {
      format = format_data.bits_per_sample == 8 ? AL_FORMAT_STEREO8 : AL_FORMAT_STEREO16;
     }
    alBufferData(buffer,
    		     format,
     		     &(*loader_.buffer()),
     		     loader_.size(),
     		     format_data.samples_per_sec);
  }

  std::atomic<bool> end_flag_;
  Loader loader_;
  buffers_handle buffers_;
  source_handle source_;
  static constexpr int kBufferSize_ = 32;
};

template <typename Loader>
class openal_streaming_voice : boost::noncopyable {
 public:
	template <typename Device, typename Load>
  explicit openal_streaming_voice(const Device &device, Load &&loader)
      : loader_(std::forward<Load>(loader)),
        thread_(std::bind(&streaming_source_voice<Loader>::run, &loader_)) {}

  ~openal_streaming_voice() {
    loader_.quit();
    thread_.join();
  }

  void start() {
    loader_.start();
  }

  void pause() {
  	loader_.pause();
  }

  void stop() {
  	loader_.stop();
  }

  void set_volume(float volume) {
    loader_.set_volume(volume);
  }

  float volume() const {
    return loader_.volume();
  }

 private:
  streaming_source_voice<Loader> loader_;
  std::thread thread_;
};
}}

#endif

