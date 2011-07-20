#ifndef NGY313_MOVED_HPP_
#define NGY313_MOVED_HPP_

#include <boost/range/algorithm/transform.hpp>
#include <ngy313/adaptor.hpp>
#include <ngy313/fvf_traits.hpp>
#include <ngy313/vector.hpp>
#include <ngy313/vertex_member.hpp>
#include <ngy313/pipe_operator.hpp>

namespace ngy313 { namespace moved_adaptor { namespace detail {
struct transformed {
 public:
  explicit transformed(const vector2 &move) : move_(move) {}

  template <typename Vertex>
  Vertex operator ()(Vertex vertex) const {
    vertex_member_at<position_member>(vertex).x_ += move_.x();
    vertex_member_at<position_member>(vertex).y_ += move_.y();
    return vertex;
  }

 private:
  vector2 move_;
};

template <typename Drawable>
struct adaptor : drawable_adaptor<adaptor<Drawable>, Drawable> {
  explicit adaptor(const Drawable &drawable, const vector2 &move)
      : adaptor::drawable_adaptor(drawable), move_(move) {}

  template <typename VertexArray>
  void transform(VertexArray &vertex) const {
    boost::transform(vertex, vertex.begin(), move_);
  }

 private:
  transformed move_;
};
}}}

namespace ngy313 { namespace moved_adaptor {
template <typename Drawable>
detail::adaptor<Drawable> make_moved(const Drawable &drawable,
		                                  const vector2 &move) {
  return detail::adaptor<Drawable>(drawable, move);
}

struct moved : pipe_operator::base<moved> {
  explicit moved(const vector2 &move) : move_(move) {}

  template <typename Drawable>
  detail::adaptor<Drawable> operator ()(const Drawable &drawable) const {
    return make_moved(drawable, move_);
  }

 private:
  vector2 move_;
};
}}

namespace ngy313 {
using moved_adaptor::make_moved;
using moved_adaptor::moved;
}

#endif
