#pragma once
#include <pstade/oven/algorithm.hpp>
#include <pstade/oven/make_range.hpp>
#include <pstade/oven/counting.hpp>
#include <d3dx9math.h>
#include "drawable_adaptor.hpp"

namespace ngy313 {
class oval
    : public drawable_adaptor<oval, 62, 60, make_drawable_tag<dimension2_fvf_tag, 
                                                              diffuse_fvf_tag, 
                                                              triangle_fan_primitive_tag>> {
 public:
  oval(const float x, const float y, const float rx, const float ry)
      : vertex_(init_vertex(x, y, rx, ry)) {}

  vertex_range_type vertex() const {
    return pstade::oven::make_range(vertex_.begin(), vertex_.end());
  }

 private:
  static vertex_array_type init_vertex(const float x, const float y, const float rx, const float ry) {
    vertex_array_type vertex = {{
      {{x, y, 0.f, 1.f}, 0xFFFFFFFF}
    }};
    pstade::oven::transform(pstade::oven::counting(1, vertex.size()), std::next(vertex.begin()), 
                                                   [x, y, rx, ry](const int i) -> vertex_type {
      const float rad = D3DX_PI * 2.f * static_cast<const float>(i - 1) / static_cast<const float>(oval::size_type::value - 2);
      const vertex_type vertex = {
        {x + std::cos(rad) * rx, y + std::sin(rad) * ry, 0.f, 1.f}, 0xFFFFFFFF
      };
      return vertex;
    });
    return vertex;
  }

  const vertex_array_type vertex_;
};
}