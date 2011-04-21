#ifndef NGY313_GRAPHIC_DETAIL_WINDOWS_FWD_HPP_
#define NGY313_GRAPHIC_DETAIL_WIDNOWS_FWD_HPP_
#include <memory>
#pragma warning(disable: 4512)
#include <boost/signals2/signal.hpp>
#pragma warning(default: 4512)
#include <d3d9.h>
#include <d3dx9.h>
#include <ngy313/utility/detail/windows/com_delete.hpp>

namespace ngy313 { namespace graphic { namespace detail {
typedef std::unique_ptr<IDirect3D9, utility::detail::com_delete> base_handle;
typedef std::unique_ptr<IDirect3DDevice9, utility::detail::com_delete> device_handle;
typedef std::unique_ptr<IDirect3DTexture9, utility::detail::com_delete> texture_handle;
typedef std::unique_ptr<IDirect3DSurface9, utility::detail::com_delete> surface_handle;
typedef std::unique_ptr<ID3DXFont, utility::detail::com_delete> font_handle;

typedef D3DVIEWPORT9 viewport;

typedef boost::signals2::signal<void (const device_handle &)> before_reset_signal;
typedef boost::signals2::signal<void (const device_handle &)> after_reset_signal;
}}}

#endif
