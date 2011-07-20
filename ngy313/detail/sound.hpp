#ifndef NGY313_DETAIL_SOUND_HPP_
#define NGY313_DETAIL_SOUND_HPP_

#include <boost/noncopyable.hpp>

#if defined(_WIN32)
#include <ngy313/detail/xaudio2_sound_system.hpp>
#elif defined(__linux__)
#include <ngy313/detail/openal_sound_system.hpp>
#endif

namespace ngy313 { namespace detail {
template <typename Sound>
class basic_sound_system : boost::noncopyable {
 public:
  basic_sound_system() : sound_() {}

 private:
  Sound sound_;
};

#if defined(_WIN32)
typedef xaudio2_sound_system sound_system;
#elif defined(__linux__)
typedef openal_sound_system sound_system;
#endif
}}

#endif
