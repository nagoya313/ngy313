#ifndef NGY313_SOUND_HPP_
#define NGY313_SOUND_HPP_

#include <cassert>
#include <cstdint>
#include <type_traits>
#include <utility>
#include <boost/noncopyable.hpp>
#include <boost/mpl/contains.hpp>
#include <ngy313/detail/ngy313.hpp>
#include <ngy313/detail/voice.hpp>

namespace ngy313 {
class sound : boost::noncopyable {
 public:              
  template <typename Loader>
  explicit sound(Loader &&loader) 
      : voice_(detail::main_singleton::instance().sound(),
               std::forward<Loader>(loader),
               false) {
    static_assert(boost::mpl::contains<typename std::decay<Loader>::type::play_type,
                                       normal_play_tag>::value, 
                  "Loader does not usually correspond to the reproduction.");
  }
               
  template <typename Loader>
  explicit sound(Loader &&loader, bool loop) 
      : voice_(detail::main_singleton::instance().sound(),
               std::forward<Loader>(loader),
               loop) {
	static_assert(boost::mpl::contains<typename std::decay<Loader>::type::play_type,
                                       normal_play_tag>::value, 
                  "Loader does not usually correspond to the reproduction.");
  }

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
    assert(volume == this->volume());
  }

  float volume() const {
    return voice_.volume();
  }

 private:
  detail::voice voice_;
};

template <typename Loader>
class basic_streaming_sound : boost::noncopyable {
 public:
  static_assert(boost::mpl::contains<typename Loader::play_type,
                                     streaming_play_tag>::value, 
                "Loader does not correspond to the streaming reproduction.");
                
  template <typename Load>
  explicit basic_streaming_sound(Load &&loader) 
      : voice_(detail::main_singleton::instance().sound(),
               std::forward<Load>(loader), false) {}

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
  typename detail::streaming_voice<Loader>::type voice_;
};
}

#endif
