#pragma once
#include <cassert>
#include <stdexcept>
#include <memory>
#include <Windows.h>
#include "string_piece.hpp"

namespace ngy313 { namespace detail {
struct mutex_delete {
  void operator ()(const HANDLE mutex) const {
    assert(mutex);
    CloseHandle(mutex);
  }
};

typedef std::unique_ptr<std::remove_pointer<HANDLE>::type, mutex_delete> mutex_handle;

inline 
mutex_handle create_mutex(const string_piece &name) {
  const HANDLE mutex = CreateMutex(nullptr, FALSE, name.c_str());
  if (!mutex) {
    throw std::runtime_error("ミューテクスオブジェクトの作成に失敗しました");
  }
  return mutex_handle(mutex);
}

inline
bool existed_mutex() {
  return GetLastError() == ERROR_ALREADY_EXISTS;
}
}}