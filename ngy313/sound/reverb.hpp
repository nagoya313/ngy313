#pragma once
#include <memory>
#include <XAPOFX.h>
#include <ngy313/adaptor/adaptor.hpp>
#include <ngy313/sound/detail/device.hpp>
#include <ngy313/utility/com_delete.hpp>

namespace ngy313 { namespace sound {
// ���̃|�C���^�̌^���ǂ����ɂ�������ƒ�`���Ă���
std::unique_ptr<IUnknown, utility::com_delete> create_reverb() {
  IUnknown *reverb;
  CreateFX(__uuidof(FXReverb), &reverb);
  return std::unique_ptr<IUnknown, utility::com_delete>(reverb);
}

// ��������B��
typedef XAUDIO2_EFFECT_DESCRIPTOR effect_descriptor;
typedef FXREVERB_PARAMETERS reverb_parameters;

// �p�C�v�Ή���߂邩��
struct reverb : public adaptor::base<reverb> {
  reverb(const float diffusion, const float room_size) : reverb_(create_reverb()), 
                                                         diffusion_(diffusion), 
                                                         room_size_(room_size) {}

  // �p�C�v�Ή���߂�΂����͕s�v
  template <typename Sound>
  void operator ()(Sound &snd) const {
    snd.set_effect(*this);
  }

  effect_descriptor descriptor() const {
    // �`�����l�����̐ݒ���ǂ����邩���l���Ƃ�
    const XAUDIO2_EFFECT_DESCRIPTOR desc = {
      reverb_.get(),
      TRUE,
      2
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
  std::unique_ptr<IUnknown, utility::com_delete> reverb_;
};
}}
