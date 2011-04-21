#ifndef NGY313_SOUND_DETAIL_WINDOWS_FWD_HPP_
#define NGY313_SOUND_DETAIL_WINDOWS_FWD_HPP_
#include <memory>
#include <XAudio2.h>
#include <ngy313/sound/detail/windows/voice_delete.hpp>
#include <ngy313/utility/detail/windows/com_delete.hpp>

namespace ngy313 { namespace sound { namespace detail {
typedef std::unique_ptr<IUnknown, utility::detail::com_delete> unknown_handle;
typedef std::unique_ptr<IXAudio2, utility::detail::com_delete> device_handle;
typedef std::unique_ptr<IXAudio2MasteringVoice, master_voice_delete> master_voice_handle;
typedef std::unique_ptr<IXAudio2SubmixVoice, submix_voice_delete> submix_voice_handle;
typedef std::unique_ptr<IXAudio2SourceVoice, source_voice_delete> source_voice_handle;

typedef IXAudio2VoiceCallback *streaming_callback;
}}}

#endif
