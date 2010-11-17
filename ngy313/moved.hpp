#pragma once
#include <pstade/oven/transformed.hpp>
#include "drawable_adaptor_base.hpp"

namespace ngy313 { namespace detail {
struct move_position : public argument_result {
  move_position(const float move_x, const float move_y) : move_x_(move_x), move_y_(move_y) {}

  template <typename Vertex>
  Vertex &operator ()(Vertex &vertex) const {
    vertex_member_at<rhw_position_t>(vertex).x += move_x_;
    vertex_member_at<rhw_position_t>(vertex).y += move_y_;
    return vertex;
  }

 private:
  const float move_x_;
  const float move_y_;
};

template <typename Drawable>
struct moved_adaptor : public all_vertex_adaptor<Drawable> {
  moved_adaptor(const Drawable &drawable, const float move_x, const float move_y)
      : all_vertex_adaptor(drawable, pstade::oven::transformed(move_position(move_x, move_y))) {}
};

template <typename Drawable>
struct moved_at_adaptor : public index_vertex_adaptor<Drawable> {
  moved_at_adaptor(const Drawable &drawable, const float move_x, const float move_y, const std::size_t at)
      : index_vertex_adaptor(drawable, move_position(move_x, move_y)) {}
};

struct moved : public adaptor_result<moved_adaptor> {
  moved(const float move_x, const float move_y) : move_x_(move_x), move_y_(move_y) {}

  template <typename Drawable>
  moved_adaptor<Drawable> operator ()(const Drawable &drawable) const {
    return moved_adaptor<Drawable>(drawable, move_x_, move_y_);
  }

 private:
  const float move_x_;
  const float move_y_;
};

struct moved_at : public adaptor_result<moved_at_adaptor> {
  moved_at(const std::size_t at, const float move_x, const float move_y) : at_(at), move_x_(move_x), move_y_(move_y) {}

  template <typename Drawable>
  moved_at_adaptor<Drawable> operator ()(const Drawable &drawable) const {
    return moved_at_adaptor<Drawable>(drawable, move_x_, move_y_, at_);
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