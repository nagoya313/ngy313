#pragma once
#include <algorithm>
#include <ngy313/sound/effect.hpp>

namespace ngy313 { namespace sound {
// エフェクト機構のテストなんで実装、インターデイス共にまだ不十分
struct fade_parameters {
  float gain;
  int count;
  int max_count;
};

struct fade_effect : public detail::effect<fade_effect, fade_parameters> {
  void do_process(fade_parameters &param, 
                  float * const data, 
                  const std::uint32_t frame, 
                  const std::uint32_t channel) {
    for (std::uint32_t i = 0; i < frame * channel; ++i) {
      data[i] *= (1.f - param.gain) / param.max_count * param.count;
    }
    param.count = (std::min)(param.count + 1, param.max_count);
  }
};

struct fade {
  fade(const float gain, const int count) : fade_(create_effect<fade_effect, fade_parameters>()), 
                                            gain_(gain), 
                                            count_(0),
                                            max_count_(count) {}

  effect_descriptor descriptor(const std::uint32_t channel) const {
    const XAUDIO2_EFFECT_DESCRIPTOR desc = {
      static_cast<IXAPO *>(fade_.get()),
      TRUE,
      channel
    };
    return desc;
  }

  fade_parameters parameters() const {
    const fade_parameters param = {
      gain_,
      count_,
      max_count_
    };
    return param;
  }

 private:
  const float gain_;
  const int count_;
  const int max_count_;
  const decltype(create_effect<fade_effect, fade_parameters>()) fade_;
};
}}
