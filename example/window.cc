#include <boost/range/algorithm/for_each.hpp>
#include <ngy313/process.hpp>
#include <ngy313/window.hpp>

using namespace boost;
using namespace ngy313;

int main() {
  set_window_caption("test_window");
  window_resize(640, 480);
  window_show();
  for_each(process_message(), main_loop([]() {
    sleep(1);
  }));
  return 0;
}