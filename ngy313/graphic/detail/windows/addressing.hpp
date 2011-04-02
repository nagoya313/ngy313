#ifndef NGY313_GRAPHIC_DETAIL_WINDOWS_ADDRESSING_HPP_
#define NGY313_GRAPHIC_DETAIL_WINDOWS_ADDRESSING_HPP_
#include <cassert>
#include <cstdint>
#include <ngy313/graphic/detail/windows/addressing_type.hpp>
#include <ngy313/graphic/detail/windows/fwd.hpp>
#include <ngy313/utility/detail/windows/com_delete.hpp>

namespace ngy313 { namespace graphic { namespace detail {
inline 
void set_addressing_mode(const device_handle &device, 
                         const std::uint32_t stage,
                         const addressing_type u,
                         const addressing_type v) {
  assert(device);
  device->SetSamplerState(stage, D3DSAMP_ADDRESSU, u);
  device->SetSamplerState(stage, D3DSAMP_ADDRESSV, v);
}

template <typename AddressingTuple>
void set_addressing_tuple(const device_handle &device) {
  assert(device);
  set_addressing_mode(device, 
                      AddressingTuple::stage_type::value,
                      AddressingTuple::u_type::value, 
                      AddressingTuple::v_type::value);
}
}}}

#endif
