#pragma once
#include <cassert>
#include "detail/image_base.hpp"
#include "drawable_base.hpp"

namespace ngy313 {
class image
    : public detail::image_base, 
      public drawable_base<image, 4, 2, image_2d_fvf_tag, triangle_strip_primitive_tag> {
 public:
  explicit image(const string_piece &file_name) : detail::image_base(file_name), drawable_base(init_vertex()) {}

 private:
  vertex_array_type init_vertex() const {
    const vertex_array_type vertex = {{
      {{0.f, 0.f, 0.f, 1.f}, 0xFFFFFFFF, {0.f, 0.f}},
      {{width(), 0.f, 0.f, 1.f}, 0xFFFFFFFF, {1.f, 0.f}},
      {{0.f, height(), 0.f, 1.f}, 0xFFFFFFFF, {0.f, 1.f}},
      {{width(), height(), 0.f, 1.f}, 0xFFFFFFFF, {1.f, 1.f}}
    }};
    return vertex;
  }
};
} 