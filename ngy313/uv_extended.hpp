#ifndef NGY313_UV_EXTENDED_HPP_
#define NGY313_UV_EXTENDED_HPP_

#include <boost/config.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <ngy313/adaptor.hpp>
#include <ngy313/fvf_traits.hpp>
#include <ngy313/vector.hpp>
#include <ngy313/vertex_member.hpp>
#include <ngy313/pipe_operator.hpp>

namespace ngy313 { namespace uv_extended_adaptor { namespace detail {
template <std::size_t Index>
struct transformed {
  explicit transformed(const vector2 &base_point,
                       const vector2 &extend)
      : base_point_(base_point), extend_(extend) {}

  template <typename Vertex>
  Vertex operator ()(Vertex vertex) const {
    vertex_member_at<texture_member>(vertex).texture_array[Index].u = 
        extend_position(vertex_member_at<texture_member>(vertex).texture_array[Index].u,
                        base_point_.get_x(),
                        extend_.get_x());
    vertex_member_at<texture_member>(vertex).texture_array[Index].v = 
        extend_position(vertex_member_at<texture_member>(vertex).texture_array[Index].v, 
                        base_point_.get_y(), 
                        extend_.get_y());
    return vertex;
  }

 private:
  static float extend_position(const float pos, const float base, const float extend) {
    return (pos - base) * extend + base;
  }

  vector2 base_point_;
  vector2 extend_;
};

template <typename Drawable, std::size_t Index>
struct adaptor : drawable_adaptor<adaptor<Drawable, Index>, Drawable> {
  template <typename BasePoint>
  explicit adaptor(const Drawable &drawable, 
                   const BasePoint &base_point,
                   const vector2 &extend)
      : adaptor::drawable_adaptor(drawable), 
        extend_(vector2(base_point.template u<Index>(drawable), 
                        base_point.template v<Index>(drawable)), extend) {}

  template <typename VertexArray>
  void transform(VertexArray &vertex) const {
    boost::transform(vertex, vertex.begin(), extend_);
  }

 private:
  transformed<Index> extend_;
};
}}}

namespace ngy313 { namespace uv_extended_adaptor {
template <std::size_t Index, typename Drawable, typename BasePoint>
detail::adaptor<Drawable, Index> make_uv_extended(const Drawable &drawable,
                                                  const BasePoint &base_point,
                                                  const vector2 &extend) {
  return detail::adaptor<Drawable, Index>(drawable, base_point, extend);
}

template <std::size_t Index, typename BasePoint>
struct uv_extended_t : pipe_operator::base<uv_extended_t<Index, BasePoint>> {
  explicit BOOST_CONSTEXPR uv_extended_t(const BasePoint &base_point,
                                         const vector2 &extend)
      : base_point_(base_point), extend_(extend) {}

  template <typename Drawable>
  detail::adaptor<Drawable, Index> operator ()(const Drawable &drawable) const {
    return make_uv_extended<Index>(drawable, base_point_, extend_);
  }

 private:
  BasePoint base_point_;
  vector2 extend_;
};

template <std::size_t Index, typename BasePoint>
BOOST_CONSTEXPR uv_extended_t<Index, BasePoint> uv_extended(const BasePoint &base_point,
                                                            const vector2 &extend) {
  return uv_extended_t<Index, BasePoint>(base_point, extend);
}
}}

namespace ngy313 {
using uv_extended_adaptor::make_uv_extended;
using uv_extended_adaptor::uv_extended;
}

#endif
