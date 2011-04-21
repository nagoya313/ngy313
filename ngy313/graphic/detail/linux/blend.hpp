#ifndef NGY313_GRAPHIC_DETAIL_LINUX_BLEND_HPP_
#define NGY313_GRAPHIC_DETAIL_LINUX_BLEND_HPP_
#include <ngy313/graphic/detail/linux/blend_type.hpp>

namespace ngy313 { namespace graphic { namespace detail {
inline
void set_blend_mode(const blend_type src, const blend_type dest) {
  glBlendFunc(src, dest);
}

template <typename BlendPair>
void set_blend_pair() {
  set_blend_mode(BlendPair::src_type::value, BlendPair::dest_type::value);
}
}}}

#endif

