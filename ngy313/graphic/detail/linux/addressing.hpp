#ifndef NGY313_GRAPHIC_DETAIL_LINUX_ADDRESSING_HPP_
#define NGY313_GRAPHIC_DETAIL_LINUX_ADDRESSING_HPP_
#include <cstdint>
#include <ngy313/graphic/detail/linux/addressing_type.hpp>

namespace ngy313 { namespace graphic { namespace detail {
inline 
void set_addressing_mode(const std::uint32_t stage, const addressing_type u, const addressing_type v) {
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, u);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, v);
}

template <typename AddressingTuple>
void set_addressing_tuple() {
  set_addressing_mode(AddressingTuple::stage_type::value,
                      AddressingTuple::u_type::value, 
                      AddressingTuple::v_type::value);
}
}}}

#endif

