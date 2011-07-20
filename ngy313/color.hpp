#ifndef NGY313_COLOR_HPP_
#define NGY313_COLOR_HPP_

#include <cstdint>
#include <algorithm>
#include <boost/config.hpp>
#include <boost/operators.hpp>
#include <ngy313/detail/color.hpp>

#if defined(_WIN32)
#include <ngy313/detail/direct3d9_color.hpp>
#elif defined(__linux__)
#include <ngy313/detail/opengl_color.hpp>
#endif

namespace ngy313 {
typedef std::uint32_t std::uint32_t;

template <typename Color>
class basic_color : boost::equality_comparable<basic_color<Color>>,
                    boost::addable<basic_color<Color>>,
                    boost::subtractable<basic_color<Color>>,
                    boost::dividable2<basic_color<Color>, float>,
                    boost::multipliable2<basic_color<Color>, float> {
 public:
  explicit BOOST_CONSTEXPR basic_color(std::uint32_t code)
      : red_(detail::uint32_to_float(code, Color::kRedShift_)),
        green_(detail::uint32_to_float(code, Color::kRedShift_)),
        blue_(detail::uint32_to_float(code, Color::kBlueShift_)),
        alpha_(detail::uint32_to_float(code, Color::kAlphaShift_)) {}
  
  BOOST_CONSTEXPR basic_color(float red,
                              float green,
                              float blue)
      : red_(red), green_(green), blue_(blue), alpha_(1.f) {}
  
  BOOST_CONSTEXPR basic_color(float red,
                              float green,
                              float blue,
                              float alpha)
      : red_(red), green_(green), blue_(blue), alpha_(alpha) {}

  void set_red(float red) {
    red_ = red;
  }

  void set_green(float green) {
    green_ = green;
  }

  void set_blue(float blue) {
    blue_ = blue;
  }

  void set_alpha(float alpha) {
    alpha_ = alpha;
  }
  
  BOOST_CONSTEXPR float get_red() const {
    return red_;
  }
  
  BOOST_CONSTEXPR float get_green() const {
    return green_;
  }
  
  BOOST_CONSTEXPR float get_blue() const {
    return blue_;
  }
  
  BOOST_CONSTEXPR float get_alpha() const {
    return alpha_;
  }
  
  BOOST_CONSTEXPR std::uint32_t get_color_code() const {
    return detail::float_to_uint32(alpha_, Color::kAlphaShift_) |
               detail::float_to_uint32(red_, Color::kRedShift_) |
                   detail::float_to_uint32(green_, Color::kGreenShift_) |
                       detail::float_to_uint32(blue_, Color::kBlueShift_);
  }

  basic_color &operator +=(const basic_color &rhs) {
    red_ = std::max(std::min(red_ + rhs.red_, 1.f), 0.f);
    green_ = std::max(std::min(green_ + rhs.green_, 1.f), 0.f);
    blue_ = std::max(std::min(blue_ + rhs.blue_, 1.f), 0.f);
    alpha_ = std::max(std::min(alpha_ + rhs.alpha_, 1.f), 0.f);
    return *this;
  }

  basic_color &operator -=(const basic_color &rhs) {
    red_ = std::max(std::min(red_ - rhs.red_, 1.f), 0.f);
    green_ = std::max(std::min(green_ - rhs.green_, 1.f), 0.f);
    blue_ = std::max(std::min(blue_ - rhs.blue_, 1.f), 0.f);
    alpha_ = std::max(std::min(alpha_ - rhs.alpha_, 1.f), 0.f);
    return *this;
  }

  basic_color &operator *=(float rhs) {
    red_ = std::max(std::min(red_ * rhs, 1.f), 0.f);
    green_ = std::max(std::min(green_ * rhs, 1.f), 0.f);
    blue_ = std::max(std::min(blue_ * rhs, 1.f), 0.f);
    alpha_ = std::max(std::min(alpha_ * rhs, 1.f), 0.f);
    return *this;
  }

  basic_color &operator /=(float rhs) {
    red_ = std::max(std::min(red_ / rhs, 1.f), 0.f);
    green_ = std::max(std::min(green_ / rhs, 1.f), 0.f);
    blue_ = std::max(std::min(blue_ / rhs, 1.f), 0.f);
    alpha_ = std::max(std::min(alpha_ / rhs, 1.f), 0.f);
    return *this;
  }

 private:
  float red_;
  float green_;
  float blue_;
  float alpha_;
};

template <typename Color>
bool operator ==(const basic_color<Color> &lhs,
                 const basic_color<Color> &rhs) {
  return lhs.red() == rhs.red()
             && lhs.green() == rhs.green()
                 && lhs.blue() == rhs.blue()
                     && lhs.alpha() == rhs.alpha();
}

#if defined(_WIN32)
typedef basic_color<detail::direct3d9_color> color;
#elif defined(__linux__)
typedef basic_color<detail::opengl_color> color;
#endif

template <typename Wrap>
struct basic_color_wrap {
  basic_color_wrap(std::uint32_t color) : wrap_(color) {}

  template <typename Code>
  basic_color_wrap(const basic_color<Code> &color) : wrap_(color) {}

  basic_color_wrap(float red,
    		            float green,
    		            float blue)
      : wrap_(red, green, blue, 1.f) {}

  basic_color_wrap(float red,
                   float green,
                   float blue,
                   float alpha)
      : wrap_(red, green ,blue, alpha) {}

  std::uint32_t get_color_code() const {
    return wrap_.color_code();
  }

  std::uint8_t get_red_uint() const {
    return wrap_.red_uint();
  }
  
  std::uint8_t get_green_uint() const {
    return wrap_.green_uint();
  }
  
  std::uint8_t get_blue_uint() const {
    return wrap_.blue_uint();
  }
  
  std::uint8_t get_alpha_uint() const {
    return wrap_.alpha_uint();
  }

  float get_red_float() const {
    return wrap_.red_float();
  }
  
  float get_green_float() const {
    return wrap_.green_float();
  }
  
  float get_blue_float() const {
    return wrap_.blue_float();
  }
  
  float get_alpha_float() const {
    return wrap_.alpha_float();
  }

 private:
  Wrap wrap_;
};

#if defined(_WIN32)
typedef basic_color_wrap<detail::direct3d9_color_wrap> color_wrap;
#elif defined(__linux__)
typedef basic_color_wrap<detail::opengl_color_wrap> color_wrap;
#endif

BOOST_CONSTEXPR_OR_CONST std::uint32_t kClear = 0x00000000;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kBlack = 0xFF000000;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kSkyBlue = 0xFF87CEEB;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kKhaki = 0xFFF0E68C;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kNavy = 0xFF000080;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kLightSkyBlue = 0xFF87CEFA;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kAliceBlue = 0xFFF0F8FF;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kDarkBlue = 0xFF00008B;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kBlueViolet = 0xFF8A2BE2;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kHoneydew = 0xFFF0FFF0;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kMediumBlue = 0xFF0000CD;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kDarkRed = 0xFF8B0000;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kAzure = 0xFFF0FFFF;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kBlue = 0xFF0000FF;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kDarkMagenta = 0xFF8B008B;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kSandyBrown = 0xFFF4A460;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kDarkGreen = 0xFF006400;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kSaddleBrown = 0xFF8B4513;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kWheat = 0xFFF5DEB3;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kGreen = 0xFF008000;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kDarkSeaGreen = 0xFF8FBC8F;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kBeige = 0xFFF5F5DC;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kTeal = 0xFF008080;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kLightGreen = 0xFF90EE90;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kWhiteSmoke = 0xFFF5F5F5;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kDarkCyan = 0xFF008B8B;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kMediumPurple = 0xFF9370DB;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kMintCream = 0xFFF5FFFA;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kDeepSkyBlue = 0xFF00BFFF;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kDarkViolet = 0xFF9400D3;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kGhostWhite = 0xFFF8F8FF;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kDarkTurquoise = 0xFF00CED1;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kPaleGreen = 0xFF98FB98;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kSalmon = 0xFFFA8072;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kMediumSpringGreen = 0xFF00FA9A;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kDarkOrchid = 0xFF9932CC;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kAntiqueWhite = 0xFFFAEBD7;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kLime = 0xFF00FF00;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kYellowGreen = 0xFF9ACD32;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kLinen = 0xFFFAF0E6;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kSpringGreen = 0xFF00FF7F;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kSienna = 0xFFA0522D;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kLightGoldenRodYellow = 0xFFFAFAD2;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kAqua = 0xFF00FFFF;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kBrown = 0xFFA52A2A;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kOldlace = 0xFFFDF5E6;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kCyan = 0xFF00FFFF;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kDarkGray = 0xFFA9A9A9;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kRed = 0xFFFF0000;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kMidnightBlue = 0xFF191970;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kLightBlue = 0xFFADD8E6;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kFuchsia = 0xFFFF00FF;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kDodgerBlue = 0xFF1E90FF;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kGreenYellow = 0xFFADFF2F;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kMagenta = 0xFFFF00FF;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kLightSeaGreen = 0xFF20B2AA;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kPaleTurquoise = 0xFFAFEEEE;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kDeepPink = 0xFFFF1493;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kForestGreen = 0xFF228B22;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kLightSteelBlue = 0xFFB0C4DE;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kOrangeRed = 0xFFFF4500;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kSeaGreen = 0xFF2E8B57;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kPowderBlue = 0xFFB0E0E6;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kTomato = 0xFFFF6347;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kDarksLateGray = 0xFF2F4F4F;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kFirebrick = 0xFFB22222;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kHotPink = 0xFFFF69B4;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kLimeGreen = 0xFF32CD32;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kDarkGoldenrod = 0xFFB8860B;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kCoral = 0xFFFF7F50;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kMediumSeaGreen = 0xFF3CB371;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kMediumOrchid = 0xFFBA55D3;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kDarkOrange = 0xFFFF8C00;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kTurquoise = 0xFF40E0D0;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kRosyBrown = 0xFFBC8F8F;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kLightSalmon = 0xFFFFA07A;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kRoyalBlue = 0xFF4169E1;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kDarkKhaki = 0xFFBDB76B;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kOrange = 0xFFFFA500;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kSteelBlue = 0xFF4682B4;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kSilver = 0xFFC0C0C0;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kLightPink = 0xFFFFB6C1;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kDarksLateBlue = 0xFF483D8B;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kMediumVioletRed = 0xFFC71585;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kPink = 0xFFFFC0CB;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kMediumTurquoise = 0xFF48D1CC;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kIndianRed = 0xFFCD5C5C;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kGold = 0xFFFFD700;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kIndigo = 0xFF4B0082;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kPeru = 0xFFCD853F;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kPeachPuff = 0xFFFFDAB9;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kDarkOliveGreen = 0xFF556B2F;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kChocolate = 0xFFD2691E;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kNavajoWhite = 0xFFFFDEAD;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kCadetBlue = 0xFF5F9EA0;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kTan = 0xFFD2B48C;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kMoccasin = 0xFFFFE4B5;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kCornFlowerBlue = 0xFF6495ED;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kLightGrey = 0xFFD3D3D3;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kBisque = 0xFFFFE4C4;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kMediumAquamarine = 0xFF66CDAA;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kThistle = 0xFFD8BFD8;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kMistyRose = 0xFFFFE4E1;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kDimGray = 0xFF696969;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kOrchid = 0xFFDA70D6;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kBlancheDalmond = 0xFFFFEBCD;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kSlateBlue = 0xFF6A5ACD;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kGoldenRod = 0xFFDAA520;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kPapayawhip = 0xFFFFEFD5;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kOliveDrab = 0xFF6B8E23;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kPaleVioletRed = 0xFFDB7093;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kLavenderBlush = 0xFFFFF0F5;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kSlateGray = 0xFF708090;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kCrimson = 0xFFDC143C;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kSeaShell = 0xFFFFF5EE;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kLightSlateGray = 0xFF778899;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kGainsBoro = 0xFFDCDCDC;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kCornSilk = 0xFFFFF8DC;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kMediumSlateBlue = 0xFF7B68EE;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kPlum = 0xFFDDA0DD;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kLemonChiffon = 0xFFFFFACD;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kLawnGreen = 0xFF7CFC00;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kBurlyWood = 0xFFDEB887;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kFloralWhite = 0xFFFFFAF0;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kChartreuse = 0xFF7FFF00;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kLightCyan = 0xFFE0FFFF;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kSnow = 0xFFFFFAFA;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kAquamarine = 0xFF7FFFD4;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kLavender = 0xFFE6E6FA;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kYellow = 0xFFFFFF00;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kMaroon = 0xFF800000;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kDarkSalmon = 0xFFE9967A;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kLightYellow = 0xFFFFFFE0;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kPurple = 0xFF800080;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kViolet = 0xFFEE82EE;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kIvory = 0xFFFFFFF0;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kOlive = 0xFF808000;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kPaleGoldenRod = 0xFFEEE8AA;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kWhite = 0xFFFFFFFF;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kGray = 0xFF808080;
BOOST_CONSTEXPR_OR_CONST std::uint32_t kLightCoral = 0xFFF08080;
}

#endif
