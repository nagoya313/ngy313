#ifndef NGY313_UTILITY_COM_INITIALIZER_HPP_
#define NGY313_UTILITY_COM_INITIALIZER_HPP_
#include <stdexcept>
#include <boost/noncopyable.hpp>
#define _WIN32_DCOM
#include <XAudio2.h>

namespace ngy313 { namespace utility { namespace detail {
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
}}}

#endif
