#pragma once
#pragma comment(lib, "d3d9.lib")
#include <cassert>
#include <memory>
#include <d3d9.h>

namespace ngy313 { namespace detail {
struct com_delete {
  void operator ()(const LPUNKNOWN com) const {
    assert(com);
    com->Release();
  }
};

typedef std::unique_ptr<IDirect3D9, com_delete> graphic_base_handle;
typedef std::unique_ptr<IDirect3DDevice9, com_delete> graphic_device_handle;
}}