#ifndef NGY313_UTILITY_COM_DELETE_
#define NGY313_UTILITY_COM_DELETE_
#include <cassert>
#include <Unknwn.h>

namespace ngy313 { namespace utility {
struct com_delete {
  void operator ()(const LPUNKNOWN com) const {
    assert(com);
    com->Release();
  }
};
}}

#endif

