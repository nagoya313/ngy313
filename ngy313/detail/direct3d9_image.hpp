#ifndef NGY313_DETAIL_DIRECT3D9_IMAGE_HPP_
#define NGY313_DETAIL_DIRECT3D9_IMAGE_HPP_

#include <stdexcept>
#include <d3d9.h>
#include <d3dx9.h>
#include <ngy313/string_wrap.hpp>

namespace ngy313 { namespace detail {
template <typename Texture>
class direct3d9_image {
 public:
	explicit direct3d9_image(const string_wrap &file_name)
	    : file_name_(file_name.string()) {}

  template <typename Device>
  typename Texture::texture_tuple operator ()(const Device &device) const {
  	assert(device.handle());
    LPDIRECT3DTEXTURE9 texture;
    D3DXIMAGE_INFO image_info;
    if (FAILED(D3DXCreateTextureFromFileEx(device.handle().get(),
                                           file_name_.c_str(),
                                           D3DX_DEFAULT,
                                           D3DX_DEFAULT,
                                           D3DX_DEFAULT,
                                           0,
                                           D3DFMT_UNKNOWN, 
                                           D3DPOOL_MANAGED,
                                           D3DX_DEFAULT,
                                           D3DX_DEFAULT,
                                           0, 
                                           &image_info,
                                           nullptr,
                                           &texture))) {
      throw std::runtime_error("画像ファイルからのテクスチャの作成に失敗しました");
    }
    return texture_tuple(texture_handle(texture, false), image_info.Width, image_info.Height);
  }

 private:
  std::string file_name_;
};
}}

#endif
