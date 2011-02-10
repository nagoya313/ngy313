#pragma once
#include <cstdint>
#include <vector>

namespace ngy313 { namespace sound {
struct buffer_format {
  std::uint16_t type;
  std::uint16_t channels;
  std::uint32_t samples_per_sec;
  std::uint32_t avg_bytes_per_sec;
  std::uint16_t block_align;
  std::uint16_t bits_per_sample;
};

typedef std::vector<std::uint8_t> buffer_container_type;
}}
