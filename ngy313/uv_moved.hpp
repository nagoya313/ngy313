#pragma once
#include <cstddef>
#include <pstade/oven/transformed.hpp>
#include "drawable_adaptor.hpp"

namespace ngy313 { namespace detail {
struct uv_move_position : public argument_result {
  uv_move_position(const float move_x, const float move_y) : move_(move_x, move_y) {}

  template <std::size_t Stage, std::size_t Index, typename Vertex>
  Vertex &operator ()(Vertex &vertex) const {
    vertex_member_at<tex_t<Stage>>(vertex).tex[Index] += move_;
    return vertex;
  }

 private:
  const vector2 move_;
};

template <typename Drawable, std::size_t Stage, std::size_t Index>
struct uv_moved_adaptor : public all_vertex_adaptor<Drawable> {
  static_assert(Stage > Index, "");

  uv_moved_adaptor(const Drawable &drawable, const float move_x, const float move_y)
      : all_vertex_adaptor(drawable, pstade::oven::transformed(uv_move_position<Stage, Index>(move_x, move_y))) {}
};

template <typename Drawable, std::size_t Stage, std::size_t Index>
struct uv_moved_at_adaptor : public index_vertex_adaptor<Drawable> {
  static_assert(Stage > Index, "");

  uv_moved_at_adaptor(const Drawable &drawable, const float move_x, const float move_y, const std::size_t at)
      : index_vertex_adaptor(drawable, uv_move_position<Stage, Index>(move_x, move_y)) {}
};

template <std::size_t Stage, std::size_t Index>
struct uv_moved : public adaptor_result<uv_moved_adaptor> {
  static_assert(Stage > Index, "");

  uv_moved(const float move_x, const float move_y) : move_x_(move_x), move_y_(move_y) {}

  template <typename Drawable>
  uv_moved_adaptor<Drawable> operator ()(const Drawable &drawable) const {
    return uv_moved_adaptor<Drawable, Stage, Index>(drawable, move_x_, move_y_);
  }

 private:
  const float move_x_;
  const float move_y_;
};

template <std::size_t Stage, std::size_t Index>
struct uv_moved_at : public adaptor_result<uv_moved_at_adaptor> {
  static_assert(Stage > Index, "");

  uv_moved_at(const std::size_t at, const float move_x, const float move_y)
      : at_(at), move_x_(move_x), move_y_(move_y) {}

  template <typename Drawable>
  uv_moved_at_adaptor<Drawable> operator ()(const Drawable &drawable) const {
    return uv_moved_at_adaptor<Drawable, Stage, Index>(drawable, move_x_, move_y_, at_);
  }

 private:
  const std::size_t at_;
  const float move_x_;
  const float move_y_;
};
}}

namespace ngy313 {
using detail::uv_moved;
using detail::uv_moved_at;
}