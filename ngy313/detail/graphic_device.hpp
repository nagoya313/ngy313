#pragma once
#include <cassert>
#include <stdexcept>
#include <type_traits>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/has_xxx.hpp>
#include "com_fwd.hpp"
#include "graphic_fwd.hpp"
#include "window_impl.hpp"
#include "drawable_core_access.hpp"

namespace ngy313 { namespace detail {
BOOST_MPL_HAS_XXX_TRAIT_DEF(image_type)
BOOST_MPL_HAS_XXX_TRAIT_DEF(image1_type)
BOOST_MPL_HAS_XXX_TRAIT_DEF(image2_type)

inline
D3DPRESENT_PARAMETERS init_present_parameters(const window_handle &window, const bool windowed) {
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
graphic_device_handle create_graphic_device(const window_handle &window, 
                                            const graphic_base_handle &direct3d,
                                            const bool windowed) {
  assert(window);
  assert(direct3d);
  D3DPRESENT_PARAMETERS present_parameters = detail::init_present_parameters(window, windowed);
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
      const HRESULT ref_hr = direct3d->CreateDevice(
                                 D3DADAPTER_DEFAULT,
                                 D3DDEVTYPE_REF,
                                 window.get(), 
                                 D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                 &present_parameters, 
                                 &graphic_device);
      if (FAILED(ref_hr)) {								
	       throw hresult_error("Direct3Dデバイスの作成に失敗しました\n詳細：",
                             ref_hr);
	    }  
    }
  }
  return graphic_device_handle(graphic_device);
}

inline
void init_device(const graphic_device_handle &graphic_device) {
  assert(graphic_device);
  graphic_device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
  graphic_device->SetRenderState(D3DRS_LIGHTING, FALSE);
  graphic_device->SetRenderState(D3DRS_ZENABLE, FALSE);
}

inline
void clear(const graphic_device_handle &graphic_device, const std::uint32_t col) {
  assert(graphic_device);
  graphic_device->Clear(0, 
                        nullptr,
                        D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 
                        col,
                        1.f, 
                        0);
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
void reset(const window_handle &window, const graphic_device_handle &graphic_device, const bool windowed) {
  assert(window);
  assert(graphic_device);
  D3DPRESENT_PARAMETERS present_parameter = detail::init_present_parameters(window, windowed);
  if (FAILED(graphic_device->Reset(&present_parameter))) {
     throw std::runtime_error("デバイスリセットに失敗しました");
	}
  init_device(graphic_device);
}

void set_blend_mode(const graphic_device_handle &graphic_device, const D3DBLEND src, const D3DBLEND dest) {
  assert(graphic_device);
  graphic_device->SetRenderState(D3DRS_SRCBLEND, src);
  graphic_device->SetRenderState(D3DRS_DESTBLEND, dest);
}

template <typename BlendPair>
void set_blend_pair(const graphic_device_handle &graphic_device) {
  assert(graphic_device);
  set_blend_mode(graphic_device, BlendPair::src_type::value, BlendPair::dest_type::value);
}

template <typename Drawable>
void set_texture12(const graphic_device_handle &graphic_device,
                   const Drawable &drawable,
                   typename boost::enable_if<has_image1_type<Drawable>>::type * = nullptr) {
  assert(graphic_device);
  graphic_device->SetTexture(0, drawable_core_access::texture1(drawable).get());
  graphic_device->SetTexture(1, nullptr);
}

template <typename Drawable>
void set_texture12(const graphic_device_handle &graphic_device,
                   const Drawable &drawable,
                   typename boost::enable_if<has_image2_type<Drawable>>::type * = nullptr) {
  assert(graphic_device);
  graphic_device->SetTexture(0, drawable_core_access::texture1(drawable).get());
  graphic_device->SetTexture(1, drawable_core_access::texture2(drawable).get());
}

template <typename Drawable>
void set_texture(const graphic_device_handle &graphic_device,
                 const Drawable &drawable,
                 typename boost::enable_if<has_image_type<Drawable>>::type * = nullptr) {
  assert(graphic_device);
  set_texture12(graphic_device, drawable);
}

template <typename Drawable>
void set_texture(const graphic_device_handle &graphic_device,
                 const Drawable &,
                 typename boost::disable_if<has_image_type<Drawable>>::type * = nullptr) {
  assert(graphic_device);
  graphic_device->SetTexture(0, nullptr);
  graphic_device->SetTexture(1, nullptr);
}

template <typename Drawable>
void common_draw(const graphic_device_handle &graphic_device, const Drawable &drawable) {
  assert(graphic_device);
  const Drawable::vertex_array_type 
      vertex = drawable_core_access::copy_vertex(drawable);
  set_texture(graphic_device, drawable);
  graphic_device->SetFVF(Drawable::fvf_type::value);
  graphic_device->DrawPrimitiveUP(Drawable::primitive_type::value,
                                  Drawable::count_type::value, 
                                  &(vertex.front()), 
                                  sizeof(vertex.front()));
}

template <typename Drawable>
void draw(const graphic_device_handle &graphic_device,
          const Drawable &drawable,
          typename boost::enable_if<std::is_same<typename Drawable::blend_type,
                                    default_blend>>::type * = nullptr) {
  assert(graphic_device);
  common_draw(graphic_device, drawable);
}

template <typename Drawable>
void draw(const graphic_device_handle &graphic_device,
          const Drawable &drawable,
          typename boost::disable_if<std::is_same<typename Drawable::blend_type,
                                     default_blend>>::type * = nullptr) {
  assert(graphic_device);
  set_blend_pair<typename Drawable::blend_type>(graphic_device);
  common_draw(graphic_device, drawable);
  set_blend_pair<default_blend>(graphic_device);
}
}}