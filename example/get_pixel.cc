#include <boost/assert.hpp>
#include <ngy313/process/process.hpp>
#include <ngy313/window/window.hpp>
#include <ngy313/graphic/graphic.hpp>
#include <ngy313/graphic/scoped_render.hpp>
#include <ngy313/graphic/box.hpp>
#include <ngy313/graphic/colored.hpp>
#include <ngy313/utility/color_code.hpp>

int main() {
  ngy313::window::show();
  return ngy313::process::run([] {
    {
      const ngy313::graphic::scoped_render render;
      if (render.succeeded()) {
        ngy313::graphic::clear_screen(ngy313::utility::kBlack);
        ngy313::graphic::draw(ngy313::graphic::box(0.f, 0.f, 480.f, 480.f) | 
                              ngy313::graphic::colored(ngy313::utility::kBlue));
        BOOST_ASSERT(ngy313::graphic::pixel_color(0.f, 0.f) == ngy313::utility::kBlue);
        BOOST_ASSERT(ngy313::graphic::pixel_color(320.f, 240.f) == ngy313::utility::kBlue);
        BOOST_ASSERT(ngy313::graphic::pixel_color(560.f, 240.f) == ngy313::utility::kBlack);
        BOOST_ASSERT(ngy313::graphic::pixel_color(560.f, 240.f) != ngy313::utility::kBlue);
      }
    }
    ngy313::graphic::present();
  });
}