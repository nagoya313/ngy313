#pragma once
#include <cstddef>
#include <ngy313/graphic/shape_position.hpp>

namespace ngy313 { namespace graphic {
#pragma warning(disable: 4512)

struct default_base_point {
  template <typename Drawable>
  float x(const Drawable &drawable) const {
    return shape_position<position_x>::at(drawable, 0);
  }

  template <typename Drawable>
  float y(const Drawable &drawable) const {
    return shape_position<position_y>::at(drawable, 0);
  }

  template <std::size_t Index, typename Drawable>
  float u(const Drawable &drawable) const {
    return shape_position<tex_u>::at<Index>(drawable, 0);
  }

  template <std::size_t Index, typename Drawable>
  float v(const Drawable &drawable) const {
    return shape_position<tex_v>::at<Index>(drawable, 0);
  }
};

// いずれ三次元も対応する
struct base_point_set {
  base_point_set(const float x, const float y) : x_(x), y_(y) {}

  template <typename Drawable>
  float x(const Drawable &) const {
    return x_;
  }

  template <typename Drawable>
  float y(const Drawable &) const {
    return y_;
  }

  template <std::size_t Index, typename Drawable>
  float u(const Drawable &drawable) const {
    return x_;
  }

  template <std::size_t Index, typename Drawable>
  float v(const Drawable &drawable) const {
    return y_;
  }

 private:
  const float x_;
  const float y_;
};

struct base_point_set_at {
  explicit base_point_set_at(const std::size_t at) : at_(at) {}

  template <typename Drawable>
  float x(const Drawable &drawable) const {
    return shape_position<position_x>::at(drawable, at_);
  }

  template <typename Drawable>
  float y(const Drawable &drawable) const {
    return shape_position<position_y>::at(drawable, at_);
  }

  template <std::size_t Index, typename Drawable>
  float u(const Drawable &drawable) const {
    return shape_position<tex_u>::at<Index>(drawable, at_);
  }

  template <std::size_t Index, typename Drawable>
  float v(const Drawable &drawable) const {
    return shape_position<tex_v>::at<Index>(drawable, at_);
  }

 private:
  const std::size_t at_;
};

#pragma warning(default: 4512)

const struct base_point_set_center_t {
  template <typename Drawable>
  float x(const Drawable &drawable) const {
    return shape_center_x(drawable);
  }

  template <typename Drawable>
  float y(const Drawable &drawable) const {
    return shape_center_y(drawable);
  }

  template <std::size_t Index, typename Drawable>
  float u(const Drawable &drawable) const {
    return shape_center_u<Index>(drawable);
  }

  template <std::size_t Index, typename Drawable>
  float v(const Drawable &drawable) const {
    return shape_center_v<Index>(drawable);
  }

} base_point_set_center = {};
}}
