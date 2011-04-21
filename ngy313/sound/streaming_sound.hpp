#ifndef NGY313_SOUND_STREAMING_SOUND_HPP_
#define NGY313_SOUND_STREAMING_SOUND_HPP_
#include <boost/noncopyable.hpp>
#include <ngy313/sound/detail/sound_device.hpp>
#include <ngy313/sound/detail/streaming_voice.hpp>

namespace ngy313 { namespace sound {
template <typename Loader>
class streaming_sound : private boost::noncopyable {
 public:
  explicit streaming_sound(Loader &loader) : voice_(loader) {}

/*
  streaming_sound(const Loader &loader, const submix &mix) : buffer_(file_name), voice_() {
    voice_ = detail::create_source_voice(detail::device().device(), buffer_.format(), mix.submix_voice(), this);
    init();
  }*/

  void start() {
    voice_.start();
  }

  void pause() {
    voice_.pause();
  }

  void stop() {
    voice_.stop();
  }

  void set_volume(const float volume) {
    voice_.set_volume(volume);
  }

  float volume() const {
    return voice_.set_volume();
  }

  template <typename Effect>
  void set_effect(const Effect &effect) {
    voice_.set_effect(effect);
  }

 private:
  detail::streaming_voice<Loader> voice_;
};
}}

#endif
