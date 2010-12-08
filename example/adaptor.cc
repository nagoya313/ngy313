#include <boost/range/algorithm/for_each.hpp>
#include <ngy313/process.hpp>
#include <ngy313/window.hpp>
#include <ngy313/graphic.hpp>
#include <ngy313/color_code.hpp>
#include <ngy313/shape.hpp>
#include <ngy313/moved.hpp>
#include <ngy313/colored.hpp>

using namespace boost;
using namespace ngy313;

int main() {
  set_window_caption("test_window");
  window_resize(640, 480);
  window_show();
  for_each(process_message(), main_loop([]() {
    {
      const scoped_render render;
      if (render.succeeded()) {
        clear_screen(kBlack);
        draw(box(vector2(0.f, 0.f), vector2(320.f, 240.f)) | moved(vector2(320.f, 240.f)) | colored(kRed));
      }
    }
    present();
  }));
  return 0;
}