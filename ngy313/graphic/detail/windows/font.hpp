#ifndef NGY313_GRAPHIC_DETAIL_WINDOWS_FONT_HPP_
#define NGY313_GRAPHIC_DETAIL_WINDOWS_FONT_HPP_
#include <cassert>
#include <stdexcept>
#include <string>
#include <boost/bind.hpp>
#include <boost/signals2/trackable.hpp>
#include <boost/noncopyable.hpp>
#include <ngy313/graphic/detail/windows/device.hpp>
#include <ngy313/graphic/detail/graphic.hpp>
#include <ngy313/utility/nonsubstitutiable.hpp>
#include <ngy313/utility/string_piece.hpp>

namespace ngy313 { namespace graphic { namespace detail {
inline
font_handle create_font(const device_handle &device, const int size, const utility::string_piece &name) {
  assert(device);
  LPD3DXFONT font;
  if (FAILED(D3DXCreateFontA(device.get(), 
                             size,
                             0,
                             FW_NORMAL, 
                             1,
                             FALSE,
                             SHIFTJIS_CHARSET,
                             OUT_DEFAULT_PRECIS,
                             DEFAULT_QUALITY,
                             DEFAULT_PITCH | FF_SWISS,
                             name.c_str(),
                             &font))) {
    throw std::runtime_error("ƒtƒHƒ“ƒg‚Ìì¬‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
  }
  return font_handle(font);
}

class font_data : public boost::signals2::trackable, private boost::noncopyable {
 public:
  explicit font_data(const int size, const utility::string_piece &name)
      : size_(size), name_(name.string()), font_(create_font(device().device(), size, name)) {
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

typedef font_data font_type;
}}}

#endif
