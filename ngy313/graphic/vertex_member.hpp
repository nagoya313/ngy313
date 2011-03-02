#pragma once
#include <cstdint>
#include <array>

namespace ngy313 { namespace graphic {
struct position {};
struct normal {};
struct diffuse {};
struct specular {};
struct tex {};

// ˆê•”Œ^‚ª–¢ŽÀ‘•
struct rhw_position_t {
  typedef position type;
  float x;
  float y;
  float z;
  float rhw;
};

struct position_t {
  typedef position type;
  float x;
  float y;
  float z;
};

struct normal_t {
  typedef normal type;
  float x;
  float y;
  float z;
};

struct diffuse_t {
  typedef diffuse type;
  std::uint32_t color;
};

struct specular_t {
  typedef specular type;
  std::uint32_t color;
};

struct uv_t {
  float u;
  float v;
};

template <std::size_t Size>
struct tex_t {
  typedef tex type;
  std::array<uv_t, Size> tex_array;
};

struct rhw_position_t_ {
  typedef position type;

  rhw_position_t_(const float p1, const float p2) : x(p1), y(p2), z(0.f), rhw(1.f) {}
  
  float x;
  float y;
  float z;
  float rhw;
};

struct diffuse_t_ {
  typedef diffuse type;

  explicit diffuse_t_(const std::uint32_t c) : color(c) {}

  std::uint32_t color;
};
}}
