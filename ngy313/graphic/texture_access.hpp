#pragma once
#include <type_traits>

namespace ngy313 { namespace graphic {
struct texture_tag;
class texture;

class texture_access {
 //private:
 public:
  template <typename Texture>
  static const texture &texture1(const Texture &tex) {
    return tex.texture1();
  }
/*
  template <typename Drawable>
  friend typename std::enable_if<std::is_base_of<texture_tag, Drawable>::value>::type
    set_texture(const detail::device_handle &device, const Drawable &drawable);

  template <typename Drawable>
  friend typename drawable_fusion<Drawable>::type 
    drawable_fusion_init(const Drawable &drawable,
                         typename std::enable_if<drawable_switch<Drawable>::type::value == 2>::type * = nullptr);*/
};
}}
