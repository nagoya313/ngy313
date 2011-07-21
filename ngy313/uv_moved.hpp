#ifndef NGY313_UV_MOVED_HPP_
#define NGY313_UV_MOVED_HPP_

#include <cstddef>
#include <boost/mpl/size_t.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <ngy313/adaptor.hpp>
#include <ngy313/fvf_traits.hpp>
#include <ngy313/vertex_member.hpp>
#include <ngy313/vector.hpp>
#include <ngy313/pipe_operator.hpp>

namespace ngy313 { namespace uv_moved_adaptor { namespace detail {
template <std::size_t Index>
struct transformed{
  explicit transformed(const vector2 &move) : move_(move) {}

  template <typename Vertex>
  Vertex operator ()(Vertex vertex) const {
    vertex_member_at<texture_member>(vertex).texture_array[Index].u += move_.get_x();
    vertex_member_at<texture_member>(vertex).texture_array[Index].v += move_.get_y();
    return vertex;
  }

 private:
  vector2 move_;
};

template <typename Drawable, std::size_t Index>
struct adaptor : public drawable_adaptor<adaptor<Drawable, Index>, Drawable> {
  explicit adaptor(const Drawable &drawable, const vector2  &move)
      : adaptor::drawable_adaptor(drawable), move_(move) {}

  void transform(typename Drawable::vertex_array_type &vertex) const {
    boost::transform(vertex, vertex.begin(), move_);
  }

 private:
  transformed<Index> move_;
};
}}}

namespace ngy313 { namespace uv_moved_adaptor {
template <std::size_t Index, typename Drawable>
detail::adaptor<Drawable, Index> make_uv_moved(const Drawable &drawable, const vector2 &move) {
  return detail::adaptor<Drawable, Index>(drawable, move);
}

template <std::size_t Index>
struct uv_moved : public pipe_operator::base<uv_moved<Index>> {
  explicit uv_moved(const vector2 &move) : move_(move) {}

  template <typename Drawable>
  detail::adaptor<Drawable, Index> operator ()(const Drawable &drawable) const {
    return make_uv_moved<Index>(drawable, move_);
  }

 private:
  vector2 move_;
};
}}

namespace ngy313 {
using uv_moved_adaptor::make_uv_moved;
using uv_moved_adaptor::uv_moved;
}

#endif
