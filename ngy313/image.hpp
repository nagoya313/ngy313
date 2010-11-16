#pragma once
#include <cassert>
#include "detail/string_piece.hpp"
#include "detail/drawable_core_access.hpp"
#include "detail/image_base.hpp"
#include "drawable_base.hpp"

namespace ngy313 {
class image
    : public detail::image_base<image>, 
      public drawable_base<image, 
                           4, 
                           2,
                           image_2d_fvf_tag,
                           triangle_strip_primitive_tag> {
 public:
  explicit image(const string_piece &file_name)
      : detail::image_base<image>(file_name), drawable_base(init_vertex()) {}

 private:
  friend detail::drawable_core_access;

  void set_texture(const detail::graphic_device_handle &graphic_device) const {
    assert(graphic_device);
    graphic_device->SetTexture(0, texture_.get().texture.get());
    graphic_device->SetTexture(1, nullptr);
  }

  vertex_array_type init_vertex() const {
    const vertex_array_type vertex = {{
      {{0.f, 0.f, 0.f, 1.f}, 0xFFFFFFFF, {0.f, 0.f}},
      {{texture_.get().width, 0.f, 0.f, 1.f}, 0xFFFFFFFF, {1.f, 0.f}},
      {{0.f, texture_.get().height, 0.f, 1.f}, 0xFFFFFFFF, {0.f, 1.f}},
      {{texture_.get().width, texture_.get().height, 0.f, 1.f},
       0xFFFFFFFF, {1.f, 1.f}}
    }};
    return vertex;
  }
};
} 