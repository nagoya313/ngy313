#include <boost/range/algorithm/for_each.hpp>
#include <ngy313/process.hpp>
#include <ngy313/window.hpp>

int main() {
  ngy313::set_window_caption("test_window");
  ngy313::window_resize(640, 480);
  ngy313::window_show();
  boost::for_each(ngy313::process_message(), ngy313::main_loop([]() {
    ngy313::sleep(1);
  }));
  return 0;
}