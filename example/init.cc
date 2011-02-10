#include <ngy313/process/process.hpp>
#include <ngy313/window/window.hpp>

int main() {
  ngy313::window::show();
  return ngy313::process::run([] {
    ngy313::process::sleep(1);
  });
}