#include <exception>
#include <string>
#include <boost/assert.hpp>
#include <ngy313/process/process.hpp>
#include <ngy313/window/window.hpp>
#include <ngy313/window/message_box.hpp>

namespace {
const std::string kCaption("window_test");
const std::string kIcon("test.ico");
const int kX = 128;
const int kY = 128;
const int kWidth = 800;
const int kHeight = 600;
}

using namespace ngy313;

int main() {
  try {
    window::set_caption(kCaption);
    BOOST_ASSERT(window::caption() == kCaption);
    window::move(kX, kY);
    BOOST_ASSERT(window::x() == kX && window::y() == kY);
    window::resize(kWidth, kHeight);
    BOOST_ASSERT(window::width() == kWidth && window::height() == kHeight);
    window::set_icon(kIcon);
    BOOST_ASSERT(window::icon() == kIcon);
    return process::run([] {
      process::sleep(1);
    });
  } catch(const std::exception &error) {
    window::message_box(error.what(), "error", window::kButtonOk, window::kIconStop);
    return 0;
  }
}