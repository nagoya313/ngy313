#ifndef NGY313_GRAPHIC_VERTEX_MEMBER_HPP_
#define NGY313_GRAPHIC_VERTEX_MEMBER_HPP_
#include <cstdint>
#include <array>
#include <ngy313/platform.hpp>

namespace ngy313 { namespace graphic {
struct position {};
struct normal {};
struct diffuse {};
struct specular {};
struct tex {};

// ˆê•”Œ^‚ª–¢ŽÀ‘•
struct rhw_position_t {
  typedef position type;

  rhw_position_t(const float p1, const float p2) : x(p1), 
                                                   y(p2),
                                                   z(0.f)
#ifdef NGY313_WINDOWS_VERSION
                                                   , rhw(1.f)
#endif
                                                          {}
  float x;
  float y;
  float z;
#ifdef NGY313_WINDOWS_VERSION
  float rhw;
#endif
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

  explicit diffuse_t(const std::uint32_t c) 
#ifdef NGY313_WINDOWS_VERSION
    : color(c) {}
    
  std::uint32_t color;
#else
#ifdef NGY313_LINUX_VERSION
    : r(static_cast<float>(static_cast<std::uint8_t>(c >> 16) / 255.f)),
      g(static_cast<float>(static_cast<std::uint8_t>(c >> 8) / 255.f)),
      b(static_cast<float>(static_cast<std::uint8_t>(c) / 255.f)),
      a(static_cast<float>(static_cast<std::uint8_t>(c >> 24) / 255.f)) {}
     
  float r;
  float g;
  float b;
  float a;
#endif
#endif
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
struct tex_t;

template <>
struct tex_t<1> {
  typedef tex type;

  tex_t(const float u, const float v) : tex_array() {
    tex_array[0].u = u;
    tex_array[0].v = v;
  }

  std::array<uv_t, 1> tex_array;
};

template <>
struct tex_t<2> {
  typedef tex type;

  tex_t(const float u1, const float v1, const float u2, const float v2) : tex_array() {
    tex_array[0].u = u1;
    tex_array[0].v = v1;
    tex_array[1].u = u2;
    tex_array[1].v = v2;
  }

  std::array<uv_t, 2> tex_array;
};
}}

#endif

