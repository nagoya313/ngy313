#pragma once
#include "detail/drawable_core_access.hpp"
#include "detail/texture.hpp"
#include "drawable_base.hpp"
#include "image.hpp"
#include "vector.hpp"

namespace ngy313 {
class texture : public drawable_base<texture, 4, 2, image_2d_fvf_tag, triangle_strip_primitive_tag>,
                public detail::texture_base {
 public:
  texture(const vector2 &pos, const image &img)
      : drawable_base(init_vertex(pos, img)), detail::texture_base(detail::drawable_core_access::texture1(img)) {}

 private:
  static vertex_array_type init_vertex(const vector2 &pos, const image &img) {
    const vertex_array_type vertex = {{
      {{pos, 0.f, 1.f}, 0xFFFFFFFF, vector2(0.f, 0.f)},
      {{vector2(pos.x() + img.width(), pos.y()), 0.f, 1.f}, 0xFFFFFFFF, vector2(1.f, 0.f)},
      {{vector2(pos.x(), pos.y() + img.height()), 0.f, 1.f}, 0xFFFFFFFF, vector2(0.f, 1.f)},
      {{vector2(pos.x() + img.width(), pos.y() + img.height()), 0.f, 1.f}, 0xFFFFFFFF, vector2(1.f, 1.f)}
    }};
    return vertex;
  }
};

/*
class texture3d : public drawable_base<texture3d, 4, 2, image_3d_fvf_tag, triangle_strip_primitive_tag>,
                  public detail::texture_base {
 public:
  texture3d(const vector3 &pos, const image &img)
      : drawable_base(init_vertex(pos, img)), detail::texture_base(detail::drawable_core_access::texture1(img)) {}

 private:
  static vertex_array_type init_vertex(const vector3 &pos, const image &img) {
    const vertex_array_type vertex = {{
      {{pos.x(), pos.y(), 0.f}, 0xFFFFFFFF, {0.f, 0.f}},
      {{pos.x() + img.width(), pos.y(), 0.f}, 0xFFFFFFFF, {1.f, 0.f}},
      {{pos.x(), pos.y() + img.height(), 0.f}, 0xFFFFFFFF, {0.f, 1.f}},
      {{pos.x() + img.width(), pos.y() + img.height(), 0.f}, 0xFFFFFFFF, {1.f, 1.f}}
    }};
    return vertex;
  }
};
*/
} 