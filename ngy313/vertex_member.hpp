#pragma once
#include <cstdint>
#include <array>

namespace ngy313 {
struct rhw_position_t {
  float x;
  float y;
  float z;
  float rhw;
};

struct diffuse_t {
  std::uint32_t diffuse;
};

struct uv_t {
  float u;
  float v;
};

template <std::size_t Size>
struct tex_t {
  std::array<uv_t, Size> tex;
};
}