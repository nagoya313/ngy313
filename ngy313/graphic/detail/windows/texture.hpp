#ifndef NGY313_GRAPHIC_DETAIL_WINDOWS_TEXTURE_HPP_
#define NGY313_GRAPHIC_DETAIL_WINDOWS_TEXTURE_HPP_
#include <cassert>
#include <type_traits>
#include <ngy313/graphic/detail/windows/device.hpp>
#include <ngy313/graphic/detail/graphic.hpp>
#include <ngy313/graphic/fvf_traits.hpp>
#include <ngy313/graphic/texture_access.hpp>
#include <ngy313/graphic/vertex_member.hpp>
#include <ngy313/utility/string_piece.hpp>

namespace ngy313 { namespace graphic {
class texture;
class multi_texture;
class text_image;
class render_target;
}}

namespace ngy313 { namespace graphic { namespace detail {
class texture_core_access {
  template <typename Texture>
  static const texture_handle &texture1(const Texture &tex) {
    return tex.texture1();
  }

  friend struct set_texture;
  friend class graphic::texture;
  friend class graphic::multi_texture;
  friend class graphic::text_image;
  friend class graphic::render_target;
};

struct set_texture {
  template <typename Drawable>
  static typename std::enable_if<std::is_same<tex_t<1>, typename drawable_switch_element<Drawable>::type>::value>::type
      set(const device_handle &device, const Drawable &drawable) {
    assert(device);
    device->SetTexture(0, texture_core_access::texture1(texture_access::texture1(drawable)).get());
  }

  template <typename Drawable>
  static typename std::enable_if<std::is_same<boost::mpl::void_, typename drawable_switch_element<Drawable>::type>::value>::type
      set(const device_handle &device, const Drawable &) {
    assert(device);
    device->SetTexture(0, nullptr);
  }
};
}}}

#endif
