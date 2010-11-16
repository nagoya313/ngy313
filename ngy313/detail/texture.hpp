#pragma once
#include <cassert>
#include <string>
#include <boost/functional/hash.hpp>
#include <d3dx9.h>
#include "com_fwd.hpp"

namespace ngy313 { namespace detail {
struct texture_key {
  const graphic_device_handle &graphic_device;
  std::string texture_name;
};

inline
bool operator ==(const texture_key &lhs, const texture_key &rhs) {
  return lhs.graphic_device == rhs.graphic_device && 
         lhs.texture_name == rhs.texture_name;
}

inline
std::size_t hash_value(const texture_key &key) {
  std::size_t hash = 0;
  boost::hash_combine(hash, key.graphic_device.get());
  boost::hash_combine(hash, key.texture_name);
  return hash;
}

typedef std::unique_ptr<IDirect3DTexture9, detail::com_delete> texture_handle;

struct texture_core_data {
  LPDIRECT3DTEXTURE9 texture;
  float width;
  float height;
};

texture_core_data create_texture(const texture_key &key) {
  assert(key.graphic_device);
  LPDIRECT3DTEXTURE9 texture = nullptr;
  D3DXIMAGE_INFO image_info;
  if (FAILED(D3DXCreateTextureFromFileEx(key.graphic_device.get(),
                                         key.texture_name.c_str(),
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
    throw std::runtime_error("画像ファイルからテクスチャの作成に失敗しました");
  }
  texture_core_data data = {
    texture,
    static_cast<float>(image_info.Width),
    static_cast<float>(image_info.Height)
  };
  return data;
}

struct texture_data {
  explicit texture_data(const texture_key &key) {
    const texture_core_data data = create_texture(key);
    texture.reset(data.texture);
    width = data.width;
    height = data.height;
  }

  texture_handle texture;
  float width;
  float height;
};
}}