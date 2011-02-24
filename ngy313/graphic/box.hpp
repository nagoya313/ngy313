#pragma once
#include <ngy313/graphic/drawable.hpp>
#include <ngy313/graphic/fvf_tag.hpp>
#include <ngy313/graphic/primitive_tag.hpp>
#include <ngy313/utility/if_cc.hpp>

namespace ngy313 { namespace graphic {
#pragma warning(disable: 4512)

// ˆø”‚ªƒxƒNƒgƒ‹‚É‚È‚é‚Ì‚Í{}‚Å‰Šú‰»‚Å‚«‚é‚æ‚¤‚É‚È‚Á‚Ä‚©‚ç
template <bool Filled>
class box_base : public drawable<box_base<Filled>, 
                                 utility::if_cc<Filled, std::size_t, 4, 5>::value,
                                 utility::if_cc<Filled, std::uint32_t, 2, 4>::value,
                                 shape_2d_fvf_tag, 
                                 typename boost::mpl::if_c<Filled,
                                                           triangle_strip_primitive_tag,
                                                           line_strip_primitive_tag>::type> {
 public:
  box_base(const float x, const float y, const float width, const float height)
      : vertex_(init_vertex<Filled>(x, y, width, height)) {}

 private:
  vertex_array_type vertex() const {
    return vertex_;
  }

  template <bool Fill>
  static vertex_array_type init_vertex(const float x,
                                       const float y,
                                       const float width, 
                                       const float height,
                                       typename std::enable_if<Fill>::type * = nullptr) {
    const vertex_array_type vertex = {{
      {{x, y, 0.f, 1.f}, 0xFFFFFFFF},
      {{x + width, y, 0.f, 1.f}, 0xFFFFFFFF},
      {{x, y + height, 0.f, 1.f}, 0xFFFFFFFF},
      {{x + width, y + height, 0.f, 1.f}, 0xFFFFFFFF}
    }};
    return vertex;
  }

  template <bool Fill>
  static vertex_array_type init_vertex(const float x,
                                       const float y, 
                                       const float width,
                                       const float height,
                                       typename std::enable_if<!Fill>::type * = nullptr) {
    const vertex_array_type vertex = {{
      {{x, y, 0.f, 1.f}, 0xFFFFFFFF},
      {{x + width, y, 0.f, 1.f}, 0xFFFFFFFF},
      {{x + width, y + height, 0.f, 1.f}, 0xFFFFFFFF},
      {{x, y + height, 0.f, 1.f}, 0xFFFFFFFF},
      {{x, y, 0.f, 1.f}, 0xFFFFFFFF}
    }};
    return vertex;
  }

  const vertex_array_type vertex_;

  friend class drawable_access;
};

#pragma warning(default: 4512)

typedef box_base<true> box;
typedef box_base<false> line_box;
}}
