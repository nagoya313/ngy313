#pragma once
#include <cstddef>
#include <pstade/oven/transformed.hpp>
#include "drawable_adaptor.hpp"

namespace ngy313 { namespace detail {
struct uv_move_position : public argument_result {
  uv_move_position(const float move_u, const float move_v) : u_(move_u), v_(move_v) {}

  template <std::size_t Stage, std::size_t Index, typename Vertex>
  Vertex &operator ()(Vertex &vertex) const {
    vertex_member_at<tex_t<Stage>>(vertex).tex[Index].u += u_;
    vertex_member_at<tex_t<Stage>>(vertex).tex[Index].v += v_;
    return vertex;
  }

 private:
  const float u_;
  const float v_;
};

template <typename Drawable, std::size_t Stage, std::size_t Index>
struct uv_moved_adaptor : public vertex_adaptor<Drawable> {
  static_assert(Stage > Index, "");

  uv_moved_adaptor(const Drawable &drawable, const float move_x, const float move_y)
      : vertex_adaptor(drawable, pstade::oven::transformed(uv_move_position<Stage, Index>(move_x, move_y))) {}
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

  uv_moved(const float move_u const float move_v) : move_u_(move_u), move_v_(move_v) {}

  template <typename Drawable>
  uv_moved_adaptor<Drawable> operator ()(const Drawable &drawable) const {
    return uv_moved_adaptor<Drawable, Stage, Index>(drawable, move_u_, move_v_);
  }

 private:
  const float move_u_;
  const float move_v_;
};

template <std::size_t Stage, std::size_t Index>
struct uv_moved_at : public adaptor_result<uv_moved_at_adaptor> {
  static_assert(Stage > Index, "");

  uv_moved_at(const std::size_t at, const float move_u, const float move_v)
      : at_(at), move_u_(move_u), move_v_(move_v) {}

  template <typename Drawable>
  uv_moved_at_adaptor<Drawable> operator ()(const Drawable &drawable) const {
    return uv_moved_at_adaptor<Drawable, Stage, Index>(drawable, move_u_, move_v_, at_);
  }

 private:
  const std::size_t at_;
  const float move_u_;
  const float move_v_;
};
}}

namespace ngy313 {
using detail::uv_moved;
using detail::uv_moved_at;
}