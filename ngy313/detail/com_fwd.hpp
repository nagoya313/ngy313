#pragma once
#pragma comment(lib, "d3d9.lib")
#ifndef NDEBUG
#pragma comment(lib, "d3dx9d.lib")
#else
#pragma comment(lib, "d3dx9.lib")
#endif
#include <cassert>
#include <memory>
#include <boost/intrusive_ptr.hpp>
#include <boost/mpl/has_xxx.hpp>
#include <d3d9.h>
#include <d3dx9.h>

inline
void intrusive_ptr_add_ref(const LPDIRECT3DTEXTURE9 com) {
  assert(com);
  com->AddRef();
}

inline
void intrusive_ptr_release(const LPDIRECT3DTEXTURE9 com) {
  assert(com);
  com->Release();
}

namespace ngy313 { namespace detail {
struct com_delete {
  void operator ()(const LPUNKNOWN com) const {
    assert(com);
    com->Release();
  }
};

typedef std::unique_ptr<IDirect3D9, com_delete> graphic_base_handle;
typedef std::unique_ptr<IDirect3DDevice9, com_delete> graphic_device_handle;
typedef boost::intrusive_ptr<IDirect3DTexture9> texture_handle;
typedef std::unique_ptr<IDirect3DSurface9, com_delete> surface_handle;
typedef std::unique_ptr<ID3DXFont, com_delete> font_handle;

BOOST_MPL_HAS_XXX_TRAIT_DEF(image_type)
BOOST_MPL_HAS_XXX_TRAIT_DEF(image1_type)
BOOST_MPL_HAS_XXX_TRAIT_DEF(image2_type)
BOOST_MPL_HAS_XXX_TRAIT_DEF(blend_pair_type)
BOOST_MPL_HAS_XXX_TRAIT_DEF(texture_stage_pair_type)
BOOST_MPL_HAS_XXX_TRAIT_DEF(addressing_pair_type)
}}