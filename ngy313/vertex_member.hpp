#pragma once
#include <cstdint>
#include <array>

namespace ngy313 {
struct position_t {
  float x;
  float y;
  float z;
};

struct rhw_position_t {
  float x;
  float y;
  float z;
  float rhw;
};

struct normal_t {
  float x;
  float y;
  float z;
};

struct diffuse_t {
  std::uint32_t diffuse;
};

struct specular_t {
  std::uint32_t specular;
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