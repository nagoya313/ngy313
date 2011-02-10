#pragma once
#pragma comment(lib, "d3d9.lib")
#ifndef NDEBUG
#pragma comment(lib, "d3dx9d.lib")
#else
#pragma comment(lib, "d3dx9.lib")
#endif
#include <memory>
#include <boost/intrusive_ptr.hpp>
#include <boost/signals2/signal.hpp>
#include <d3d9.h>
#include <d3dx9.h>

namespace ngy313 { namespace utility {
struct com_delete;
}}

namespace ngy313 { namespace graphic { namespace detail {
typedef std::unique_ptr<IDirect3D9, utility::com_delete> base_handle;
typedef std::unique_ptr<IDirect3DDevice9, utility::com_delete> device_handle;
typedef boost::intrusive_ptr<IDirect3DTexture9> texture_handle;
typedef std::unique_ptr<IDirect3DSurface9, utility::com_delete> surface_handle;
typedef boost::intrusive_ptr<ID3DXFont> font_handle;

typedef D3DVIEWPORT9 viewport;

typedef boost::signals2::signal<void (const device_handle &)> before_reset_signal;
typedef boost::signals2::signal<void (const device_handle &)> after_reset_signal;
}}}
