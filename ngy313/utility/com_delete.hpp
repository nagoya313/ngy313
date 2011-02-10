#pragma once
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
