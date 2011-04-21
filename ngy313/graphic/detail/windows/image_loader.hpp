#ifndef NGY313_GRAPHIC_DETAIL_WINDOWS_IMAGE_LOADER_HPP_
#define NGY313_GRAPHIC_DETAIL_WINDOWS_IMAGE_LOADER_HPP_
#include <cassert>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>
#include <boost/noncopyable.hpp>
#include <d3dx9.h>
#include <ngy313/graphic/detail/windows/device.hpp>
#include <ngy313/graphic/detail/singleton.hpp>
#include <ngy313/graphic/fvf_traits.hpp>
#include <ngy313/graphic/texture_access.hpp>
#include <ngy313/graphic/vertex_member.hpp>
#include <ngy313/utility/string_piece.hpp>

namespace ngy313 { namespace graphic { namespace detail {
inline
texture_handle create_texture_from_memory(const device_handle &device, const std::vector<std::uint8_t> &data) {
  assert(device);
  LPDIRECT3DTEXTURE9 texture;
  D3DXIMAGE_INFO image_info;
  if (FAILED(D3DXCreateTextureFromFileInMemoryEx(device.get(), 
                                                 data.data(),
                                                 data.size(),
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
    throw std::runtime_error("画像データからのテクスチャの作成に失敗しました");
  }
  return texture_handle(texture);
}

inline
std::tuple<texture_handle, int, int> 
    create_texture_from_file(const device_handle &device, const utility::string_piece &file_name) {
  assert(device);
  LPDIRECT3DTEXTURE9 texture;
  D3DXIMAGE_INFO image_info;
  if (FAILED(D3DXCreateTextureFromFileExA(device.get(),
                                          file_name.c_str(),
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
  return std::tuple<texture_handle, int, int>(texture_handle(texture), image_info.Width, image_info.Height);
}

inline
std::tuple<texture_handle, int, int> 
    create_texture_from_alpha_png_file(const device_handle &device, const utility::string_piece &file_name) {
  return create_texture_from_file(device, file_name);
}

inline
std::tuple<texture_handle, int, int>
    create_texture_from_non_alpha_png_file(const device_handle &device, const utility::string_piece &file_name) {
  return create_texture_from_file(device, file_name);
}

inline
std::tuple<texture_handle, int, int> 
    create_texture_from_jpeg_file(const device_handle &device, const utility::string_piece &file_name) {
  return create_texture_from_file(device, file_name);
}
}}}

#endif
