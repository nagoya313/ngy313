#include <ngy313/process/process.hpp>
#include <ngy313/window/window.hpp>
#include <ngy313/graphic/graphic.hpp>
#include <ngy313/graphic/scoped_render.hpp>
#include <ngy313/graphic/pixel.hpp>
#include <ngy313/graphic/colored.hpp>
#include <ngy313/utility/color_code.hpp>

int main() {
  ngy313::window::show();
  return ngy313::process::run([] {
    {
      const ngy313::graphic::scoped_render render;
      if (render.succeeded()) {
        ngy313::graphic::clear_screen(ngy313::utility::kBlack);
        ngy313::graphic::draw(ngy313::graphic::pixel(320.f, 240.f) | 
                              ngy313::graphic::colored(ngy313::utility::kGreen));
      }
    }
    ngy313::graphic::present();
  });
}