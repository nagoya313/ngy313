#pragma once
#include <boost/mpl/if.hpp>
#include <pstade/oven/transformed.hpp>
#include "drawable_adaptor.hpp"
#include "vector.hpp"

namespace ngy313 { namespace detail {
template <std::size_t Dimension>
struct move_position : public argument_result {
  static_assert(Dimension == 2 || Dimension == 3, "");

  typedef typename boost::mpl::if_c<Dimension == 2, vector2, vector3>::type vector_type;
  typedef typename boost::mpl::if_c<Dimension == 2, rhw_position_t, position_t>::type position_type;

  explicit move_position(const vector_type &move) : move_(move) {}

  template <typename Vertex>
  Vertex &operator ()(Vertex &vertex) const {
    vertex_member_at<position_type>(vertex).pos += move_;
    return vertex;
  }

 private:
  const vector_type move_;
};

template <typename Drawable>
struct moved_adaptor : public all_vertex_adaptor<Drawable> {
  template <typename Vector>
  moved_adaptor(const Drawable &drawable, const Vector &move)
      : all_vertex_adaptor(drawable, pstade::oven::transformed(move_position<Vector::dimension_type::value>(move))) {}
};

template <typename Drawable>
struct moved_at_adaptor : public index_vertex_adaptor<Drawable> {
  template <typename Vector>
  moved_at_adaptor(const Drawable &drawable, const Vector &move, const std::size_t at)
      : index_vertex_adaptor(drawable, at, move_position<Vector::dimension_type::value>(move)) {}
};

template <typename Vector>
struct moved_t : public adaptor_result<moved_adaptor> {
  explicit moved_t(const Vector &move) : move_(move) {}

  template <typename Drawable>
  moved_adaptor<Drawable> operator ()(const Drawable &drawable) const {
    return moved_adaptor<Drawable>(drawable, move_);
  }

 private:
  const Vector move_;
};

template <typename Vector>
struct moved_at_t : public adaptor_result<moved_at_adaptor> {
  moved_at_t(const std::size_t at, const Vector &move) : at_(at), move_(move) {}

  template <typename Drawable>
  moved_at_adaptor<Drawable> operator ()(const Drawable &drawable) const {
    return moved_at_adaptor<Drawable>(drawable, move_, at_);
  }

 private:
  const std::size_t at_;
  const Vector move_;
};

template <typename Vector>
moved_t<Vector> moved(const Vector &pos) {
  return moved_t<Vector>(pos);
}

template <typename Vector>
moved_at_t<Vector> moved_at(const std::size_t at, const Vector &pos) {
  return moved_at_t<Vector>(at, pos);
}
}}

namespace ngy313 {
using detail::moved;
using detail::moved_at;
}