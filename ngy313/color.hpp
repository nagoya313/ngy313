#pragma once
#include <cstdint>

namespace ngy313 { namespace detail {
inline
std::uint32_t check_range_color(const float value) {
  return value >= 1.f ? 
             0xFF :
             value <= 0.f ?
                 0x00 :
                 static_cast<std::uint32_t>(value * 255.f + 0.5f);
}
}}

namespace ngy313 {
struct color {
  explicit color(const std::uint32_t code) 
      : r(static_cast<float>(static_cast<std::uint8_t>(code >> 16))), 
        g(static_cast<float>(static_cast<std::uint8_t>(code >> 8))),
        b(static_cast<float>(static_cast<std::uint8_t>(code >> 0))),
        a(static_cast<float>(static_cast<std::uint8_t>(code >> 24))) {}

  color(const float red, 
        const float green, 
        const float blue, 
        const float alpha = 1.f)
      : r(red), 
        g(green),
        b(blue),
        a(alpha) {}

  std::uint32_t color_code() const {
    return (detail::check_range_color(a) << 24) | 
               (detail::check_range_color(r) << 16) |
                   (detail::check_range_color(g) << 8) |
                       detail::check_range_color(b);
  }

  float r;
  float g;
  float b;
  float a;
};
}