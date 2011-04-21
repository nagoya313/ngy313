#ifndef NGY313_SOUND_DETAIL_WINDOWS_VOICE_DELETE_HPP_
#define NGY313_SOUND_DETAIL_WINDOWS_VOICE_DELETE_HPP_
#include <cassert>
#include <XAudio2.h>

namespace ngy313 { namespace sound { namespace detail {
struct master_voice_delete {
  void operator ()(IXAudio2MasteringVoice * const voice) const {
    assert(voice);
    voice->DestroyVoice();
  }
};

struct submix_voice_delete {
  void operator ()(IXAudio2SubmixVoice * const voice) const {
    assert(voice);
    voice->DestroyVoice();
  }
};

struct source_voice_delete {
  void operator ()(IXAudio2SourceVoice * const voice) const {
    assert(voice);
    voice->Stop();
    voice->DestroyVoice();
  }
};
}}}

#endif
