#pragma once
#include <cassert>
#include <cstdint>
#include <type_traits>
#include <boost/mpl/at.hpp>
#include <ngy313/graphic/detail/key.hpp>
#include <ngy313/graphic/texture_stage_tag.hpp>
#include <ngy313/graphic/detail/fwd.hpp>
#include <ngy313/utility/com_delete.hpp>
#include <ngy313/utility/intrusive_com_delete.hpp>

namespace ngy313 { namespace graphic { namespace detail {
inline
void set_color_option(const device_handle &device, const std::uint32_t stage, const std::uint32_t op) {
  assert(device);
  device->SetTextureStageState(stage, D3DTSS_COLOROP, op);
}

inline
void set_color_arg1(const device_handle &device, const std::uint32_t stage,  const std::uint32_t op) {
  assert(device);
  device->SetTextureStageState(stage, D3DTSS_COLORARG1, op);
}

inline
void set_color_arg2(const device_handle &device, const std::uint32_t stage,  const std::uint32_t op) {
  assert(device);
  device->SetTextureStageState(stage, D3DTSS_COLORARG2, op);
}

template <typename ColorTuple>
void set_texture_color(const device_handle &device,
                       const std::uint32_t stage,
                       typename std::enable_if<std::is_same<typename ColorTuple::operator_type, 
                                                            disable_texture_operator_tag>::value>::type * = nullptr) {
  assert(device);
  set_color_option(device, stage, ColorTuple::operator_type::value);
}

template <typename ColorTuple>
void set_texture_color(const device_handle &device,
                       const std::uint32_t stage,
                       typename std::enable_if<std::is_same<typename ColorTuple::operator_type, 
                                                            arg1_texture_operator_tag>::value>::type * = nullptr) {
  assert(device);
  set_color_arg1(device, stage, ColorTuple::arg1_type::value);
  set_color_option(device, stage, ColorTuple::operator_type::value);
}

template <typename ColorTuple>
void set_texture_color(const device_handle &device,
                       const std::uint32_t stage,
                       typename std::enable_if<!std::is_same<typename ColorTuple::operator_type, 
                                                             arg1_texture_operator_tag>::value &&
                                               !std::is_same<typename ColorTuple::operator_type, 
                                                             disable_texture_operator_tag>::value>::type * = nullptr) {
  assert(device);
  set_color_arg1(device, stage, ColorTuple::arg1_type::value);
  set_color_option(device, stage, ColorTuple::operator_type::value);
  set_color_arg2(device, stage, ColorTuple::arg2_type::value);
}

inline
void set_alpha_option(const device_handle &device, const std::uint32_t stage, const std::uint32_t op) {
  assert(device);
  device->SetTextureStageState(stage, D3DTSS_ALPHAOP, op);
}

inline
void set_alpha_arg1(const device_handle &device, const std::uint32_t stage, const std::uint32_t op) {
  assert(device);
  device->SetTextureStageState(stage, D3DTSS_ALPHAARG1, op);
}

inline
void set_alpha_arg2(const device_handle &device, const std::uint32_t stage, const std::uint32_t op) {
  assert(device);
  device->SetTextureStageState(stage, D3DTSS_ALPHAARG1, op);
}

template <typename AlphaTuple>
void set_texture_alpha(const device_handle &device,
                       const std::uint32_t stage,
                       typename std::enable_if<std::is_same<typename AlphaTuple::operator_type, 
                                                            disable_texture_operator_tag>::value>::type * = nullptr) {
  assert(device);
  set_alpha_option(device, stage, AlphaTuple::operator_type::value);
}

template <typename AlphaTuple>
void set_texture_alpha(const device_handle &device,
                       const std::uint32_t stage,
                       typename std::enable_if<std::is_same<typename AlphaTuple::operator_type, 
                                                            arg1_texture_operator_tag>::value>::type * = nullptr) {
  assert(device);
  set_alpha_arg1(device, stage, AlphaTuple::arg1_type::value);
  set_alpha_option(device, stage, AlphaTuple::operator_type::value);
}

template <typename AlphaTuple>
void set_texture_alpha(const device_handle &device,
                       const std::uint32_t stage,
                       typename std::enable_if<!std::is_same<typename AlphaTuple::operator_type, 
                                                             arg1_texture_operator_tag>::value &&
                                               !std::is_same<typename AlphaTuple::operator_type, 
                                                             disable_texture_operator_tag>::value>::type * = nullptr) {
  assert(device);
  set_alpha_arg1(device, stage, AlphaTuple::arg1_type::value);
  set_alpha_option(device, stage, AlphaTuple::operator_type::value);
  set_alpha_arg2(device, stage, AlphaTuple::arg2_type::value);
}

template <typename TextureStageTuple>
void set_texture_stage(const device_handle &device,
                       typename boost::enable_if<std::is_same<typename TextureStageTuple::alpha_type, 
                                                              void>>::type * = nullptr) {
  assert(device);
  set_texture_color<typename TextureStageTuple::color_type>(device, TextureStageTuple::stage_type::value);
}

template <typename TextureStageTuple>
void set_texture_stage(const device_handle &device,
                       typename boost::disable_if<std::is_same<typename TextureStageTuple::alpha_type, 
                                                               void>>::type * = nullptr) {
  assert(device);
  set_texture_color<typename TextureStageTuple::color_type>(device, TextureStageTuple::stage_type::value);
  set_texture_alpha<typename TextureStageTuple::alpha_type>(device, TextureStageTuple::stage_type::value);
}

template <typename List, typename T = void>
class scoped_texture_stage {
 public:
  explicit scoped_texture_stage(const device_handle &) {}
};

template <typename List>
class scoped_texture_stage<List, 
                           typename std::enable_if<
                               !std::is_same<typename boost::mpl::at<List, detail::texture_stage_tuple_key>::type,
                                             boost::mpl::void_>::value>::type> {
 public:
  explicit scoped_texture_stage(const device_handle &device) : device_(device) {
    assert(device_);
    set_texture_stage<typename boost::mpl::at<List, detail::texture_stage_tuple_key>::type>(device_);
  }

  ~scoped_texture_stage() {
    assert(device_);
    set_texture_stage<
        boost::mpl::at_c<
            default_stage, 
            typename boost::mpl::at<List, detail::texture_stage_tuple_key>::type::stage_type::value>::type>(device_);
  }

 private:
  const device_handle &device_;
};
}}}
