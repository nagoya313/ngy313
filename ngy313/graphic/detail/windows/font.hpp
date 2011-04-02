#pragma once
#include <cassert>
#include <stdexcept>
#include <string>
#include <boost/bind.hpp>
#include <boost/signals2/trackable.hpp>
#include <boost/noncopyable.hpp>
#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>
#include <boost/functional/hash.hpp>
#include <ngy313/graphic/detail/device.hpp>
#include <ngy313/graphic/detail/singleton.hpp>
#include <ngy313/utility/string_piece.hpp>

namespace ngy313 { namespace graphic { namespace detail {
struct font_key {
  font_key(const device_handle &dev, const int siz, const std::string &nam) : device(dev), size(siz), name(nam) {}

  const device_handle &device;
  int size;
  std::string name;

 private:
   font_key &operator =(const font_key &);
};

inline
bool operator ==(const font_key &lhs, const font_key &rhs) {
  return lhs.device == rhs.device && lhs.size == rhs.size && lhs.name == rhs.name;
}

inline
std::size_t hash_value(const font_key &key) {
  std::size_t hash = 0;
  boost::hash_combine(hash, key.device.get());
  boost::hash_combine(hash, key.size);
  boost::hash_combine(hash, key.name);
  return hash;
}

inline
font_handle create_font(const font_key &key) {
  assert(key.device);
  LPD3DXFONT ft;
  if (FAILED(D3DXCreateFont(key.device.get(), 
                            key.size,
                            0,
                            FW_NORMAL, 
                            1,
                            FALSE,
                            SHIFTJIS_CHARSET,
                            OUT_DEFAULT_PRECIS,
                            DEFAULT_QUALITY,
                            DEFAULT_PITCH | FF_SWISS,
                            key.name.c_str(),
                            &ft))) {
    throw std::runtime_error("ƒtƒHƒ“ƒg‚Ìì¬‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
  }
  return font_handle(ft);
}

class font_data : public boost::signals2::trackable, private boost::noncopyable {
 public:
  explicit font_data(const font_key &key) : size_(key.size), name_(key.name), font_(create_font(key)) {
    assert(device().device());
    device().before_reset.connect(boost::bind(&font_data::release, this));
    device().after_reset.connect(boost::bind(&font_data::reset, this));
  }

  int size() const {
    return size_;
  }

  std::string name() const {
    return name_;
  }

  const font_handle &font() const {
    return font_;
  }

 private:
  void release() {
    assert(font_);
    font_->OnLostDevice();
  }

  void reset() {
    assert(font_);
    font_->OnResetDevice();
  }

  const int size_;
  const std::string name_;
  const font_handle font_;
};

inline
font_key init_font_key(const int size, const utility::string_piece &font_name) {
  return font_key(device().device(), size, font_name.string());
}

typedef boost::flyweights::flyweight<boost::flyweights::key_value<font_key, font_data>> font_type;
}}}
