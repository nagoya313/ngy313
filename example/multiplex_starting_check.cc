#include <ngy313/process/process.hpp>
#include <ngy313/process/multiplex_starting_check.hpp>
#include <ngy313/window/message_box.hpp>

int main() {
  const ngy313::process::multiplex_starting_check check("multiplex_starting_check_sample");
  if (check.multiplex_starting()) {
    ngy313::window::message_box("multiplex starting",
                                "message",
                                ngy313::window::kButtonOk,
                                ngy313::window::kIconInformation);
  } else {
    ngy313::window::message_box("not multiplex starting", 
                                "message",
                                ngy313::window::kButtonOk,
                                ngy313::window::kIconInformation);
  }
  ngy313::process::run([] {
    ngy313::process::sleep(1);
  });
}
