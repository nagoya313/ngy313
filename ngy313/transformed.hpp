#ifndef NGY313_TRANSFORMED_HPP_
#define NGY313_TRANSFORMED_HPP_

#include <cstddef>
#include <ngy313/adaptor.hpp>
#include <ngy313/fvf_traits.hpp>
#include <ngy313/vector.hpp>
#include <ngy313/vertex_member.hpp>
#include <ngy313/pipe_operator.hpp>

namespace ngy313 { namespace transformed_adaptor { namespace detail {
template <typename Drawable>
struct adaptor : drawable_adaptor<adaptor<Drawable>, Drawable> {
  explicit adaptor(const Drawable &drawable, 
                   std::size_t at,
                   const vector2 &move)
      : adaptor::drawable_adaptor(drawable), at_(at), move_(move) {}

  template <typename VertexArray>
  void transform(VertexArray &vertex) const {
  	vertex_member_at<position_member>(vertex[at_]).x_ += move_.x();
  	vertex_member_at<position_member>(vertex[at_]).y_ += move_.y();
  }

 private:
  std::size_t at_;
  vector2 move_;
};
}}}

namespace ngy313 { namespace transformed_adaptor {
template <typename Drawable>
detail::adaptor<Drawable> make_transformed(const Drawable &drawable,
                                           size_t at,
                                           const vector2 &move) {
  return detail::adaptor<Drawable>(drawable, at, move);
}

struct transformed : pipe_operator::base<transformed> {
  explicit transformed(std::size_t at,
  		                  const vector2 &move) : at_(at), move_(move) {}

  template <typename Drawable>
  detail::adaptor<Drawable> operator ()(const Drawable &drawable) const {
    return make_transformed(drawable, at_, move_);
  }

 private:
  std::size_t at_;
  vector2 move_;
};
}}

namespace ngy313 {
using transformed_adaptor::make_transformed;
using transformed_adaptor::transformed;
}

#endif
