#pragma once
#include <pstade/oven/algorithm.hpp>
#include <pstade/oven/make_range.hpp>
#include <pstade/oven/counting.hpp>
#include <d3dx9math.h>
#include "drawable_adaptor.hpp"

namespace ngy313 {
class line_circle
    : public drawable_adaptor<line_circle, 60, 59, make_drawable_tag<dimension2_fvf_tag, 
                                                                     diffuse_fvf_tag, 
                                                                     line_strip_primitive_tag>> {
 public:
  line_circle(const float x, const float y, const float r)
      : vertex_(init_vertex(x, y, r)) {}

  vertex_range_type vertex() const {
    return pstade::oven::make_range(vertex_.begin(), vertex_.end());
  }

 private:
  static vertex_array_type init_vertex(const float x, const float y, const float r) {
    vertex_array_type vertex;
    pstade::oven::transform(pstade::oven::counting(0, vertex.size()), vertex.begin(),
                            [x, y, r](const int i) -> vertex_type {
      const float rad = D3DX_PI * 2.f * static_cast<float>(i) / static_cast<float>(line_circle::size_type::value - 1);
      const vertex_type vertex = {
        {x + std::cos(rad) * r, y + std::sin(rad) * r, 0.f, 1.f}, 0xFFFFFFFF
      };
      return vertex;
    });
    return vertex;
  }

  const vertex_array_type vertex_;
};
}