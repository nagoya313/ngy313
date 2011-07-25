#ifndef NGY313_DETAIL_COLOR_HPP_
#define NGY313_DETAIL_COLOR_HPP_

#include <cstdint>
#include <algorithm>
#include <boost/config.hpp>

namespace ngy313 { namespace detail {
inline
BOOST_CONSTEXPR float uint8_to_float(std::uint8_t code) {
  return static_cast<float>(code) / 255.f;
}

BOOST_CONSTEXPR float uint32_to_float(std::uint32_t code,
                                      std::uint32_t shift) {
  return static_cast<float>(
             static_cast<std::uint8_t>(code >> shift)) / 255.f;
}

inline
BOOST_CONSTEXPR std::uint8_t float_to_uint8(float f) {
  return f >= 1.f ?
         0xFF :
         f <= 0.f ?
         0x00 :
         static_cast<std::uint8_t>(f * 255.f + 0.5f);
}

inline
BOOST_CONSTEXPR std::uint32_t float_to_uint32(float f,
                                              std::uint32_t shift) {
  return static_cast<std::uint32_t>(
            f >= 1.f ?
            0xFF :
            f <= 0.f ?
            0x00 :
            static_cast<std::uint32_t>(f * 255.f + 0.5f)) << shift;
}

inline
float limit(float value) {
  return std::max(std::min(value, 1.f), 0.f);
} 
}}

#endif
