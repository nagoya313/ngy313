#pragma once
#include <cassert>
#include <cstdint>
#include <type_traits>
#include <ngy313/graphic/addressing_tag.hpp>
#include <ngy313/graphic/detail/fwd.hpp>
#include <ngy313/utility/com_delete.hpp>
#include <ngy313/utility/intrusive_com_delete.hpp>

namespace ngy313 { namespace graphic { namespace detail {
inline 
void set_addressing_mode(const device_handle &device, 
                         const std::uint32_t stage,
                         const D3DTEXTUREADDRESS u,
                         const D3DTEXTUREADDRESS v) {
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

template <typename AddressingTuple, typename T = void>
class scoped_addressing;

template <typename AddressingTuple>
class scoped_addressing<AddressingTuple, typename std::enable_if<!std::is_same<void, AddressingTuple>::value>::type> {
 public:
  explicit scoped_addressing(const device_handle &device) : device_(device) {
    assert(device_);
    set_addressing_tuple<AddressingTuple>(device_);
  }

  ~scoped_addressing() {
    assert(device_);
    set_blend_pair<default_addressing<AddressingTuple::stage_type::value>::type>(device_);
  }

 private:
  const device_handle &device_;
};

template <typename AddressingTuple>
class scoped_addressing<AddressingTuple, typename std::enable_if<std::is_same<void, AddressingTuple>::value>::type> {
 public:
  explicit scoped_addressing(const device_handle &) {}
};
}}}
