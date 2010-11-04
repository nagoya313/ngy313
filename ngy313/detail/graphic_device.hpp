#pragma once
#include <cassert>
#include <stdexcept>
#include "com_fwd.hpp"
#include "window_impl.hpp"
#include "copy_vertex.hpp"

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

inline
void init_device(const graphic_device_handle &graphic_device) {
  assert(graphic_device);
  graphic_device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
  graphic_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
  graphic_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
  graphic_device->SetRenderState(D3DRS_LIGHTING, FALSE);
  graphic_device->SetRenderState(D3DRS_ZENABLE, FALSE);
}

inline
void clear(const graphic_device_handle &graphic_device, const std::uint32_t col) {
  assert(graphic_device);
  graphic_device->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, col, 1.f, 0);
}

inline
bool begin_scene(const graphic_device_handle &graphic_device) {
  assert(graphic_device);
  return SUCCEEDED(graphic_device->BeginScene());
}

inline
void end_scene(const graphic_device_handle &graphic_device) {
  assert(graphic_device);
  graphic_device->EndScene();
}

inline
void present(const window_handle &window, 
             const graphic_device_handle &graphic_device, 
             const bool windowed) {
  assert(window);
  assert(graphic_device);
  switch (graphic_device->Present(nullptr, nullptr, nullptr, nullptr)) {
    case D3DERR_DEVICELOST: {
      D3DPRESENT_PARAMETERS present_parameter = detail::init_present_parameters(window, windowed);
	    if (graphic_device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
        if (FAILED(graphic_device->Reset(&present_parameter))) {
           throw std::runtime_error("デバイスロストからの復旧に失敗しました");
	      }
        detail::init_device(graphic_device);
      }
	    break;
    }
    case D3DERR_DRIVERINTERNALERROR: {
	    throw std::runtime_error("内部ドライバエラーが発生しました");
	    break;
    }
    default: {
	    break;
    }
  }
}

inline
void reset(const window_handle &window,
           const graphic_device_handle &graphic_device,
           const bool windowed) {
  assert(window);
  assert(graphic_device);
  D3DPRESENT_PARAMETERS present_parameter = detail::init_present_parameters(window, windowed);
  if (FAILED(graphic_device->Reset(&present_parameter))) {
     throw std::runtime_error("デバイスリセｯﾄに失敗しました");
	}
}

template <typename Drawable>
void draw(const graphic_device_handle &graphic_device, const Drawable &drawable) {
  assert(graphic_device);
  const typename Drawable::vertex_array_type vertex = copy_vertex(drawable);
  graphic_device->SetFVF(typename Drawable::fvf_type::value);
  graphic_device->DrawPrimitiveUP(typename Drawable::primitive_type::value,
                                  typename Drawable::count_type::value, 
                                  &(vertex.front()), 
                                  sizeof(vertex.front()));
}
}}