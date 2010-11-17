#pragma once
#include <cstdint>
#include <d3dx9math.h>
#include "detail/math_expr.hpp"

namespace ngy313 { namespace expr {
struct color {
  color() : color_() {}

  explicit color(const std::uint32_t code) : color_(code) {}

  color(const float r, const float g, const float b, const float a = 1.f) : color_(r, g, b, a) {}

  operator std::uint32_t() const {
    return color_;
  }

  template <typename Expr>
  explicit color(const Expr &expr)
      : color_(expr.x(), expr.y(), expr.z(), expr.w()) {}

  template <typename Expr>
  color &operator =(const Expr &expr) {
    pos.r = expr.x();
    pos.g = expr.y();
    pos.b = expr.z();
    pos.a = expr.w();
    return *this;
  }

  template <typename Expr>
  color &operator +=(const Expr &expr) {
    pos.r += expr.x();
    pos.g += expr.y();
    pos.b += expr.z();
    pos.a += expr.w();
    return *this;
  }

  template <typename Expr>
  color &operator -=(const Expr &expr) {
    pos.r -= expr.x();
    pos.g -= expr.y();
    pos.b -= expr.z();
    pos.a -= expr.w();
    return *this;
  }

  color &operator *=(const float rhs) {
    color_ *= rhs;
    return *this;
  }

  color &operator /=(const float rhs) {
    color_ /= rhs;
    return *this;
  }

  bool operator ==(const color &rhs) const {
    return (color_ == rhs.color_) != 0;
  }

  bool operator !=(const color &rhs) const {
    return (color_ != rhs.color_) != 0;
  }

  float &r() {
    return color_.r;
  }

  float &g() {
    return color_.g;
  }

  float &b() {
    return color_.b;
  }

  float &a() {
    return color_.a;
  }

  const float &r() const {
    return color_.r;
  }

  const float &g() const {
    return color_.g;
  }

  const float &b() const {
    return color_.b;
  }

  const float &a() const {
    return color_.a;
  }

 private:
  D3DXCOLOR color_;
};
}}

namespace ngy313 {
using expr::color;
}