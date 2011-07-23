#ifndef NGY313_DETAIL_XAUDIO2_VOICE_HPP_
#define NGY313_DETAIL_XAUDIO2_VOICE_HPP_

#include <cassert>
#include <memory>
#include <boost/noncopyable.hpp>
#include <ngy313/sound_format.hpp>

namespace ngy313 { namespace detail {
struct source_voice_delete {
  void operator ()(IXAudio2SourceVoice *voice) const {
    assert(voice);
    voice->Stop();
    voice->DestroyVoice();
  }
};

typedef std::unique_ptr<IXAudio2SourceVoice, source_voice_delete> 
    source_voice_handle;

inline
WAVEFORMATEX transform_format(const buffer_format &format) {
  const WAVEFORMATEX format_ex = {
    format.type, 
    format.channels,
    format.samples_per_sec,
    format.avg_bytes_per_sec,
    format.block_align,
    format.bits_per_sample,
    0
  };
  return format_ex;
}

template <typename Device>
source_voice_handle create_source_voice(const Device &xaudio, const buffer_format &format) {
  assert(xaudio);
  IXAudio2SourceVoice *voice;
  const WAVEFORMATEX format_ex = transform_format(format);
  if (FAILED(xaudio->CreateSourceVoice(&voice, &format_ex))) {
    throw std::runtime_error("ソースボイスの作成に失敗しました");
  }
  return source_voice_handle(voice);
}

template <typename Loader>
class xaudio2_voice : boost::noncopyable {
 public:
  template <typename Device, typename Load>
  explicit xaudio2_voice(const Device &device, Load &&loader)
      : loader_(std::forward<Load>(loader)), 
        voice_(create_source_voice(device.context(), loader_.format())) {
    init();
  }

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

 private:
  void init() {
    assert(voice_);
    const XAUDIO2_BUFFER buffer = {
      XAUDIO2_END_OF_STREAM,
      loader_.size(),
      &(*loader_.buffer()), 
      0,
      0,
      0,
      0,
      0,
      nullptr
    };
    voice_->SubmitSourceBuffer(&buffer);
  }

  Loader loader_;
  source_voice_handle voice_;
};
}}

#endif

