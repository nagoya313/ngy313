#pragma once
#include <cassert>
#include <stdexcept>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>
#include <boost/flyweight.hpp>
#pragma warning(disable: 4512)
#include <boost/flyweight/key_value.hpp>
#pragma warning(default: 4512)
#include <boost/functional/hash.hpp>
#include <boost/noncopyable.hpp>
#include <d3dx9.h>
#include <ngy313/graphic/detail/device.hpp>
#include <ngy313/graphic/detail/singleton.hpp>
#include <ngy313/graphic/fvf_traits.hpp>
#include <ngy313/graphic/vertex_member.hpp>
#include <ngy313/utility/string_piece.hpp>

namespace ngy313 { namespace graphic {
class texture;
struct texture_tag;
class multi_texture;
class text_image;
}}

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
    throw std::runtime_error("画像データメモリからテクスチャの作成に失敗しました");
  }
  return texture_handle(texture);
}

#pragma warning(disable: 4512)

struct texture_key {
  texture_key(const device_handle &dev, const std::string &nam) : device(dev), name(nam) {}

  const device_handle &device;
  std::string name;
};

#pragma warning(default: 4512)

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
  return std::tuple<texture_handle, float, float>(texture_handle(texture), 
                                                  static_cast<float>(image_info.Width), 
                                                  static_cast<float>(image_info.Height));
}

class texture_data : private boost::noncopyable {
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
  return texture_key(device().device(), file_name.string());
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
  friend typename std::enable_if<std::is_base_of<texture_tag, Drawable>::value>::type
    set_texture(const device_handle &device, const Drawable &drawable);
};

template <typename Drawable>
typename std::enable_if<std::is_same<tex_t<1>, typename drawable_switch_element<Drawable>::type>::value>::type
    set_texture(const device_handle &device, const Drawable &drawable) {
  assert(device);
  device->SetTexture(0, texture_core_access::texture1(drawable.tex()).get());
}

template <typename Drawable>
typename std::enable_if<std::is_same<boost::mpl::void_, typename drawable_switch_element<Drawable>::type>::value>::type
    set_texture(const device_handle &device, const Drawable &) {
  assert(device);
  device->SetTexture(0, nullptr);
}
}}}
