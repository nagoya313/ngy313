#ifndef NGY313_DETAIL_OPENGL_COLOR_HPP_
#define NGY313_DETAIL_OPENGL_COLOR_HPP_

#include <cstdint>
#include <boost/config.hpp>
#include <boost/noncopyable.hpp>
#include <ngy313/detail/color.hpp>
#include <ngy313/fwd.hpp>

namespace ngy313 { namespace detail {
struct opengl_color : private boost::noncopyable {
	BOOST_STATIC_CONSTEXPR std::uint8_t kAlphaIndex_ = 3;
	BOOST_STATIC_CONSTEXPR std::uint8_t kRedIndex_ = 0;
	BOOST_STATIC_CONSTEXPR std::uint8_t kGreenIndex_ = 1;
	BOOST_STATIC_CONSTEXPR std::uint8_t kBlueIndex_ = 2;

	BOOST_STATIC_CONSTEXPR std::uint8_t kAlphaShift_ = 24;
	BOOST_STATIC_CONSTEXPR std::uint8_t kRedShift_ = 0;
	BOOST_STATIC_CONSTEXPR std::uint8_t kGreenShift_ = 8;
	BOOST_STATIC_CONSTEXPR std::uint8_t kBlueShift_ = 16;

  opengl_color() = delete;
};

struct opengl_color_wrap {
  explicit opengl_color_wrap(std::uint32_t color)
      : red_(uint32_to_float(color, opengl_color::kRedShift_)),
        green_(uint32_to_float(color, opengl_color::kGreenShift_)),
        blue_(uint32_to_float(color, opengl_color::kBlueShift_)),
        alpha_(uint32_to_float(color, opengl_color::kAlphaShift_)) {}

  template <typename Code>
  explicit opengl_color_wrap(const basic_color<Code> &color)
      : red_(color.red()),
        green_(color.green()),
        blue_(color.blue()),
        alpha_(color.alpha()) {}

  explicit opengl_color_wrap(float red,
                             float green,
                             float blue,
                             float alpha)
    : red_(red), green_(green), blue_(blue), alpha_(alpha) {}

  std::uint32_t color_code() const {
    return float_to_uint32(alpha_, opengl_color::kAlphaShift_) |
        float_to_uint32(red_, opengl_color::kRedShift_) |
            float_to_uint32(green_, opengl_color::kGreenShift_) |
                float_to_uint32(blue_, opengl_color::kBlueShift_);;
  }

  std::uint8_t red_uint() const {
    return float_to_uint8(red_);
  }

  std::uint8_t green_uint() const {
    return float_to_uint8(green_);
  }

  std::uint8_t blue_uint() const {
    return float_to_uint8(blue_);
  }

  std::uint8_t alpha_uint() const {
    return float_to_uint8(alpha_);
  }

  float red_float() const {
    return red_;
  }

  float green_float() const {
    return green_;
  }

  float blue_float() const {
    return blue_;
  }

  float alpha_float() const {
    return alpha_;
  }

 private:
  float red_;
  float green_;
  float blue_;
  float alpha_;
};
}}

#endif
