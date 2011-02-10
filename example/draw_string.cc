#include <ngy313/process/process.hpp>
#include <ngy313/window/window.hpp>
#include <ngy313/graphic/graphic.hpp>
#include <ngy313/graphic/scoped_render.hpp>
#include <ngy313/graphic/font.hpp>
#include <ngy313/graphic/text.hpp>
#include <ngy313/utility/color_code.hpp>

int main() {
  ngy313::window::show();
  const ngy313::graphic::font font(32, "ÇlÇr ÉSÉVÉbÉN");
  return ngy313::process::run([&] {
    {
      const ngy313::graphic::scoped_render render;
      if (render.succeeded()) {
        ngy313::graphic::clear_screen(ngy313::utility::kBlack);
        ngy313::graphic::draw(ngy313::graphic::text(0.f, 0.f, "Hello C++ World!", font));
      }
    }
    ngy313::graphic::present();
  });
}