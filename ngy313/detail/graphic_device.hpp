#pragma once
#include <cassert>
#include <stdexcept>
#include "com_fwd.hpp"
#include "window_impl.hpp"

namespace ngy313 { namespace detail {
inline
D3DPRESENT_PARAMETERS init_present_parameters(const window_handle &window, 
                                              const bool windowed) {
  assert(window);
  const D3DPRESENT_PARAMETERS present_parameters = {
    width(window),
    height(window),
    windowed ? D3DFMT_UNKNOWN : D3DFMT_X8R8G8B8,
    1,
    D3DMULTISAMPLE_NONE,
    0,
    D3DSWAPEFFECT_DISCARD,
    window.get(),
    windowed ? TRUE : FALSE,
    TRUE,
    D3DFMT_D24S8,
    0,
    D3DPRESENT_RATE_DEFAULT,
    D3DPRESENT_INTERVAL_DEFAULT
  };
  return present_parameters;
}

inline
graphic_base_handle create_graphic_base() {
  const LPDIRECT3D9 direct3d = Direct3DCreate9(D3D_SDK_VERSION);
  if (!direct3d) {
    throw std::runtime_error("Direct3Dの作成に失敗しました");
  }
  return graphic_base_handle(direct3d);
}

inline
graphic_device_handle create_graphic_device(
    const window_handle &window, 
    const graphic_base_handle &direct3d,
    const bool windowed) {
  assert(window);
  assert(direct3d);
  D3DPRESENT_PARAMETERS present_parameters = 
      detail::init_present_parameters(window, windowed);
  LPDIRECT3DDEVICE9 graphic_device = nullptr;
  if (FAILED(direct3d->CreateDevice(D3DADAPTER_DEFAULT, 
                                    D3DDEVTYPE_HAL, 
                                    window.get(), 
                                    D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                    &present_parameters,
                                    &graphic_device))) {
    if (FAILED(direct3d->CreateDevice(D3DADAPTER_DEFAULT,
                                      D3DDEVTYPE_HAL, 
                                      window.get(), 
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &present_parameters,
                                      &graphic_device))) {
      if (FAILED(direct3d->CreateDevice(D3DADAPTER_DEFAULT,
                                        D3DDEVTYPE_REF,
                                        window.get(), 
                                        D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                        &present_parameters, 
                                        &graphic_device))) {								
	       throw std::runtime_error("Direct3Dデバイスの作成に失敗しました");
	    }  
    }
  }
  return graphic_device_handle(graphic_device);
}
}}