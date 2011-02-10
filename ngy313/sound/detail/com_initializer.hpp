#pragma once
#include <stdexcept>
#include <boost/noncopyable.hpp>
#define _WIN32_DCOM
#include <XAudio2.h>

namespace ngy313 { namespace sound { namespace detail {
struct com_initializer : private boost::noncopyable {
  com_initializer() {
    if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED))) {
      throw std::runtime_error("COMÇÃèâä˙âªÇ…é∏îsÇµÇ‹ÇµÇΩ");
    }
  }

  ~com_initializer() {
    CoUninitialize();
  }
};
}}}
