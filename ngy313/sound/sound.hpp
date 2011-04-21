#ifndef NGY313_SOUND_HPP_
#define NGY313_SOUND_HPP_
#include <boost/noncopyable.hpp>
#include <ngy313/sound/detail/sound_device.hpp>
#include <ngy313/sound/detail/voice.hpp>
#include <ngy313/sound/submix.hpp>

namespace ngy313 { namespace sound {
// éÊÇËä∏Ç¶Ç∏ÉRÉsÅ[ÇÕã÷é~
template <typename Loader>
class sound : private boost::noncopyable {
 public:
  explicit sound(const Loader &loader) : voice_(detail::device().device(), loader) {}
  
/*
  sound(const Loader &loader, const submix &mix)
      : buffer_(loader),
        voice_(detail::create_source_voice(detail::device().device(), buffer_.format(), mix.submix_voice())) {
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
  detail::voice<Loader> voice_;
};
}}

#endif
