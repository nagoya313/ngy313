#include <boost/range/algorithm/for_each.hpp>
#include <ngy313/process.hpp>
#include <ngy313/window.hpp>
#include <ngy313/graphic.hpp>
#include <ngy313/color_code.hpp>
#include <ngy313/box.hpp>

int main() {
  ngy313::set_window_caption("test_window");
  ngy313::window_resize(640, 480);
  ngy313::window_show();
  boost::for_each(ngy313::process_message(), ngy313::main_loop([]() {
    {
      const ngy313::scoped_render render;
      if (render.succeeded()) {
        ngy313::clear_screen(ngy313::kBlack);
        ngy313::draw(ngy313::box(0.f, 0.f, 320.f, 240.f));
      }
    }
    ngy313::present();
  }));
  return 0;
}