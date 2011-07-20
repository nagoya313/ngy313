#ifndef NGY313_GRADATIONED_HPP_
#define NGY313_GRADATIONED_HPP_

#include <cstddef>
#include <ngy313/adaptor.hpp>
#include <ngy313/color.hpp>
#include <ngy313/fvf_traits.hpp>
#include <ngy313/vertex_member.hpp>
#include <ngy313/pipe_operator.hpp>

namespace ngy313 { namespace gradationed_adaptor { namespace detail {
template <typename Drawable>
struct adaptor : drawable_adaptor<adaptor<Drawable>, Drawable> {
  explicit adaptor(const Drawable &drawable,
  		              std::size_t at,
  		              const color_wrap &color)
      : adaptor::drawable_adaptor(drawable), at_(at), color_(color) {}

  template <typename VertexArray>
  void transform(VertexArray &vertex) const {
    vertex_member_at<diffuse_member>(vertex[at_]) = color_;
  }

 private:
  std::size_t at_;
  color_wrap color_;
};
}}}

namespace ngy313 { namespace gradationed_adaptor {
template <typename Drawable>
detail::adaptor<Drawable> make_gradationed(const Drawable &drawable,
		                                       std::size_t at,
		                                       const color_wrap &color) {
  return detail::adaptor<Drawable>(drawable, at, color);
}

struct gradationed : pipe_operator::base<gradationed> {
  explicit gradationed(std::size_t at,
  		                  const color_wrap &color) : at_(at), color_(color) {}

  template <typename Drawable>
  detail::adaptor<Drawable> operator ()(const Drawable &drawable) const {
    return make_gradationed(drawable, at_, color_);
  }

 private:
  std::size_t at_;
  color_wrap color_;
};
}}

namespace ngy313 {
using gradationed_adaptor::make_gradationed;
using gradationed_adaptor::gradationed;
}

#endif
