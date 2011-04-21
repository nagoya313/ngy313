#ifndef NGY313_GRAPHIC_DETAIL_EXTEND_POSITION_HPP_
#define NGY313_GRAPHIC_DETAIL_EXTEND_POSITION_HPP_
#include <ngy313/graphic/fvf_traits.hpp>
#include <ngy313/graphic/vertex_member.hpp>

namespace ngy313 { namespace graphic { namespace detail {
inline
float extend_position(const float pos, const float base, const float extend) {
  return (pos - base) * extend + base;
}
}}}

#endif
