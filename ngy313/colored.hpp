#ifndef NGY313_COLORED_HPP_
#define NGY313_COLORED_HPP_

#include <boost/range/algorithm/transform.hpp>
#include <ngy313/adaptor.hpp>
#include <ngy313/color.hpp>
#include <ngy313/fvf_traits.hpp>
#include <ngy313/vertex_member.hpp>
#include <ngy313/pipe_operator.hpp>

namespace ngy313 { namespace colored_adaptor { namespace detail {
struct transformed {
 public:
  explicit transformed(const color_wrap &color) : color_(color) {}

  template <typename Vertex>
  Vertex operator ()(Vertex vertex) const {
    vertex_member_at<diffuse_member>(vertex) = color_;
    return vertex;
  }

 private:
  color_wrap color_;
};

template <typename Drawable>
struct adaptor : drawable_adaptor<adaptor<Drawable>, Drawable> {
  explicit adaptor(const Drawable &drawable, const color_wrap &color)
      : adaptor::drawable_adaptor(drawable), color_(color) {}

  template <typename VertexArray>
  void transform(VertexArray &vertex) const {
    boost::transform(vertex, vertex.begin(), color_);
  }

 private:
  transformed color_;
};
}}}

namespace ngy313 { namespace colored_adaptor {
template <typename Drawable>
detail::adaptor<Drawable> make_colored(const Drawable &drawable,
		                                   const color_wrap &color) {
  return detail::adaptor<Drawable>(drawable, color);
}

struct colored : pipe_operator::base<colored> {
  explicit colored(const color_wrap &color) : color_(color) {}

  template <typename Drawable>
  detail::adaptor<Drawable> operator ()(const Drawable &drawable) const {
    return make_colored(drawable, color_);
  }

 private:
  color_wrap color_;
};
}}

namespace ngy313 {
using colored_adaptor::make_colored;
using colored_adaptor::colored;
}

#endif
