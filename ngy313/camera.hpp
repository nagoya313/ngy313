#pragma once
#include <d3dx9math.h>
#include "window.hpp"
#include "vector.hpp"

namespace ngy313 {
const class camera_t {
 public:
  vector3 sten() const {
    return vector3(0.f, -1.f, 0.f);
  }

  vector3 center() const {
    return vector3(0.f, 0.f, 0.f);
  }

  vector3 view() const {
    return vector3(0.f, 0.f, 1.f);
  }

  vector3 target() const {
    return vector3(0.f, 0.f, 0.f);
  }

  vector3 up() const {
    return vector3(0.f, -1.f, 0.f);
  }

  float zoom() const {
    return D3DX_PI / 4.f;
  }

  float aspect() const {
    return static_cast<float>(window_width()) / static_cast<float>(window_height());
  }

  float angle() const {
    return 0.f;
  }

} camera = {};
}