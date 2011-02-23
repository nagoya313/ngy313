#pragma once
#include <ngy313/sound/detail/effect.hpp>

namespace ngy313 { namespace sound {
typedef XAUDIO2_EFFECT_DESCRIPTOR effect_descriptor;

template <typename Effect, typename Parameter>
std::unique_ptr<detail::effect<Effect, Parameter>, detail::xapo_delete> create_effect() {
  detail::effect<Effect, Parameter> * const effect = new Effect();
  if (FAILED(effect->Initialize(nullptr, 0))) {
    throw std::runtime_error("エフェクトの初期化に失敗しました");
  }
  return std::unique_ptr<detail::effect<Effect, Parameter>, detail::xapo_delete>(effect);
}
}}
