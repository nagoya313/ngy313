#ifndef NGY313_SOUND_DETAIL_VOICE_HPP_
#define NGY313_SOUND_DETAIL_VOICE_HPP_
#include <ngy313/platform.hpp>
#if defined(NGY313_WINDOWS_VERSION)
#include <ngy313/sound/detail/windows/voice.hpp>
#elif defined(NGY313_LINUX_VERSION)
#include <ngy313/sound/detail/linux/voice.hpp>
#endif

#endif

