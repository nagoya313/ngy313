#pragma once
#include <XAPOFX.h>
#include <ngy313/sound/detail/device.hpp>
#include <ngy313/sound/effect.hpp>
#include <ngy313/utility/com_delete.hpp>

namespace ngy313 { namespace sound {
detail::unknown_handle create_reverb() {
  IUnknown *reverb;
  CreateFX(__uuidof(FXReverb), &reverb);
  return detail::unknown_handle(reverb);
}

typedef FXREVERB_PARAMETERS reverb_parameters;

struct reverb {
  reverb(const float diffusion, const float room_size) : reverb_(create_reverb()), 
                                                         diffusion_(diffusion), 
                                                         room_size_(room_size) {}

  effect_descriptor descriptor(const std::uint32_t channel) const {
    // ƒ`ƒƒƒ“ƒlƒ‹”‚Ìİ’è‚ğ‚Ç‚¤‚·‚é‚©‚ğl‚¦‚Æ‚­
    const effect_descriptor desc = {
      reverb_.get(),
      TRUE,
      channel
    };
    return desc;
  }

  reverb_parameters parameters() const {
    const reverb_parameters param = {
      diffusion_,
      room_size_
    };
    return param;
  }

 private:
  const float diffusion_;
  const float room_size_;
  detail::unknown_handle reverb_;
};
}}
