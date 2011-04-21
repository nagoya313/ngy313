#ifndef NGY313_GRAPHIC_BASE_POINT_HPP_
#define NGY313_GRAPHIC_BASE_POINT_HPP_
#include <cstddef>
#include <ngy313/graphic/shape_position.hpp>
#include <ngy313/utility/nonsubstitutiable.hpp>

namespace ngy313 { namespace graphic {
// ‚¢‚¸‚êŽOŽŸŒ³‚à‘Î‰ž‚·‚é
struct base_point_set : private utility::nonsubstitutiable {
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
  float u(const Drawable &) const {
    return x_;
  }

  template <std::size_t Index, typename Drawable>
  float v(const Drawable &) const {
    return y_;
  }

 private:
  const float x_;
  const float y_;
};

struct base_point_set_at : private utility::nonsubstitutiable {
  explicit base_point_set_at(const std::size_t at) : at_(at) {}

  template <typename Drawable>
  float x(const Drawable &drawable) const {
    return shape_position::x(drawable, at_);
  }

  template <typename Drawable>
  float y(const Drawable &drawable) const {
    return shape_position::y(drawable, at_);
  }

  template <std::size_t Index, typename Drawable>
  float u(const Drawable &drawable) const {
    return shape_position::u<Index>(drawable, at_);
  }

  template <std::size_t Index, typename Drawable>
  float v(const Drawable &drawable) const {
    return shape_position::v<Index>(drawable, at_);
  }

 private:
  const std::size_t at_;
};

const struct base_point_set_center_t {
  template <typename Drawable>
  float x(const Drawable &drawable) const {
    return shape_center::x(drawable);
  }

  template <typename Drawable>
  float y(const Drawable &drawable) const {
    return shape_center::y(drawable);
  }

  template <std::size_t Index, typename Drawable>
  float u(const Drawable &drawable) const {
    return shape_center_u::u<Index>(drawable);
  }

  template <std::size_t Index, typename Drawable>
  float v(const Drawable &drawable) const {
    return shape_center_v::v<Index>(drawable);
  }

} base_point_set_center = {};
}}

#endif
