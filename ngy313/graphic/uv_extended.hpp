#ifndef NGY313_GRAPHIC_UV_EXTENDED_HPP_
#define NGY313_GRAPHIC_UV_EXTENDED_HPP_
#include <boost/mpl/size_t.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <ngy313/graphic/detail/extend_position.hpp>
#include <ngy313/graphic/adaptor.hpp>
#include <ngy313/graphic/fvf_traits.hpp>
#include <ngy313/graphic/shape_position.hpp>
#include <ngy313/graphic/vertex_member.hpp>
#include <ngy313/utility/nonsubstitutiable.hpp>
#include <ngy313/utility/pipe_operator.hpp>

namespace ngy313 { namespace graphic {
template <std::size_t Index>
struct transform_uv_extend : private utility::nonsubstitutiable {
  transform_uv_extend(
      const float base_point_u, const float base_point_v, const float extend_u, const float extend_v) 
      : base_point_u_(base_point_u), base_point_v_(base_point_v), extend_u_(extend_u), extend_v_(extend_v) {}

  template <typename Vertex>
  Vertex operator ()(Vertex vertex) const {
    vertex_member_at<tex>(vertex).tex_array[Index].u = 
        detail::extend_position(vertex_member_at<tex>(vertex).tex_array[Index].u, base_point_u_, extend_u_);
    vertex_member_at<tex>(vertex).tex_array[Index].v = 
        detail::extend_position(vertex_member_at<tex>(vertex).tex_array[Index].v, base_point_v_, extend_v_);
    return vertex;
  }

 private:
  const float base_point_u_;
  const float base_point_v_;
  const float extend_u_;
  const float extend_v_;
};

template <typename Drawable, std::size_t Index>
struct uv_extended_adaptor : public drawable_adaptor<uv_extended_adaptor<Drawable, Index>, Drawable>,
                             private utility::nonsubstitutiable {
  template <typename BasePoint>
  uv_extended_adaptor(
      const Drawable &drawable, const BasePoint &base_point, const float extend_u, const float extend_v)
      : uv_extended_adaptor::drawable_adaptor(drawable), 
        extend_(base_point.template u<Index>(drawable), base_point.template v<Index>(drawable), extend_u, extend_v) {}

 private:
  void transform(typename Drawable::vertex_array_type &vertex) const {
    boost::transform(vertex, vertex.begin(), extend_);
  }

  const transform_uv_extend<Index> extend_;

  friend class adaptor_access;
};

template <std::size_t Index, typename Drawable, typename BasePoint>
uv_extended_adaptor<Drawable, Index> 
    make_uv_extended(const Drawable &drawable, const BasePoint &base_point, const float extend_u, const float extend_v) {
  return uv_extended_adaptor<Drawable, Index>(drawable, base_point, extend_u, extend_v);
}

template <std::size_t Index, typename BasePoint>
struct uv_extended_t : public utility::pipe_operator::base<uv_extended_t<Index, BasePoint>>,
                       private utility::nonsubstitutiable {
  uv_extended_t(const BasePoint &base_point, const float extend_u, const float extend_v)
      : base_point_(base_point), extend_u_(extend_u), extend_v_(extend_v) {}

  template <typename Drawable>
  uv_extended_adaptor<Drawable, Index> operator ()(const Drawable &drawable) const {
    return make_uv_extended<Index>(drawable, base_point_, extend_u_, extend_v_);
  }

 private:
  const BasePoint base_point_;
  const float extend_u_;
  const float extend_v_;
};

template <std::size_t Index, typename BasePoint>
uv_extended_t<Index, BasePoint> 
    uv_extended(const BasePoint &base_point, const float extend_u, const float extend_v) {
  return uv_extended_t<Index, BasePoint>(base_point, extend_u, extend_v);
}
}}

#endif
