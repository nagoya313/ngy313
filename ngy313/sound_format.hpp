#ifndef NGY313_SOUND_FORMAT_HPP_
#define NGY313_SOUND_FORMAT_HPP_

#include <cstdint>
#include <tuple>
#include <vector>
#include <boost/config.hpp>

#if defined(_WIN32)
#include <Xaudio2.h>
#elif defined(__linux__)
#define WAVE_FORMAT_PCM  0
#endif

namespace ngy313 {
BOOST_CONSTEXPR_OR_CONST std::uint16_t kFormatPCM = WAVE_FORMAT_PCM;

struct buffer_format {
  std::uint16_t type;
  std::uint16_t channels;
  std::uint32_t samples_per_sec;
  std::uint32_t avg_bytes_per_sec;
  std::uint16_t block_align;
  std::uint16_t bits_per_sample;
};

typedef std::vector<std::uint8_t> buffer_container_type;

typedef std::tuple<buffer_container_type, buffer_format> sound_tuple;
}

#endif
