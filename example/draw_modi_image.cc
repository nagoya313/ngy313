#include <ngy313/process/process.hpp>
#include <ngy313/window/window.hpp>
#include <ngy313/graphic/graphic.hpp>
#include <ngy313/graphic/scoped_render.hpp>
#include <ngy313/graphic/image.hpp>
#include <ngy313/graphic/sprite.hpp>
#include <ngy313/graphic/moved.hpp>
#include <ngy313/utility/color_code.hpp>

int main() {
  ngy313::window::show();
  const ngy313::graphic::image image("test2.png");
  return ngy313::process::run([&] {
    {
      const ngy313::graphic::scoped_render render;
      if (render.succeeded()) {
        ngy313::graphic::clear_screen(ngy313::utility::kBlack);
        ngy313::graphic::draw(ngy313::graphic::sprite(0.f, 0.f, image) | 
                              ngy313::graphic::moved_at(1, 145.f, 62.f) |
                              ngy313::graphic::moved_at(2, 12.f, 56.f) |
                              ngy313::graphic::moved_at(3, 168.f, 121.f));
      }
    }
    ngy313::graphic::present();
  });
}