#ifndef NGY313_GRAPHIC_DETAIL_WINDOWS_IMAGE_LOADER_HPP_
#define NGY313_GRAPHIC_DETAIL_WINDOWS_IMAGE_LOADER_HPP_
#include <cassert>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>
#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>
#include <boost/functional/hash.hpp>
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

struct texture_key {
  texture_key(const device_handle &dev, const std::string &nam) : device(dev), name(nam) {}

  const device_handle &device;
  std::string name;

 private:
  texture_key &operator =(const texture_key &);
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
std::tuple<texture_handle, int, int> create_texture_from_file(const texture_key &key) {
  assert(key.device);
  LPDIRECT3DTEXTURE9 texture;
  D3DXIMAGE_INFO image_info;
  if (FAILED(D3DXCreateTextureFromFileExA(key.device.get(),
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
    throw std::runtime_error("画像ファイルからのテクスチャの作成に失敗しました");
  }
  return std::tuple<texture_handle, int, int>(texture_handle(texture), image_info.Width, image_info.Height);
}

struct default_texture_reader {
 public:
  std::tuple<texture_handle, int, int> operator ()(const texture_key &key) const {
    return std::tuple<texture_handle, int, int>();
  }
};

class texture_data : private boost::noncopyable {
 public:
  explicit texture_data(const texture_key &key) : data_(create_texture_from_file(key)) {}

  const texture_handle &texture() const {
    return std::get<0>(data_);
  }

  int width() const {
    return std::get<1>(data_);
  }

  int height() const {
    return std::get<2>(data_);
  }

 private:
  const std::tuple<texture_handle, int, int> data_;
};

inline
texture_key init_texture_key(const utility::string_piece &file_name) {
  return texture_key(device().device(), file_name.string());
}

typedef boost::flyweights::flyweight<boost::flyweights::key_value<texture_key, texture_data>> texture_type;
}}}

#endif
