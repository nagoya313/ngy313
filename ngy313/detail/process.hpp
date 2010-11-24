#pragma once
#include <cassert>
#include <cstdint>
#include <boost/optional.hpp>
#include <Windows.h>

namespace ngy313 { namespace detail {
typedef boost::optional<MSG> message; 

inline
bool has_message() {
  MSG mes;
  return PeekMessage(&mes, nullptr, 0, 0, PM_NOREMOVE) != 0;
}

inline
message get_message() {
  MSG mes;
  const BOOL result = GetMessage(&mes, nullptr, 0, 0);
  if (!(result && ~result)) {
    return message();
  }
  return message(mes);
}

inline
void translate_and_dispatch_message(const message &mes) {
  assert(mes);
  TranslateMessage(&(*mes));
  DispatchMessage(&(*mes));
}

inline
void post_quit_message(const int code) {
  PostQuitMessage(0);
}

inline 
void sleep_process(const std::uint32_t time) {
  Sleep(time);
}
}}