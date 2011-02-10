#pragma once
#pragma comment(lib, "XAPOFX.lib")
#include <memory>
#include <XAudio2.h>

namespace ngy313 { namespace utility {
struct com_delete;
}}

namespace ngy313 { namespace sound { namespace detail {
struct master_voice_delete;
struct submix_voice_delete;
struct source_voice_delete;

typedef std::unique_ptr<IXAudio2, utility::com_delete> device_handle;
typedef std::unique_ptr<IXAudio2MasteringVoice, master_voice_delete> master_voice_handle;
typedef std::unique_ptr<IXAudio2SubmixVoice, submix_voice_delete> submix_voice_handle;
typedef std::unique_ptr<IXAudio2SourceVoice, source_voice_delete> source_voice_handle;

typedef IXAudio2VoiceCallback *streaming_callback;
}}}
