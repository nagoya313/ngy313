#ifndef NGY313_DETAIL_DIRECT3D9_COLOR_HPP_
#define NGY313_DETAIL_DIRECT3D9_COLOR_HPP_

#include <cstdint>
#include <boost/config.hpp>
#include <boost/noncopyable.hpp>
#include <ngy313/detail/color.hpp>
#include <ngy313/fwd.hpp>

namespace ngy313 { namespace detail {
struct direct3d9_color : private boost::noncopyable {
	BOOST_STATIC_CONSTEXPR std::uint8_t kAlphaIndex_ = 3;
	BOOST_STATIC_CONSTEXPR std::uint8_t kRedIndex_ = 2;
	BOOST_STATIC_CONSTEXPR std::uint8_t kGreenIndex_ = 1;
	BOOST_STATIC_CONSTEXPR std::uint8_t kBlueIndex_ = 0;

	BOOST_STATIC_CONSTEXPR std::uint8_t kAlphaShift_ = 24;
	BOOST_STATIC_CONSTEXPR std::uint8_t kRedShift_ = 16;
	BOOST_STATIC_CONSTEXPR std::uint8_t kGreenShift_ = 8;
	BOOST_STATIC_CONSTEXPR std::uint8_t kBlueShift_ = 0;

 private:
  direct3d9_color();
};

struct direct3d9_color_wrap {
  explicit direct3d9_color_wrap(std::uint32_t color) {
    color_.code = color;
  }

  template <typename Code>
  explicit direct3d9_color_wrap(const basic_color<Code> &color) {
    color_.code = color.color_code();
  }

  explicit direct3d9_color_wrap(float red,
    		                        float green,
    		                        float blue,
    		                        float alpha) {
  	color_.rgba[direct3d9_color::kRedIndex_] = float_to_uint8(red);
  	color_.rgba[direct3d9_color::kGreenIndex_] = float_to_uint8(green);
  	color_.rgba[direct3d9_color::kBlueIndex_] = float_to_uint8(blue);
  	color_.rgba[direct3d9_color::kAlphaIndex_] = float_to_uint8(alpha);
  }

  std::uint32_t color_code() const {
    return color_.code;
  }

  std::uint8_t red_uint() const {
    return color_.rgba[direct3d9_color::kRedIndex_];
  }

  std::uint8_t green_uint() const {
    return color_.rgba[direct3d9_color::kGreenIndex_];
  }

  std::uint8_t blue_uint() const {
    return color_.rgba[direct3d9_color::kBlueIndex_];
  }

  std::uint8_t alpha_uint() const {
    return color_.rgba[direct3d9_color::kAlphaIndex_];
  }

  float red_float() const {
    return uint8_to_float(color_.rgba[direct3d9_color::kRedIndex_]);
  }

  float green_float() const {
    return uint8_to_float(color_.rgba[direct3d9_color::kGreenIndex_]);
  }

  float blue_float() const {
    return uint8_to_float(color_.rgba[direct3d9_color::kBlueIndex_]);
  }

  float alpha_float() const {
    return uint8_to_float(color_.rgba[direct3d9_color::kAlphaIndex_]);
  }

 private:
  union {
    std::uint32_t code;
    std::uint8_t rgba[4];
  } color_;
};
}}

#endif
