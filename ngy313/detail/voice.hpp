#ifndef NGY313_DETAIL_VOICE_HPP_
#define NGY313_DETAIL_VOICE_HPP_

#include <utility>
#include <boost/noncopyable.hpp>

#if defined(_WIN32)
#include <ngy313/detail/xaudio2_voice.hpp>
#elif defined(__linux__)
#include <ngy313/detail/openal_voice.hpp>
#endif

namespace ngy313 { namespace detail {
template <typename Voice, typename Loader>
class basic_voice : boost::noncopyable {
 public:
  template <typename Device, typename Load>
  explicit basic_voice(const Device &device, Load &&loader)
      : voice_(device, std::forward<Load>(loader)) {}

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
    voice_.setVolume(volume);
  }

  float volume() const {
    return voice_.volume();
  }

 private:
  Voice voice_;
};

#if defined(_WIN32)
template <typename Loader>
struct voice {
  typedef basic_voice<xaudio2_voice<Loader>, Loader> type;
};
#elif defined(__linux__)
template <typename Loader>
struct voice {
  typedef basic_voice<openal_voice<Loader>, Loader> type;
};

template <typename Loader>
struct streaming_voice {
  typedef basic_voice<openal_streaming_voice<Loader>, Loader> type;
};
#endif
}}

#endif

