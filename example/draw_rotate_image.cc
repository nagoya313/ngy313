#include <ngy313/process/process.hpp>
#include <ngy313/window/window.hpp>
#include <ngy313/graphic/graphic.hpp>
#include <ngy313/graphic/scoped_render.hpp>
#include <ngy313/graphic/image.hpp>
#include <ngy313/graphic/sprite.hpp>
#include <ngy313/graphic/extended.hpp>
#include <ngy313/graphic/rotated.hpp>
#include <ngy313/graphic/base_point.hpp>
#include <ngy313/utility/color_code.hpp>

const float kPI = 3.141592f;

int main() {
  ngy313::window::show();
  const ngy313::graphic::image image("test2.png");
  return ngy313::process::run([&] {
    {
      const ngy313::graphic::scoped_render render;
      if (render.succeeded()) {
        ngy313::graphic::clear_screen(ngy313::utility::kBlack);
        ngy313::graphic::draw(ngy313::graphic::sprite((640.f - image.width()) / 2.f, 
                                                      (480.f - image.height()) / 2.f,
                                                      image) | 
                              ngy313::graphic::extended(ngy313::graphic::base_point_set_center, 1.5f) |
                              ngy313::graphic::rotated(ngy313::graphic::base_point_set_center, kPI / 2.f));
      }
    }
    ngy313::graphic::present();
  });
}