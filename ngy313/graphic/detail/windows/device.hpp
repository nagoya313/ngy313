#ifndef NGY313_GRAPHIC_DETAIL_WINDOWS_DEVICE_HPP_
#define NGY313_GRAPHIC_DETAIL_WINDOWS_DEVICE_HPP_
#include <cassert>
#include <stdexcept>
#include <ngy313/graphic/detail/windows/fwd.hpp>
#include <ngy313/graphic/detail/windows/addressing.hpp>
#include <ngy313/graphic/detail/windows/blend.hpp>
#include <ngy313/graphic/detail/windows/scoped_addressing.hpp>
#include <ngy313/graphic/detail/windows/scoped_blend.hpp>
#include <ngy313/graphic/detail/windows/scoped_texture_stage.hpp>
#include <ngy313/utility/detail/windows/com_delete.hpp>
#include <ngy313/window/detail/windows/fwd.hpp>
#include <ngy313/window/detail/windows/main_window.hpp>

namespace ngy313 { namespace graphic { namespace detail {
inline
D3DPRESENT_PARAMETERS init_present_parameters(const bool windowed, const int width, const int height) {
  const D3DPRESENT_PARAMETERS present_parameters = {
    width,
    height,
    windowed ? D3DFMT_UNKNOWN : D3DFMT_X8R8G8B8,
    1,
    D3DMULTISAMPLE_NONE,
    0,
    D3DSWAPEFFECT_DISCARD,
    nullptr,
    windowed ? TRUE : FALSE,
    TRUE,
    D3DFMT_D24S8,
    D3DPRESENTFLAG_LOCKABLE_BACKBUFFER,
    D3DPRESENT_RATE_DEFAULT,
    D3DPRESENT_INTERVAL_DEFAULT
  };
  return present_parameters;
}

inline
base_handle create_base() {
  const LPDIRECT3D9 direct3d = Direct3DCreate9(D3D_SDK_VERSION);
  if (!direct3d) {
    throw std::runtime_error("Direct3Dの作成に失敗しました");
  }
  return base_handle(direct3d);
}

inline
device_handle create_device(
    const window::detail::main_window &window, const base_handle &direct3d, const bool windowed) {
  assert(window.width());
  assert(direct3d);
  D3DPRESENT_PARAMETERS present_parameters = init_present_parameters(windowed, window.width(), window.height());
  LPDIRECT3DDEVICE9 device;
  if (FAILED(direct3d->CreateDevice(D3DADAPTER_DEFAULT, 
                                    D3DDEVTYPE_HAL, 
                                    window.window(), 
                                    D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                    &present_parameters,
                                    &device))) {
    if (FAILED(direct3d->CreateDevice(D3DADAPTER_DEFAULT,
                                      D3DDEVTYPE_HAL, 
                                      window.window(), 
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &present_parameters,
                                      &device))) {
      const HRESULT ref_hr = direct3d->CreateDevice(D3DADAPTER_DEFAULT,
                                                    D3DDEVTYPE_REF,
                                                    window.window(), 
                                                    D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                                    &present_parameters, 
                                                    &device);
      if (FAILED(ref_hr)) {
        // 例外をちゃんと実装する
        throw std::runtime_error("Direct3Dデバイスの作成に失敗しました\n詳細：");
	    }  
    }
  }
  return device_handle(device);
}

inline
void init_device(const device_handle &device) {
  assert(device);
  //set_addressing_tuple<default_addressing<0>::type>(device);
  //set_addressing_tuple<default_addressing<1>::type>(device);
  //set_texture_stage<default_stage0>(device);
  //set_texture_stage<default_stage1>(device);
  //device->SetRenderState(D3DRS_LIGHTING, FALSE);
  //device->SetRenderState(D3DRS_ZENABLE, FALSE);
  //device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR); 
  //device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR); 
  //device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR); 
}

inline
surface_handle render_surface(const device_handle &device) {
  assert(device);
  LPDIRECT3DSURFACE9 target;
  if (FAILED(device->GetRenderTarget(0, &target))) {
    throw std::runtime_error("レンダリングターゲットのサーフエイスの取得に失敗しました");
  }
  return surface_handle(target);
}

inline
void set_render_surface(const device_handle &device, const surface_handle &surface) {
  assert(device);
  assert(surface);
  device->SetRenderTarget(0, surface.get());
}


inline
surface_handle back_buffer(const device_handle &device) {
  assert(device);
  LPDIRECT3DSURFACE9 back;
  if (FAILED(device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &back))) {
    throw std::runtime_error("バックバッファの取得に失敗しました");
  }
  return surface_handle(back);
}

inline
surface_handle z_and_stencil(const device_handle &device) {
  assert(device);
  LPDIRECT3DSURFACE9 z_s;
  device->GetDepthStencilSurface(&z_s);
  return surface_handle(z_s);
}

inline
texture_handle create_texture(const device_handle &device, const int width, const int height) {
  assert(device);
  LPDIRECT3DTEXTURE9 tex;
  if (FAILED(device->CreateTexture(width, 
                                   height,
                                   1,
                                   D3DUSAGE_RENDERTARGET,
                                   D3DFMT_A8R8G8B8, 
                                   D3DPOOL_DEFAULT, 
                                   &tex, 
                                   nullptr))) {
    throw std::runtime_error("テクスチャの作成に失敗しました");
  }
  return texture_handle(tex);
}

inline
surface_handle create_z_and_stencil(const device_handle &device, const int width, const int height) {
  assert(device);
  LPDIRECT3DSURFACE9 suf;
  if (FAILED(device->CreateDepthStencilSurface(width, 
                                               height,
                                               D3DFMT_D24S8,
                                               D3DMULTISAMPLE_NONE,
                                               0, 
                                               TRUE, 
                                               &suf, 
                                               nullptr))) {
    throw std::runtime_error("深度及びステンシルバッファの作成に失敗しました");
  }
  return surface_handle(suf);
}

inline
surface_handle surface_level(const texture_handle &tex) {
  assert(tex);
  LPDIRECT3DSURFACE9 surface;
  if (FAILED(tex->GetSurfaceLevel(0, &surface))) {
    throw std::runtime_error("サーフェイスレベルの取得に失敗しました");
  }
  return surface_handle(surface);
}

inline
void set_z_and_stencil(const device_handle &device, const surface_handle &surface) {
  assert(device);
  assert(surface);
  device->SetDepthStencilSurface(surface.get());
}
}}}

#endif
