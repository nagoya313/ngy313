#pragma once
#include <cassert>
#include <cmath>
#include <stdexcept>
#include <string>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <vector>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
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
inline
texture_handle create_texture_from_memory(const device_handle &device, const std::vector<std::uint8_t> &data) {
  assert(device);
  LPDIRECT3DTEXTURE9 texture;
  if (FAILED(D3DXCreateTextureFromFileInMemory(device.get(), data.data(), data.size(), &texture))) {
    throw std::runtime_error("画像データメモリからテクスチャの作成に失敗しました");
  }
  return texture_handle(texture, false);
}

template<typename T>
T reverse_endian(const T p) {
  T t = p;
  std::uint8_t *begin = reinterpret_cast<uint8_t *>(&t);
  std::uint8_t *end = reinterpret_cast<uint8_t *>(&t) + sizeof(T);  
  for (;begin < end; ++begin, --end) {
    uint8_t tmp = *begin;
    *begin = *(end - 1);
    *(end - 1) = tmp;
  }
  return t; 
}

std::pair<float, float> bitmap_size(const std::vector<std::uint8_t> &data) {
  std::int32_t width;
  std::memcpy(&width, &data[18], sizeof(width));
  std::int32_t height;
  std::memcpy(&height, &data[22], sizeof(height));
  return std::make_pair(static_cast<float>(std::abs(width)), static_cast<float>(std::abs(height)));
}

std::pair<float, float> png_size(const std::vector<std::uint8_t> &data) {
  std::int32_t width;
  std::memcpy(&width, &data[16], sizeof(width));
  std::int32_t height;
  std::memcpy(&height, &data[20], sizeof(height));
  return std::make_pair(static_cast<float>(reverse_endian(width)), static_cast<float>(reverse_endian(height)));
}

std::pair<float, float> jpeg_size(const std::vector<std::uint8_t> &data) {
  return std::make_pair(0.f, 0.f);
}

template <typename Loader>
class image_binary {
 public:
  explicit image_binary(const std::string &key) : binary_(Loader()(key)) {
    const std::uint8_t bitmap[] = {0x42, 0x4d};
    const std::uint8_t png[] = {0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a};
    const std::uint8_t jpeg[] = {0xff, 0xd8, 0xff};
    if (!std::memcmp(binary_.data(), bitmap, sizeof(bitmap))) {
      const auto size = bitmap_size(binary_);
      width_ = size.first;
      height_ = size.second;
    } else if (!std::memcmp(binary_.data(), png, sizeof(png))) {
      const auto size = png_size(binary_);
      width_ = size.first;
      height_ = size.second;
    } else if (!std::memcmp(binary_.data(), jpeg, sizeof(jpeg))) {
      const auto size = jpeg_size(binary_);
      width_ = size.first;
      height_ = size.second;
    } else {
      throw std::runtime_error("対応していない画像フォーマットです");
    }
  }

  float width() const {
    return width_;
  }

  float height() const {
    return height_;
  }

  texture_handle texture() const {
    const auto it = texture_map_.find(device().get());
    if (it != texture_map_.end()) {
      return it->second;
    } else {
      const auto it = texture_map_.insert(std::make_pair(device().get(), create_texture_from_memory(device(), binary_)));
      return it.first->second;
    }
  }

 private:
  const std::vector<std::uint8_t> binary_;
  float width_;
  float height_;
  mutable std::unordered_map<device_handle::pointer, texture_handle> texture_map_;
};

struct default_image_loader {
  std::vector<std::uint8_t> operator ()(const std::string &key) const {
    boost::filesystem::ifstream fin(key, std::ios::in | std::ios::binary);
    std::vector<std::uint8_t> v(static_cast<std::size_t>(boost::filesystem::file_size(key)));
    fin.read(reinterpret_cast<char *>(v.data()), v.size());
    return v;
  }
};

typedef boost::flyweights::flyweight<boost::flyweights::key_value<
                                         std::string, 
                                         image_binary<default_image_loader>>> image_binary_type;

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
  const texture_key key = {device().device(), file_name.string()};
  return key;
}

//typedef boost::flyweights::flyweight<boost::flyweights::key_value<std::string, image_binary<default_image_loader>>> texture_type;
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
