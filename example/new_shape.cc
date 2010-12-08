#include <boost/range/algorithm/for_each.hpp>
#include <ngy313/process.hpp>
#include <ngy313/window.hpp>
#include <ngy313/graphic.hpp>
#include <ngy313/color_code.hpp>
#include <ngy313/drawable_base.hpp>

using namespace boost;
using namespace ngy313;

class square : public drawable_base<square, 4, 2, shape_2d_fvf_tag, triangle_strip_primitive_tag> {
 public:
  square(const vector2 &pos, const float size)
      : drawable_base(init_vertex(pos, size)) {}

 private:
  static vertex_array_type init_vertex(const vector2 &pos, const float size) {
    const vertex_array_type vertex = {{
      {{pos, 0.f, 1.f}, 0xFFFFFFFF},
      {{vector2(pos.x() + size, pos.y()), 0.f, 1.f}, 0xFFFFFFFF},
      {{vector2(pos.x(), pos.y() + size), 0.f, 1.f}, 0xFFFFFFFF},
      {{pos + vector2(size, size), 0.f, 1.f}, 0xFFFFFFFF}
    }};
    return vertex;
  }
};

int main() {
  set_window_caption("test_window");
  window_resize(640, 480);
  window_show();
  for_each(process_message(), main_loop([]() {
    {
      const scoped_render render;
      if (render.succeeded()) {
        clear_screen(kBlack);
        draw(square(vector2(0.f, 0.f), 320.f));
      }
    }
    present();
  }));
  return 0;
}