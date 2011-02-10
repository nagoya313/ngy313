#include <ngy313/process/process.hpp>
#include <ngy313/window/window.hpp>
#include <ngy313/graphic/graphic.hpp>
#include <ngy313/graphic/scoped_render.hpp>
#include <ngy313/graphic/image.hpp>
#include <ngy313/graphic/sprite.hpp>
#include <ngy313/graphic/uv_moved.hpp>
#include <ngy313/graphic/uv_extended.hpp>
#include <ngy313/graphic/base_point.hpp>
#include <ngy313/utility/color_code.hpp>

int main() {
  ngy313::window::show();
  const ngy313::graphic::image image("test2.png");
  int i = 0;
  int frame = 0;
  return ngy313::process::run([&] {
    {
      const ngy313::graphic::scoped_render render;
      if (render.succeeded()) {
        ngy313::graphic::clear_screen(ngy313::utility::kBlack);
        ngy313::graphic::draw(ngy313::graphic::size_sprite(0.f, 0.f, 48.f, 56.f, image) |
                              ngy313::graphic::uv_extended_uv<0>(ngy313::graphic::base_point_set(0.f, 0.f),
                                                                 1.f / 4.f,
                                                                 1.f / 3.f) |
                              ngy313::graphic::uv_moved<0>((1.f / 4.f) * (i % 4), (1.f / 3.f) * (i / 4)));
      }
    }
    ngy313::graphic::present();
    if (!(++frame % 8)) {
      if (++i == 10) {
        i = 0;
      }
    }
  });
}