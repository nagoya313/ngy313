#ifndef NGY313_SOUND_DETAIL_LINUX_STREAMING_VOICE_HPP_
#define NGY313_SOUND_DETAIL_LINUX_STREAMING_VOICE_HPP_
#include <cassert>
#include <boost/range/algorithm/for_each.hpp>
#include <boost/noncopyable.hpp>
#include <boost/thread.hpp>
#include <ngy313/process/process.hpp>
#include <ngy313/sound/detail/sound_device.hpp>

namespace ngy313 { namespace sound { namespace detail {
template <typename Loader>
class streaming_voice : private boost::noncopyable {
 public:
  explicit streaming_voice(Loader &loader)
     : end_flag_(false), playing_(false), loader_(loader), voice_(), buffer_(), thread_([this] {this->run();}) {
    alGenSources(1, &voice_);
    alGenBuffers(32, buffer_);
    boost::for_each(buffer_, [this](const ALuint buffer) {
      this->read(buffer);
    });
    alSourceQueueBuffers(voice_, 32, buffer_);
  }
  
  ~streaming_voice() {
    end_flag_ = true;
    thread_.join();
    alSourceStop(voice_);
    alDeleteSources(1, &voice_);
    alDeleteBuffers(32, buffer_);
  }

  void start() {
    playing_ = true;
    alSourcePlay(voice_);
  }

  void pause() {
    playing_ = false;
    alSourcePause(voice_);
  }

  void stop() {
    playing_ = false;
    alSourceStop(voice_);
    loader_.reset();
  }

  void set_volume(const float volume) {
    alSourcef(voice_, AL_GAIN, volume);
  }

  float volume() const {
    float vol;
    alGetSourcef(voice_, AL_GAIN, &vol);
    return vol;
  }

  template <typename Effect>
  void set_effect(const Effect &effect) {
  }

 private:
  void read(const ALuint buffer) {
    assert(buffer);
    loader_.start();
    const auto format_data = loader_.format();
    ALenum format;
    if (format_data.channels ==  1) {
      format = format_data.bits_per_sample == 8 ? AL_FORMAT_MONO8 : AL_FORMAT_MONO16;
    } else {
      format = format_data.bits_per_sample == 8 ? AL_FORMAT_STEREO8 : AL_FORMAT_STEREO16;
     }
    alBufferData(buffer, format, &(*loader_.buffer()), loader_.size(), format_data.samples_per_sec);
  }
  
  void run() {
    for (;;) {
      if (end_flag_) {
        break;
      }
     if (playing_) {
       int processed;
       alGetSourcei(voice_, AL_BUFFERS_PROCESSED, &processed);
       while(processed--) {
         ALuint buffer;
         alSourceUnqueueBuffers(voice_, 1, &buffer);
         read(buffer);
         alSourceQueueBuffers(voice_, 1, &buffer);
        }
      }
     process::sleep(1);
    }
  }
  
  volatile bool end_flag_;
  volatile bool playing_;
  Loader &loader_;
  ALuint voice_;
  ALuint buffer_[32];
  boost::thread thread_;
};
}}}

#endif
