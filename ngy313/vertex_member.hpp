#ifndef NGY313_VERTEX_MEMBER_HPP_
#define NGY313_VERTEX_MEMBER_HPP_

#include <cstdint>
#include <array>
#include <ngy313/fwd.hpp>
#include <ngy313/vector.hpp>

namespace ngy313 {
struct position_member {};
struct normal_member {};
struct diffuse_member {};
struct specular_member {};
struct texture_member {};

#if defined(_WIN32)
struct rhw_position_t {
  typedef position_member type;

  rhw_position_t(const vector2 &position)
      : x_(position.get_x()), y_(position.get_y()), z_(0.f), rhw_(1.f) {}

  rhw_position_t &operator +=(const vector2 &position) {
    x_ += position.get_x();
    y_ += position.get_y();
    return *this;
  }

  rhw_position_t &operator -=(const vector2 &position) {
    x_ -= position.get_x();
    y_ -= position.get_y();
    return *this;
  }

  float x_;
  float y_;
  float z_;
  float rhw_;
};

#elif defined(__linux__)
struct rhw_position_t {
  typedef position_member type;

  rhw_position_t(const vector2 &position)
      : x_(position.get_x()), y_(position.get_y()), z_(0.f) {}

  rhw_position_t &operator +=(const vector2 &position) {
    x_ += position.get_x();
    y_ += position.get_y();
    return *this;
  }

  rhw_position_t &operator -=(const vector2 &position) {
    x_ -= position.get_x();
    y_ -= position.get_y();
    return *this;
  }

  float x_;
  float y_;
  float z_;
};
#endif

struct position_t {
  typedef position_member type;

  float x;
  float y;
  float z;
};

struct normal_t {
  typedef normal_member type;

  float x;
  float y;
  float z;
};

#if defined(_WIN32)
struct diffuse_t {
  typedef diffuse_member type;
  
  diffuse_t() : color_(0xFFFFFFFF) {}

  template <typename Wrap>
  diffuse_t(const basic_color_wrap<Wrap> &color) 
      : color_(color.get_color_code()) {}

  std::uint32_t color_;
};

#elif defined(__linux__)
struct diffuse_t {
  typedef diffuse_member type;
  
  diffuse_t() : r_(1.f), g_(1.f), b_(1.f), a_(1.f) {}

  template <typename Wrap>
  diffuse_t(const basic_color_wrap<Wrap> &color)
    : r_(color.red_float()),
      g_(color.green_float()),
      b_(color.blue_float()),
      a_(color.alpha_float()) {}
 
  float r_;
  float g_;
  float b_;
  float a_;
};
#endif

struct specular_t {
  typedef specular_member type;

  std::uint32_t color;
};

struct uv_t {
  float u;
  float v;
};

template <std::size_t Size>
struct texture_t;

template <>
struct texture_t<1> {
  typedef texture_member type;

  explicit texture_t(const vector2 &uv) : texture_array() {
    texture_array[0].u = uv.get_x();
    texture_array[0].v = uv.get_y();
  }

  std::array<uv_t, 1> texture_array;
};

template <>
struct texture_t<2> {
  typedef texture_t type;

  explicit texture_t(const vector2 &uv1,
                     const vector2 &uv2) : texture_array() {
    texture_array[0].u = uv1.get_x();
    texture_array[0].v = uv1.get_y();
    texture_array[1].u = uv2.get_x();
    texture_array[1].v = uv2.get_y();
  }

  std::array<uv_t, 2> texture_array;
};
}

#endif
