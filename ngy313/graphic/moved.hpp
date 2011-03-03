#pragma once
#include <boost/range/algorithm/transform.hpp>
#include <ngy313/graphic/adaptor.hpp>
#include <ngy313/graphic/fvf_traits.hpp>
#include <ngy313/graphic/vertex_member.hpp>
#include <ngy313/utility/pipe_operator.hpp>

namespace ngy313 { namespace graphic {
struct transform_move {
 public:
  transform_move(const float move_x, const float move_y) : move_x_(move_x), move_y_(move_y) {}

  template <typename Vertex>
  Vertex operator ()(Vertex vertex) const {
    vertex_member_at<position>(vertex).x += move_x_;
    vertex_member_at<position>(vertex).y += move_y_;
    return vertex;
  }

 private:
  const float move_x_;
  const float move_y_;
};

template <typename Drawable>
struct moved_adaptor : public drawable_adaptor<moved_adaptor<Drawable>, Drawable> {
  moved_adaptor(const Drawable &drawable, const float move_x, const float move_y)
      : drawable_adaptor<moved_adaptor<Drawable>, Drawable>(drawable), move_(move_x, move_y) {}

 private:
  void transform(typename Drawable::vertex_array_type &vertex) const {
    boost::transform(vertex, vertex.begin(), move_);
  }

  const transform_move move_;

  friend class adaptor_access;
};

template <typename Drawable>
moved_adaptor<Drawable> make_moved(const Drawable &drawable, const float move_x, const float move_y) {
  return moved_adaptor<Drawable>(drawable, move_x, move_y);
}

struct moved : public utility::pipe_operator::base<moved> {
  moved(const float move_x, const float move_y) : move_x_(move_x), move_y_(move_y) {}

  template <typename Drawable>
  moved_adaptor<Drawable> operator ()(const Drawable &drawable) const {
    return make_moved(drawable, move_x_, move_y_);
  }

 private:
  const float move_x_;
  const float move_y_;
};

template <typename Drawable>
struct moved_at_adaptor : public drawable_adaptor<moved_at_adaptor<Drawable>, Drawable> {
  moved_at_adaptor(const Drawable &drawable, const std::size_t at, const float move_x, const float move_y)
      : drawable_adaptor<moved_at_adaptor<Drawable>, Drawable>(drawable), 
        at_(at),
        move_x_(move_x),
        move_y_(move_y) {}

 private:
  void transform(typename Drawable::vertex_array_type &vertex) const {
    vertex_member_at<position>(vertex[at_]).x += move_x_;
    vertex_member_at<position>(vertex[at_]).x += move_y_;
  }

  const std::size_t at_;
  const float move_x_;
  const float move_y_;

  friend class adaptor_access;
};

template <typename Drawable>
moved_at_adaptor<Drawable> make_moved_at(const Drawable &drawable,
                                         const std::size_t at,
                                         const float move_x,
                                         const float move_y) {
  return moved_at_adaptor<Drawable>(drawable, at, move_x, move_y);
}

struct moved_at : public utility::pipe_operator::base<moved_at> {
  moved_at(const std::size_t at, const float move_x, const float move_y) : at_(at), move_x_(move_x), move_y_(move_y) {}

  template <typename Drawable>
  moved_at_adaptor<Drawable> operator ()(const Drawable &drawable) const {
    return make_moved_at(drawable, at_, move_x_, move_y_);
  }

 private:
  const std::size_t at_;
  const float move_x_;
  const float move_y_;
};
}}
