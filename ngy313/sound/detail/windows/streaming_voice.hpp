#ifndef NGY313_SOUND_DETAIL_WINDOWS_STREAMING_VOICE_HPP_
#define NGY313_SOUND_DETAIL_WINDOWS_STREAMING_VOICE_HPP_
#include <boost/noncopyable.hpp>
#include <ngy313/sound/detail/sound_device.hpp>
#include <ngy313/sound/submix.hpp>
#include <ngy313/sound/detail/streamin_callback.hpp>

namespace ngy313 { namespace sound { namespace detail {
template <typename Loader>
class streaming_voice : private IXAudio2VoiceCallback, private boost::noncopyable {
 public:
  streaming_voice(const device_handle &xaudio, const Loader &loader) : buffer_(loader), voice_() {
    voice_ = create_source_voice(xaudio, buffer_.format(), this);
    init();
  }
/*
  streaming_sound(const Loader &loader, const submix &mix) : buffer_(file_name), voice_() {
    voice_ = detail::create_source_voice(detail::device().device(), buffer_.format(), mix.submix_voice(), this);
    init();
  }*/

  void start() {
    assert(voice_);
    voice_->Start();
  }

  void pause() {
    assert(voice_);
    voice_->Stop();
  }

  void stop() {
    assert(voice_);
    voice_->Stop();
    voice_->FlushSourceBuffers();
    buffer_->reset();
    init();
  }

  void set_volume(const float volume) {
    assert(voice_);
    oice_->SetVolume(volume);
  }

  float volume() const {
    assert(voice_);
    float vol;
    voice_->GetVolume(&vol);
    return vol;
  }

  template <typename Effect>
  void set_effect(const Effect &effect) {
    assert(voice_);
    auto desc = effect.descriptor(buffer_.format().channels);
    const XAUDIO2_EFFECT_CHAIN chain = {1, &desc};
    voice_->SetEffectChain(&chain);
    auto param = effect.parameters();
    voice_->SetEffectParameters(0, &param, sizeof(param));
  }

 private:
  void init() {
    assert(voice_);
    const XAUDIO2_BUFFER buffer = {0, buffer_.size(), &(*buffer_.buffer()), 0, 0, 0, 0, 0, nullptr};
    voice_->SubmitSourceBuffer(&buffer);
  }

  void buufer_start() {
    buffer_.start();
    init();
  }

  void buffer_end() {
    buffer_.end();
  }

  void WINAPI OnStreamEnd() {}

  void WINAPI OnVoiceProcessingPassEnd() {}

  void WINAPI OnVoiceProcessingPassStart(UINT32) {}

  void WINAPI OnBufferEnd(void *) {
    buffer_.end();
  }

  void WINAPI OnBufferStart(void *) {
    buffer_.start();
    init();
  }

  void WINAPI OnLoopEnd(void *) {}

  void WINAPI OnVoiceError(void *, HRESULT) {
    throw std::runtime_error("�X�g���[�~���O�Đ����ɃG���[���������܂���");
  }

  Loader buffer_;
  streaming_callback callback_;
  source_voice_handle voice_;
};
}}}

#endif