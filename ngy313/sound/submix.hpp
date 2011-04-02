#pragma once
#include <cassert>
#include <cstdint>
#include <ngy313/sound/detail/device.hpp>
#include <ngy313/sound/detail/singleton.hpp>

namespace ngy313 { namespace sound {
class submix {
 public:
  submix(const std::uint32_t channels, const std::uint32_t sample_rate)
    : submix_voice_(detail::create_submix_voice(detail::device().device(), channels, sample_rate)) {}

  void set_volume(const float volume) {
    assert(submix_voice_);
    submix_voice_->SetVolume(volume);
  }

  float volume() const {
    assert(submix_voice_);
    float vol;
    submix_voice_->GetVolume(&vol);
    return vol;
  }

 private:
  const detail::submix_voice_handle &submix_voice() const {
    return submix_voice_;
  }

  const detail::submix_voice_handle submix_voice_;

  template <typename BufferType>
  friend class sound;
};
}}
