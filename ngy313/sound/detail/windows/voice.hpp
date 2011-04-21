#ifndef NGY313_SOUND_DETAIL_WINDOWS_VOICE_HPP_
#define NGY313_SOUND_DETAIL_WINDOWS_VOICE_HPP_
#include <cassert>
#include <boost/noncopyable.hpp>
#include <ngy313/sound/detail/sound_device.hpp>

namespace ngy313 { namespace sound { namespace detail {
template <typename Loader>
class voice : private boost::noncopyable {
 public:
  voice(const device_handle &xaudio, const Loader &loader)
      : buffer_(loader), voice_(detail::create_source_voice(xaudio, loader.format())) {
    init();
  }
/*
  sound(const Loader &loader, const submix &mix)
      : buffer_(loader),
        voice_(detail::create_source_voice(detail::device().device(), buffer_.format(), mix.submix_voice())) {
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
    const XAUDIO2_BUFFER buffer = {XAUDIO2_END_OF_STREAM, buffer_.size(), &(*buffer_.buffer()), 0, 0, 0, 0, 0, nullptr};
    voice_->SubmitSourceBuffer(&buffer);
  }

  const Loader buffer_;
  const source_voice_handle voice_;
};
}}}

#endif

