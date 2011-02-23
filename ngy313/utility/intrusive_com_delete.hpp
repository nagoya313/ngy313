#pragma once
#include <cassert>
#include <Unknwn.h>

namespace boost {
inline
void intrusive_ptr_add_ref(const LPUNKNOWN com) {
  assert(com);
  com->AddRef();
}

inline
void intrusive_ptr_release(const LPUNKNOWN com) {
  assert(com);
  com->Release();
}
}
