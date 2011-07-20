#ifndef NGY313_SOUND_HPP_
#define NGY313_SOUND_HPP_

#include <cstdint>
#include <vector>
#include <ngy313/platform.hpp>

#if defined(NGY313_USE_XAUDIO2)
#include <Xaudio2.h>
#elif defined(NGY313_USE_OPENAL)
#define WAVE_FORMAT_PCM  0
#endif

namespace ngy313 {
const std::uint16_t kFormatPCM = WAVE_FORMAT_PCM;

struct buffer_format {
  std::uint16_t type;
  std::uint16_t channels;
  std::uint32_t samples_per_sec;
  std::uint32_t avg_bytes_per_sec;
  std::uint16_t block_align;
  std::uint16_t bits_per_sample;
};

typedef std::vector<std::uint8_t> buffer_container_type;
}

#endif
