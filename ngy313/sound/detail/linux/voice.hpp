#ifndef NGY313_SOUND_DETAIL_LINUX_VOICE_HPP_
#define NGY313_SOUND_DETAIL_LINUX_VOICE_HPP_
#include <cassert>
#include <boost/noncopyable.hpp>
#include <ngy313/sound/format.hpp>
#include <ngy313/sound/detail/sound_device.hpp>

namespace ngy313 { namespace sound { namespace detail {
class source_voice : private boost::noncopyable {
 public:
  template <typename Loader>
  source_voice(const Loader &loader) : voice_(), buffer_() {
    alGenSources(1, &voice_);
    alGenBuffers(1, &buffer_);
    const auto format_data = loader.format();
    ALenum format;
    if (format_data.channels ==  1) {
      format = format_data.bits_per_sample == 8 ? AL_FORMAT_MONO8 : AL_FORMAT_MONO16;
    } else {
      format = format_data.bits_per_sample == 8 ? AL_FORMAT_STEREO8 : AL_FORMAT_STEREO16;
    }
    alBufferData(buffer_, format, &(*loader.buffer()), loader.size(), format_data.samples_per_sec);
    alSourcei(voice_, AL_BUFFER, buffer_);
  }
  
  ~source_voice() {
    alSourceStop(voice_);
    alDeleteSources(1, &voice_);
    alDeleteBuffers(1, &buffer_);
  }
  
  ALuint voice() const {
    return voice_;
  }
 
 private:
  ALuint voice_;
  ALuint buffer_;
};

template <typename Loader>
class voice : private boost::noncopyable {
 public:
  voice(const int device, const Loader &loader) : voice_(loader) {}
  
/*
  sound(const Loader &loader, const submix &mix)
      : buffer_(loader),
        voice_(detail::create_source_voice(detail::device().device(), buffer_.format(), mix.submix_voice())) {
    init();
  }*/

  void start() {
    alSourcePlay(voice_.voice());
  }

  void pause() {
    alSourcePause(voice_.voice());
  }

  void stop() {
    alSourceStop(voice_.voice());
  }

  void set_volume(const float volume) {
    alSourcef(voice_.voice(), AL_GAIN, volume);
  }

  float volume() const {
    float vol;
    alGetSourcef(voice_.voice(), AL_GAIN, &vol);
    return vol;
  }

  template <typename Effect>
  void set_effect(const Effect &effect) {
  }

 private:
  source_voice voice_;
};
}}}

#endif

