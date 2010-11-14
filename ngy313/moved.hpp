#pragma once
#include <pstade/oven/transformed.hpp>
#include "drawable_filter_adaptor.hpp"

namespace ngy313 { namespace detail {
struct move_position : public copy_argument_base {
  move_position(const float move_x, const float move_y)
      : move_x_(move_x), move_y_(move_y) {}

  template <typename Vertex>
  Vertex &operator ()(Vertex &vertex) const {
    member_at<rhw_position_t>(vertex).x += move_x_;
    member_at<rhw_position_t>(vertex).y += move_y_;
    return vertex;
  }

 private:
  const float move_x_;
  const float move_y_;
};

template <typename Drawable>
struct moved_filter : public all_vertex_drawable_filter_adaptor<Drawable> {
  moved_filter(const Drawable &drawable, 
               const float move_x,
               const float move_y)
      : all_vertex_drawable_filter_adaptor(
            drawable, 
            pstade::oven::transformed(move_position(move_x, move_y))) {}
};

template <typename Drawable>
struct moved_at_filter : public index_vertex_drawable_filter_adaptor<Drawable> {
  moved_at_filter(const Drawable &drawable, 
                  const float move_x,
                  const float move_y,
                  const std::size_t at)
      : index_vertex_drawable_filter_adaptor(drawable, 
                                             move_position(move_x, move_y)) {}
};

struct moved : public filtered_base<moved_filter> {
  moved(const float move_x, const float move_y)
      : move_x_(move_x), move_y_(move_y) {}

  template <typename Drawable>
  moved_filter<Drawable> operator ()(const Drawable &drawable) const {
    return moved_filter<Drawable>(drawable, move_x_, move_y_);
  }

 private:
  const float move_x_;
  const float move_y_;
};

struct moved_at : public filtered_base<moved_at_filter> {
  moved_at(const std::size_t at, const float move_x, const float move_y)
      : at_(at), move_x_(move_x), move_y_(move_y) {}

  template <typename Drawable>
  moved_at_filter<Drawable> operator ()(const Drawable &drawable) const {
    return moved_at_filter<Drawable>(drawable, move_x_, move_y_, at_);
  }

 private:
  const std::size_t at_;
  const float move_x_;
  const float move_y_;
};
}}

namespace ngy313 {
using detail::moved;
using detail::moved_at;
}