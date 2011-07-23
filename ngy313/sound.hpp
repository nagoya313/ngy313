#ifndef NGY313_SOUND_HPP_
#define NGY313_SOUND_HPP_

#include <utility>
#include <boost/noncopyable.hpp>
#include <ngy313/detail/ngy313.hpp>
#include <ngy313/detail/voice.hpp>

namespace ngy313 {
template <typename Loader>
class sound : boost::noncopyable {
 public:
  template <typename Load>
  explicit sound(Load &&loader) 
      : voice_(detail::main_singleton::instance().sound(),
               std::forward<Load>(loader)) {}

  void start() {
    voice_.start();
  }

  void pause() {
    voice_.pause();
  }

  void stop() {
    voice_.stop();
  }

  void set_volume(float volume) {
    voice_.set_volume(volume);
  }

  float volume() const {
    return voice_.set_volume();
  }

 private:
  typename detail::voice<Loader>::type voice_;
};
}

#endif
