#pragma once
#include <cassert>
#include <stdexcept>
#include <string>
#include <tuple>
#include <type_traits>
#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>
#include <boost/functional/hash.hpp>
#include <d3dx9.h>
#include <ngy313/graphic/detail/device.hpp>
#include <ngy313/graphic/detail/singleton.hpp>
#include <ngy313/utility/string_piece.hpp>

namespace ngy313 { namespace graphic {
class texture;
class multi_texture;
class text_image;
}}

namespace ngy313 { namespace graphic { namespace detail {
struct texture_key {
  const device_handle &device;
  std::string name;
};

inline
bool operator ==(const texture_key &lhs, const texture_key &rhs) {
  return lhs.device == rhs.device && lhs.name == rhs.name;
}

inline
std::size_t hash_value(const texture_key &key) {
  std::size_t hash = 0;
  boost::hash_combine(hash, key.device.get());
  boost::hash_combine(hash, key.name);
  return hash;
}

inline
std::tuple<texture_handle, float, float> create_texture_from_file(const texture_key &key) {
  assert(key.device);
  LPDIRECT3DTEXTURE9 texture;
  D3DXIMAGE_INFO image_info;
  if (FAILED(D3DXCreateTextureFromFileEx(key.device.get(),
                                         key.name.c_str(),
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
  return std::make_tuple(texture_handle(texture, false), 
                         static_cast<float>(image_info.Width), 
                         static_cast<float>(image_info.Height));
}

class texture_data {
 public:
  explicit texture_data(const texture_key &key) : data_(create_texture_from_file(key)) {}

  const texture_handle &texture() const {
    return std::get<0>(data_);
  }

  float width() const {
    return std::get<1>(data_);
  }

  float height() const {
    return std::get<2>(data_);
  }

 private:
  const std::tuple<texture_handle, float, float> data_;
};

inline
texture_key init_texture_key(const utility::string_piece &file_name) {
  const texture_key key = {device(), file_name.string()};
  return key;
}

typedef boost::flyweights::flyweight<boost::flyweights::key_value<texture_key, texture_data>> texture_type;

class texture_access {
 private:
  template <typename Image>
  static const texture_handle &texture1(const Image &image) {
    return image.texture1();
  }

  friend class ngy313::graphic::texture;
  friend class ngy313::graphic::multi_texture;
  friend class ngy313::graphic::text_image;
};

class texture_core_access {
 private:
  template <typename Texture>
  static const texture_handle &texture1(const Texture &tex) {
    return tex.texture1();
  }

  template <typename Drawable>
  friend typename std::enable_if<std::is_base_of<texture, Drawable>::value>::type
    set_texture(const device_handle &device, const Drawable &drawable);
};

template <typename Drawable>
typename std::enable_if<std::is_base_of<texture, Drawable>::value>::type
    set_texture(const device_handle &device, const Drawable &drawable) {
  assert(device);
  device->SetTexture(0, texture_core_access::texture1(drawable).get());
}

template <typename Drawable>
typename std::enable_if<!std::is_base_of<texture, Drawable>::value>::type
    set_texture(const device_handle &device, const Drawable &) {
  assert(device);
  device->SetTexture(0, nullptr);
}
}}}
