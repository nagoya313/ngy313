#ifndef NGY313_GRAPHIC_UV_MOVED_HPP_
#define NGY313_GRAPHIC_UV_MOVED_HPP_
#include <cstddef>
#include <boost/mpl/size_t.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <ngy313/graphic/adaptor.hpp>
#include <ngy313/graphic/fvf_traits.hpp>
#include <ngy313/graphic/vertex_member.hpp>
#include <ngy313/utility/nonsubstitutiable.hpp>
#include <ngy313/utility/pipe_operator.hpp>

namespace ngy313 { namespace graphic {
template <std::size_t Index>
struct transform_uv_move : private utility::nonsubstitutiable {
  transform_uv_move(const float move_u, const float move_v) : move_u_(move_u), move_v_(move_v) {}

  template <typename Vertex>
  Vertex operator ()(Vertex vertex) const {
    vertex_member_at<tex>(vertex).tex_array[Index].u += move_u_;
    vertex_member_at<tex>(vertex).tex_array[Index].v += move_v_;
    return vertex;
  }

 private:
  const float move_u_;
  const float move_v_;
};

template <typename Drawable, std::size_t Index>
struct uv_moved_adaptor : public drawable_adaptor<uv_moved_adaptor<Drawable, Index>, Drawable>,
                          private utility::nonsubstitutiable {
  uv_moved_adaptor(const Drawable &drawable, const float move_u, const float move_v)
      : drawable_adaptor<uv_moved_adaptor<Drawable, Index>, Drawable>(drawable),
        move_(move_u, move_v) {}

 private:
  void transform(typename Drawable::vertex_array_type &vertex) const {
    boost::transform(vertex, vertex.begin(), move_);
  }

  const transform_uv_move<Index> move_;

  friend class adaptor_access;
};

template <std::size_t Index, typename Drawable>
uv_moved_adaptor<Drawable, Index> make_uv_moved(const Drawable &drawable, const float move_u, const float move_v) {
  return uv_moved_adaptor<Drawable, Index>(drawable, move_u, move_v);
}

template <std::size_t Index>
struct uv_moved : public utility::pipe_operator::base<uv_moved<Index>>,
                  private utility::nonsubstitutiable {
  uv_moved(const float move_u, const float move_v) : move_u_(move_u), move_v_(move_v) {}

  template <typename Drawable>
  uv_moved_adaptor<Drawable, Index> operator ()(const Drawable &drawable) const {
    return make_uv_moved<Index>(drawable, move_u_, move_v_);
  }

 private:
  const float move_u_;
  const float move_v_;
};

template <typename Drawable, std::size_t Index>
struct uv_moved_at_adaptor : public drawable_adaptor<uv_moved_at_adaptor<Drawable, Index>, Drawable>,
                             private utility::nonsubstitutiable {
  uv_moved_at_adaptor(const Drawable &drawable, const std::size_t at, const float move_u, const float move_v)
      : uv_moved_at_adaptor::drawable_adaptor(drawable), 
        at_(at),
        move_u_(move_u),
        move_v_(move_v) {}

 private:
  void transform(typename Drawable::vertex_array_type &vertex) const {
    vertex_member_at<tex>(vertex[at_]).tex_array[Index].u += move_u_;
    vertex_member_at<tex>(vertex[at_]).tex_array[Index].v += move_v_;
  }

  const std::size_t at_;
  const float move_u_;
  const float move_v_;

  friend class adaptor_access;
};

template <std::size_t Index, typename Drawable>
uv_moved_at_adaptor<Drawable, Index> make_uv_moved_at(const Drawable &drawable,
                                                      const std::size_t at,
                                                      const float move_u,
                                                      const float move_v) {
  return uv_moved_at_adaptor<Drawable, Index>(drawable, at, move_u, move_v);
}

template <std::size_t Index>
struct uv_moved_at : public utility::pipe_operator::base<uv_moved_at<Index>>,
                     private utility::nonsubstitutiable {
  uv_moved_at(const std::size_t at, const float move_u, const float move_v) : at_(at),
                                                                              move_u_(move_u),
                                                                              move_v_(move_v) {}

  template <typename Drawable>
  uv_moved_at_adaptor<Drawable, Index> operator ()(const Drawable &drawable) const {
    return make_uv_moved_at<Index>(drawable, at_, move_u_, move_v_);
  }

 private:
  const std::size_t at_;
  const float move_u_;
  const float move_v_;
};
}}

#endif
