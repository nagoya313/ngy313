#ifndef NGY313_DETAIL_DIRECT3D9_TEXTURE_HPP_
#define NGY313_DETAIL_DIRECT3D9_TEXTURE_HPP_

#include <cassert>
#include <memory>
#include <tuple>
#include <boost/noncopyable.hpp>
#include <d3d9.h>
#include <ngy313/detail/com.hpp>

namespace ngy313 { namespace detail {
typedef boost::intrusive_ptr<IDirect3DTexture9> texture_handle;
typedef std::tuple<texture_handle, int, int> texture_tuple;

template <typename Device>
texture_tuple create_texture(const Device &device,
		                         int width,
		                         int height) {
  assert(device.handle());
  LPDIRECT3DTEXTURE9 tex;
  if (FAILED(D3DXCreateTexture(device.handle().get(),
                               width, 
                               height,
                               1,
                               D3DUSAGE_RENDERTARGET,
                               D3DFMT_A8R8G8B8, 
                               D3DPOOL_DEFAULT, 
                               &tex))) {
    throw std::runtime_error("レンダリングターゲットテクスチャの作成に失敗しました");
  }
  return texture_tuple(texture_handle(tex, false), width, height);
}

class direct3d9_texture {
 public:
  typedef const texture_handle &handle_type;
  typedef std::tuple<texture_handle, int, int> texture_tuple;
  typedef void (*deleter_type)(LPUNKNOWN);

  template <typename Device>
  explicit direct3d9_texture(const Device &device,
  		                       int width,
  		                       int height)
      : data_(create_texture(device, width, height)) {}

  template <typename Device, typename Image>
  explicit direct3d9_texture(const Device &device,
  		                       const Image &image)
      : data_(image(device)) {}

  int width() const {
    return std::get<1>(data_);
  }

  int height() const {
    return std::get<2>(data_);
  }

  handle_type handle() const {
    return std::get<0>(data_);
  }

 private:
  texture_tuple data_;
};
}}

#endif
