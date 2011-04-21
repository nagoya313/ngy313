#ifndef NGY313_GRAPHIC_TEXTURE_ACCESS_HPP_
#define NGY313_GRAPHIC_TEXTURE_ACCESS_HPP_
#include <type_traits>

namespace ngy313 { namespace graphic { namespace detail {
struct drawable_fusion_initializer;
struct set_texture;
}}}

namespace ngy313 { namespace graphic {
struct texture_tag;
class texture;

class texture_access {
  template <typename Texture>
  static const texture &texture1(const Texture &tex) {
    return tex.texture1();
  }

  friend struct detail::set_texture;
  friend struct detail::drawable_fusion_initializer;
};
}}

#endif
