#pragma once
#include <string>
#include <boost/functional/hash.hpp>
#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>
#include "drawable_core_access.hpp"
#include "window_singleton.hpp"
#include "string_piece.hpp"

namespace ngy313 { namespace detail {
struct texture_key {
  const graphic_device_handle &graphic_device;
  std::string texture_name;
};

inline
bool operator ==(const texture_key &lhs, const texture_key &rhs) {
  return lhs.graphic_device == rhs.graphic_device && lhs.texture_name == rhs.texture_name;
}

inline
std::size_t hash_value(const texture_key &key) {
  std::size_t hash = 0;
  boost::hash_combine(hash, key.graphic_device.get());
  boost::hash_combine(hash, key.texture_name);
  return hash;
}

struct texture_core_data {
  texture_handle texture;
  float width;
  float height;
};

inline
texture_core_data create_texture_from_file(const texture_key &key) {
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
  const texture_core_data data = {
    texture_handle(texture, false), static_cast<float>(image_info.Width), static_cast<float>(image_info.Height)
  };
  return data;
}

struct texture_data {
  explicit texture_data(const texture_key &key) {
    const texture_core_data data = create_texture_from_file(key);
    texture = data.texture;
    width = data.width;
    height = data.height;
  }

  texture_handle texture;
  float width;
  float height;
};

inline
texture_key init_key(const string_piece &file_name) {
  const texture_key key = {graphic_device(), file_name.string()};
  return key;
}

typedef boost::flyweights::flyweight<boost::flyweights::key_value<texture_key, texture_data>> texture_type;

class texture_base {
 public:
  typedef texture_base image_type;
  typedef texture_base image1_type;

  explicit texture_base(const texture_handle &texture) : texture1_(texture) {}

 private:
  friend drawable_core_access;

  const texture_handle &texture1() const {
    return texture1_;
  }

  const texture_handle texture1_;
};

class texture2_base {
 public:
  typedef texture2_base image_type;
  typedef texture2_base image2_type;

  texture2_base(const texture_handle &texture1, const texture_handle &texture2) 
      : texture1_(texture1), texture2_(texture2) {}

 private:
  friend drawable_core_access;

  const texture_handle &texture1() const {
    return texture1_;
  }

  const texture_handle &texture2() const {
    return texture2_;
  }

  const texture_handle texture1_;
  const texture_handle texture2_;
};
}}