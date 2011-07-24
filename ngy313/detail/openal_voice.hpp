#ifndef NGY313_DETAIL_OPENAL_VOICE_HPP_
#define NGY313_DETAIL_OPENAL_VOICE_HPP_

#include <cassert>
#include <memory>
#include <boost/noncopyable.hpp>
#include <ngy313/sound_format.hpp>

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
}}

#endif

