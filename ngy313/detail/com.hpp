#ifndef NGY313_DETAIL_COM_HPP_
#define NGY313_DETAIL_COM_HPP_

#include <cassert>
#include <stdexcept>
#include <boost/noncopyable.hpp>
#include <Objbase.h>
#include <Unknwn.h>

namespace boost {
void intrusive_ptr_add_ref(LPUNKNOWN com) {
  assert(com);
  com->AddRef();
}

void intrusive_ptr_release(LPUNKNOWN com) {
  assert(com);
  com->Release();
}
}

namespace ngy313 { namespace detail {
struct com_initializer : private boost::noncopyable {
  com_initializer() {
    if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED))) {
      throw std::runtime_error("COMの初期化に失敗しました");
    }
  }

  ~com_initializer() {
    CoUninitialize();
  }
};

struct com_delete {
  void operator ()(LPUNKNOWN com) const {
    assert(com);
    com->Release();
  }
};
}}

#endif
