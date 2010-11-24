#pragma once
#include <pstade/oven/transformed.hpp>
#include "drawable_adaptor.hpp"

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

struct move_position3d : public argument_result {
  move_position3d(const float move_x, const float move_y, const float move_z)
      : move_x_(move_x), move_y_(move_y), move_z_(move_z) {}

  template <typename Vertex>
  Vertex &operator ()(Vertex &vertex) const {
    vertex_member_at<position_t>(vertex).x += move_x_;
    vertex_member_at<position_t>(vertex).y += move_y_;
    vertex_member_at<position_t>(vertex).y += move_z_;
    return vertex;
  }

 private:
  const float move_x_;
  const float move_y_;
  const float move_z_;
};

template <typename Drawable>
struct moved_adaptor : public all_vertex_adaptor<Drawable> {
  moved_adaptor(const Drawable &drawable, const float move_x, const float move_y)
      : all_vertex_adaptor(drawable, pstade::oven::transformed(move_position(move_x, move_y))) {}

  moved_adaptor(const Drawable &drawable, const float move_x, const float move_y, const float move_z)
      : all_vertex_adaptor(drawable, pstade::oven::transformed(move_position3d(move_x, move_y, move_z))) {}
};

template <typename Drawable>
struct moved_at_adaptor : public index_vertex_adaptor<Drawable> {
  moved_at_adaptor(const Drawable &drawable, const float move_x, const float move_y, const std::size_t at)
      : index_vertex_adaptor(drawable, at, move_position(move_x, move_y)) {}

  moved_at_adaptor(const Drawable &drawable,
                   const float move_x,
                   const float move_y,
                   const float move_z,
                   const std::size_t at) 
      : index_vertex_adaptor(drawable, at, move_position3d(move_x, move_y, move_z)) {}
};

struct moved2d : public adaptor_result<moved_adaptor> {
  moved2d(const float move_x, const float move_y) : move_x_(move_x), move_y_(move_y) {}

  template <typename Drawable>
  moved_adaptor<Drawable> operator ()(const Drawable &drawable) const {
    return moved_adaptor<Drawable>(drawable, move_x_, move_y_);
  }

 private:
  const float move_x_;
  const float move_y_;
};

struct moved3d : public adaptor_result<moved_adaptor> {
  moved3d(const float move_x, const float move_y, const float move_z)
      : move_x_(move_x), move_y_(move_y), move_z_(move_z) {}

  template <typename Drawable>
  moved_adaptor<Drawable> operator ()(const Drawable &drawable) const {
    return moved_adaptor<Drawable>(drawable, move_x_, move_y_, move_z_);
  }

 private:
  const float move_x_;
  const float move_y_;
  const float move_z_;
};

struct moved_at_2d : public adaptor_result<moved_at_adaptor> {
  moved_at_2d(const std::size_t at, const float move_x, const float move_y)
      : at_(at), move_x_(move_x), move_y_(move_y) {}

  template <typename Drawable>
  moved_at_adaptor<Drawable> operator ()(const Drawable &drawable) const {
    return moved_at_adaptor<Drawable>(drawable, move_x_, move_y_, at_);
  }

 private:
  const std::size_t at_;
  const float move_x_;
  const float move_y_;
};

struct moved_at_3d : public adaptor_result<moved_at_adaptor> {
  moved_at_3d(const std::size_t at, const float move_x, const float move_y, const float move_z) 
      : at_(at), move_x_(move_x), move_y_(move_y), move_z_(move_z) {}

  template <typename Drawable>
  moved_at_adaptor<Drawable> operator ()(const Drawable &drawable) const {
    return moved_at_adaptor<Drawable>(drawable, move_x_, move_y_, move_z_, at_);
  }

 private:
  const std::size_t at_;
  const float move_x_;
  const float move_y_;
  const float move_z_;
};

moved2d moved(const float x, const float y) {
  return moved2d(x, y);
}

moved3d moved(const float x, const float y, const float z) {
  return moved3d(x, y, z);
}

moved_at_2d moved_at(const std::size_t at, const float x, const float y) {
  return moved_at_2d(at, x, y);
}

moved_at_3d moved_at(const std::size_t at, const float x, const float y, const float z) {
  return moved_at_3d(at, x, y, z);
}
}}

namespace ngy313 {
using detail::moved;
using detail::moved_at;
}