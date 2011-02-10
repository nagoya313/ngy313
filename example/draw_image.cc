#include <ngy313/process/process.hpp>
#include <ngy313/window/window.hpp>
#include <ngy313/graphic/graphic.hpp>
#include <ngy313/graphic/scoped_render.hpp>
#include <ngy313/graphic/image.hpp>
#include <ngy313/graphic/sprite.hpp>
#include <ngy313/utility/color_code.hpp>

int main() {
  ngy313::window::show();
  const ngy313::graphic::image image("test1.png");
  return ngy313::process::run([&] {
    {
      const ngy313::graphic::scoped_render render;
      if (render.succeeded()) {
        ngy313::graphic::clear_screen(ngy313::utility::kBlack);
        ngy313::graphic::draw(ngy313::graphic::sprite(0.f, 0.f, image));
      }
    }
    ngy313::graphic::present();
  });
}