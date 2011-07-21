#ifndef NGY313_DETAIL_XAUDIO2_SOUND_SYSTEM_HPP_
#define NGY313_DETAIL_XAUDIO2_SOUND_SYSTEM_HPP_

#include <cassert>
#include <memory>
#include <stdexcept>
#include <boost/noncopyable.hpp>
#include <XAudio2.h>
#include <ngy313/detail/com.hpp>

namespace ngy313 { namespace detail {
class xaudio2_sound_system : boost::noncopyable {
  struct master_voice_delete {
    void operator ()(IXAudio2MasteringVoice * const voice) const {
      assert(voice);
      voice->DestroyVoice();
    }
  };

  typedef std::unique_ptr<IXAudio2, com_delete> device_handle;
  typedef std::unique_ptr<IXAudio2MasteringVoice, 
                          master_voice_delete> master_voice_handle;

 public:
  xaudio2_sound_system() : device_(create_device()),
                           voice_(create_master_voice(device_)) {}

 private:
  static device_handle create_device() {
#ifdef NDEBUG
    const std::uint32_t flag = 0;
#else
    const std::uint32_t flag = XAUDIO2_DEBUG_ENGINE;
#endif
    IXAudio2 *xaudio;
    if (FAILED(XAudio2Create(&xaudio, flag))) {
      throw std::runtime_error("XAudio2の初期化に失敗しました");
    }
    return device_handle(xaudio);
  }

  static master_voice_handle 
      create_master_voice(const device_handle &xaudio) {
    assert(xaudio);
    IXAudio2MasteringVoice *mastering_voice;
    if (FAILED(xaudio->CreateMasteringVoice(&mastering_voice))) {
      throw std::runtime_error("マスターボイスの作成に失敗しました");
    }
    return master_voice_handle(mastering_voice);
  }

  device_handle device_;
  master_voice_handle voice_;
};
}}

#endif
