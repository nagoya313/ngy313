#pragma once
#include <cstdint>
#include <array>
#include "vector.hpp"

namespace ngy313 {
struct position_t {
  vector3 pos;
};

struct rhw_position_t {
  vector2 pos; 
  float z;
  float rhw;
};

struct normal_t {
  vector3 norm;
};

struct diffuse_t {
  std::uint32_t diffuse;
};

struct specular_t {
  std::uint32_t specular;
};

template <std::size_t Size>
struct tex_t {
  std::array<vector2, Size> tex;
};
}