#include <ngy313/process/process.hpp>
#include <ngy313/window/window.hpp>
#include <ngy313/graphic/graphic.hpp>
#include <ngy313/graphic/scoped_render.hpp>
#include <ngy313/graphic/drawable.hpp>
#include <ngy313/graphic/fvf_tag.hpp>
#include <ngy313/graphic/primitive_tag.hpp>
#include <ngy313/graphic/colored.hpp>
#include <ngy313/utility/color_code.hpp>

namespace my_shape {
class square : public ngy313::graphic::drawable<square, 
                                                4,
                                                2,
                                                ngy313::graphic::shape_2d_fvf_tag, 
                                                ngy313::graphic::triangle_strip_primitive_tag> {
 public:
  square(const float x, const float y, const float size) : x_(x), y_(y), size_(size) {}

 private:
  vertex_array_type vertex() const {
    const vertex_array_type vertex = {{
      vertex_type(ngy313::graphic::rhw_position_t(x_, y_), ngy313::graphic::diffuse_t(0xFFFFFFFF)),
      vertex_type(ngy313::graphic::rhw_position_t(x_ + size_, y_), ngy313::graphic::diffuse_t(0xFFFFFFFF)),
      vertex_type(ngy313::graphic::rhw_position_t(x_, y_ + size_), ngy313::graphic::diffuse_t(0xFFFFFFFF)),
      vertex_type(ngy313::graphic::rhw_position_t(x_ + size_, y_ + size_), ngy313::graphic::diffuse_t(0xFFFFFFFF))
    }};
    return vertex;
  }

  float x_;
  float y_;
  float size_;

  friend class ngy313::graphic::drawable_access;
};
}

int main() {
  ngy313::window::show();
  return ngy313::process::run([] {
    {
      const ngy313::graphic::scoped_render render;
      if (render.succeeded()) {
        ngy313::graphic::clear_screen(ngy313::utility::kBlack);
        ngy313::graphic::draw(my_shape::square(0.f, 0.f, 480.f) | 
                              ngy313::graphic::colored(ngy313::utility::kBlue));
      }
    }
    ngy313::graphic::present();
  });
}
