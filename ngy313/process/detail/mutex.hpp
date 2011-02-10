#pragma once
#include <cassert>
#include <memory>
#include <stdexcept>
#include <string>
#include <Windows.h>
#include <ngy313/utility/string_piece.hpp>

namespace ngy313 { namespace process { namespace detail {
struct mutex_delete {
  void operator ()(const HANDLE mutex) const {
    assert(mutex);
    CloseHandle(mutex);
  }
};

typedef std::unique_ptr<std::remove_pointer<HANDLE>::type, mutex_delete> mutex_handle;

inline 
mutex_handle create_mutex(const utility::string_piece &name) {
  const HANDLE mutex = CreateMutex(nullptr, FALSE, name.c_str());
  if (!mutex) {
    // �G���[�̎��������x���ׂ�
    //throw std::runtime_error("�~���[�e�N�X�I�u�W�F�N�g�̍쐬�Ɏ��s���܂���");
  }
  return mutex_handle(mutex);
}

inline
bool existed_mutex() {
  return GetLastError() == ERROR_ALREADY_EXISTS;
}
}}}
