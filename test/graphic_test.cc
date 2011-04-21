#include <exception>
#include <boost/assert.hpp>
#include <ngy313/process/process.hpp>
#include <ngy313/window/message_box.hpp>
#include <ngy313/graphic/box.hpp>
#include <ngy313/graphic/graphic.hpp>
#include <ngy313/graphic/scoped_render.hpp>
#include <ngy313/utility/color_code.hpp>

using namespace ngy313;

namespace {
const auto kClearColor = utility::kBlack;
const auto kShapeColor = utility::kWhite;
const int kWidth = 320;
const int kHeight = 240;
}

int main() {
  try {
    graphic::resize(kWidth, kHeight);
    BOOST_ASSERT(graphic::width() == kWidth && graphic::height() == kHeight);
    return process::run([] {
      {
        const graphic::scoped_render render;
        if (render.succeeded()) {
          graphic::clear_screen(kClearColor);
          BOOST_ASSERT(graphic::pixel_color(0, 0) == kClearColor);
          BOOST_ASSERT(graphic::pixel_color(160, 120) == kClearColor);
          BOOST_ASSERT(graphic::pixel_color(319, 239) == kClearColor);
          graphic::draw(graphic::box(0.f, 0.f, 320.f, 240.f, kShapeColor));
          BOOST_ASSERT(graphic::pixel_color(160, 120) == kShapeColor);
        }
      }
      graphic::present();
    });
  } catch(const std::exception &error) {
    window::message_box(error.what(), "error", window::kButtonOk, window::kIconStop);
    return 0;
  }
}