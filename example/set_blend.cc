#include <ngy313/process/process.hpp>
#include <ngy313/window/window.hpp>
#include <ngy313/graphic/graphic.hpp>
#include <ngy313/graphic/scoped_render.hpp>
#include <ngy313/graphic/image.hpp>
#include <ngy313/graphic/blend.hpp>
#include <ngy313/graphic/sprite.hpp>
#include <ngy313/graphic/colored.hpp>
#include <ngy313/utility/color_code.hpp>

int main() {
  ngy313::window::show();
  const ngy313::graphic::image back("test3.png");
  const ngy313::graphic::image image("test4.png");
  return ngy313::process::run([&] {
    {
      const ngy313::graphic::scoped_render render;
      if (render.succeeded()) {
        ngy313::graphic::clear_screen(ngy313::utility::kBlack);
        ngy313::graphic::draw(ngy313::graphic::sprite(0.f, 0.f, back));
        ngy313::graphic::draw(ngy313::graphic::sprite(0.f, 0.f, image));
        ngy313::graphic::draw(ngy313::graphic::sprite(image.width(), 0.f, image) | 
                              ngy313::graphic::colored(0x80FFFFFF));
        ngy313::graphic::draw(ngy313::graphic::sprite(0.f, image.height(), image) | 
                              ngy313::graphic::add_blend);
        ngy313::graphic::draw(ngy313::graphic::sprite(image.width(), image.height(), image) | 
                              ngy313::graphic::colored(0xCCFFFFFF) |
                              ngy313::graphic::sub_blend);
        ngy313::graphic::draw(ngy313::graphic::sprite(0.f, image.height() * 2.f, image) | 
                              ngy313::graphic::mul_blend);
      }
    }
    ngy313::graphic::present();
  });
}