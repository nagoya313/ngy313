#ifndef NGY313_GRAPHIC_DETAIL_LINUX_DEVICE_HPP_
#define NGY313_GRAPHIC_DETAIL_LINUX_DEVICE_HPP_
#include <gtkglmm.h>

namespace ngy313 { namespace graphic { namespace detail {
void gl_init() {
  char empty_str[] = "";
  char *nul[1] = {empty_str};
  char **tempc = {nul};
  int tempv = 1;
  Gtk::GL::init(tempv, tempc);
}
}}}

#endif

