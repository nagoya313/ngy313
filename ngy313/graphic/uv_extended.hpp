#pragma once
#include <boost/mpl/size_t.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <ngy313/adaptor/adaptor.hpp>
#include <ngy313/graphic/adaptor.hpp>
#include <ngy313/graphic/fvf_traits.hpp>
#include <ngy313/graphic/shape_position.hpp>
#include <ngy313/graphic/vertex_member.hpp>

namespace ngy313 { namespace graphic {
template <std::size_t Index>
struct transform_uv_extend {
  transform_uv_extend(const float base_point_u, const float base_point_v, const float extend) 
      : base_point_u_(base_point_u), base_point_v_(base_point_v), extend_(extend) {}

  template <typename Vertex>
  Vertex operator ()(Vertex vertex) const {
    vertex_member_at<tex>(vertex).tex_array[Index].u = 
        extend_position(vertex_member_at<tex>(vertex).tex_array[Index].u, base_point_u_, extend_);
    vertex_member_at<tex>(vertex).tex_array[Index].v = 
        extend_position(vertex_member_at<tex>(vertex).tex_array[Index].v, base_point_v_, extend_);
    return vertex;
  }

 private:
  const float base_point_u_;
  const float base_point_v_;
  const float extend_;
};

template <typename Drawable, std::size_t Index>
struct uv_extended_adaptor : public drawable_adaptor<uv_extended_adaptor<Drawable, Index>, Drawable> {
  template <typename BasePoint>
  uv_extended_adaptor(const Drawable &drawable, const BasePoint &base_point, const float extend)
      : drawable_adaptor<extended_adaptor<Drawable>, Drawable>(drawable), 
        extend_(base_point.u<Index>(drawable), base_point.v<Index>(drawable), extend) {}

 private:
  void transform(typename Drawable::vertex_array_type &vertex) const {
    const std::size_t index = Index;
    boost::transform(vertex, vertex.begin(), extend_);
  }

  const transform_uv_extend<Index> extend_;

  friend class adaptor_access;
};

template <std::size_t Index, typename Drawable, typename BasePoint>
uv_extended_adaptor<Drawable, Index> make_uv_extended(const Drawable &drawable,
                                                      const BasePoint &base_point,
                                                      const float extend) { 
  return uv_extended_adaptor<Drawable, Index>(drawable, base_point, extend);
}

template <std::size_t Index, typename BasePoint>
struct uv_extended_t : public adaptor::base<uv_extended_t<Index, BasePoint>> {
  uv_extended_t(const BasePoint &base_point, const float extend) : base_point_(base_point), extend_(extend) {}

  template <typename Drawable>
  uv_extended_adaptor<Drawable, Index> operator ()(const Drawable &drawable) const {
    return make_uv_extended<Index>(drawable, base_point_, extend_);
  }

 private:
  const BasePoint base_point_;
  const float extend_;
};

template <std::size_t Index, typename BasePoint>
uv_extended_t<Index, BasePoint> uv_extended(const BasePoint &base_point, const float extend) {
  return uv_extended_t<Index, BasePoint>(base_point, extend);
}

template <typename Tex, std::size_t Index>
struct transform_uv_extend_one {
  transform_uv_extend_one(const float base_point, const float extend) : base_point_(base_point), extend_(extend) {}

  template <typename Vertex>
  Vertex operator ()(Vertex vertex) const {
    extend_position_selecter<Tex>::transform<Index>(vertex, base_point_, extend_);
    return vertex;
  }

 private:
  const float base_point_;
  const float extend_;
};

template <std::size_t Index, typename Tex, typename Drawable>
struct uv_extended_one_adaptor : public drawable_adaptor<uv_extended_one_adaptor<Index, Drawable, Tex>, Drawable> {
  template <typename BasePoint>
  uv_extended_one_adaptor(const Drawable &drawable, const BasePoint &base_point, const float extend)
      : drawable_adaptor<extended_one_adaptor<Index, Drawable, Position>, Drawable>(drawable),  
        extend_(base_position<Tex>::at<Index>(drawable), extend) {}

 private:
  void transform(typename Drawable::vertex_array_type &vertex) const {
    boost::transform(vertex, vertex.begin(), extend_);
  }

  const transform_uv_extend_one<Tex, Index> extend_;

  friend class adaptor_access;
};

template <std::size_t Index, typename Tex, typename Drawable, typename BasePoint>
uv_extended_one_adaptor<Index, Tex, Drawable> make_uv_extended_one(const Drawable &drawable,
                                                                   const BasePoint &base_point,
                                                                   const float extend) {
  return uv_extended_one_adaptor<Index, Tex, Drawable>(drawable, base_point, extend);
}

template <std::size_t Index, typename Drawable, typename BasePoint>
uv_extended_one_adaptor<Index, tex_u, Drawable> make_uv_extended_u(const Drawable &drawable, 
                                                                   const BasePoint &base_point,
                                                                   const float extend) {
  return make_uv_extended_one<Index, tex_u>(drawable, base_point, extend);
}

template <std::size_t Index, typename Drawable, typename BasePoint>
uv_extended_one_adaptor<Index, tex_v, Drawable> make_uv_extended_v(const Drawable &drawable, 
                                                                   const BasePoint &base_point,
                                                                   const float extend) {
  return make_uv_extended_one<Index, tex_v>(drawable, base_point, extend);
}

template <std::size_t Index, typename BasePoint, typename Tex>
struct uv_extended_one_t : public adaptor::base<uv_extended_one_t<Index, BasePoint, Tex>> {
  uv_extended_one_t(const BasePoint &base_point, const float extend)
      : base_point_(base_point), extend_(extend) {}

  template <typename Drawable>
  uv_extended_one_adaptor<Index, Drawable, Tex> operator ()(const Drawable &drawable) const {
    return make_uv_extended_one<Tex, Index>(drawable, base_point_, extend_);
  }

 private:
  const BasePoint base_point_;
  const float extend_;
};

template <std::size_t Index, typename BasePoint>
uv_extended_one_t<Index, BasePoint, tex_u> uv_extended_u(const BasePoint &base_point, const float extend) {
  return uv_extended_one_t<Index, BasePoint, tex_u>(base_point, extend);
}

template <std::size_t Index, typename BasePoint>
uv_extended_one_t<Index, BasePoint, tex_v> uv_extended_v(const BasePoint &base_point, const float extend) {
  return uv_extended_one_t<Index, BasePoint, tex_v>(base_point, extend);
}

template <std::size_t Index>
struct transform_uv_extend_uv {
  transform_uv_extend_uv(const float base_point_u,
                         const float base_point_v,
                         const float extend_u,
                         const float extend_v) 
      : base_point_u_(base_point_u), base_point_v_(base_point_v), extend_u_(extend_u), extend_v_(extend_v) {}

  template <typename Vertex>
  Vertex operator ()(Vertex vertex) const {
    vertex_member_at<tex>(vertex).tex_array[Index].u = 
        extend_position(vertex_member_at<tex>(vertex).tex_array[Index].u, base_point_u_, extend_u_);
    vertex_member_at<tex>(vertex).tex_array[Index].v = 
        extend_position(vertex_member_at<tex>(vertex).tex_array[Index].v, base_point_v_, extend_v_);
    return vertex;
  }

 private:
  const float base_point_u_;
  const float base_point_v_;
  const float extend_u_;
  const float extend_v_;
};

template <typename Drawable, std::size_t Index>
struct uv_extended_uv_adaptor : public drawable_adaptor<uv_extended_uv_adaptor<Drawable, Index>, Drawable> {
  template <typename BasePoint>
  uv_extended_uv_adaptor(const Drawable &drawable, 
                         const BasePoint &base_point,
                         const float extend_u,
                         const float extend_v)
      : drawable_adaptor<uv_extended_uv_adaptor<Drawable, Index>, Drawable>(drawable), 
        extend_(base_point.u<Index>(drawable), base_point.v<Index>(drawable), extend_u, extend_v) {}

 private:
  void transform(typename Drawable::vertex_array_type &vertex) const {
    const std::size_t index = Index;
    boost::transform(vertex, vertex.begin(), extend_);
  }

  const transform_uv_extend_uv<Index> extend_;

  friend class adaptor_access;
};

template <std::size_t Index, typename Drawable, typename BasePoint>
uv_extended_uv_adaptor<Drawable, Index> make_uv_extended_uv(const Drawable &drawable,
                                                            const BasePoint &base_point, 
                                                            const float extend_u, 
                                                            const float extend_v) {
  return uv_extended_uv_adaptor<Drawable, Index>(drawable, base_point, extend_u, extend_v);
}

template <std::size_t Index, typename BasePoint>
struct uv_extended_uv_t : public adaptor::base<uv_extended_uv_t<Index, BasePoint>> {
  uv_extended_uv_t(const BasePoint &base_point, const float extend_u, const float extend_v)
      : base_point_(base_point), extend_u_(extend_u), extend_v_(extend_v) {}

  template <typename Drawable>
  uv_extended_uv_adaptor<Drawable, Index> operator ()(const Drawable &drawable) const {
    return make_uv_extended_uv<Index>(drawable, base_point_, extend_u_, extend_v_);
  }

 private:
  const BasePoint base_point_;
  const float extend_u_;
  const float extend_v_;
};

template <std::size_t Index, typename BasePoint>
uv_extended_uv_t<Index, BasePoint> uv_extended_uv(const BasePoint &base_point, 
                                                  const float extend_u,
                                                  const float extend_v) {
  return uv_extended_uv_t<Index, BasePoint>(base_point, extend_u, extend_v);
}
}}

// 反転アダプタを定義しておく
