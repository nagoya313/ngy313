#ifndef NGY313_GRAPHIC_COLORED_HPP_
#define NGY313_GRAPHIC_COLORED_HPP_
#include <cstdint>
#include <boost/range/algorithm/transform.hpp>
#include <ngy313/graphic/adaptor.hpp>
#include <ngy313/graphic/fvf_traits.hpp>
#include <ngy313/graphic/vertex_member.hpp>
#include <ngy313/utility/nonsubstitutiable.hpp>
#include <ngy313/utility/pipe_operator.hpp>

namespace ngy313 { namespace graphic {
struct transform_color : private utility::nonsubstitutiable {
  explicit transform_color(const std::uint32_t color) : color_(color) {}

  template <typename Vertex>
  Vertex operator ()(Vertex vertex) const {
    vertex_member_at<diffuse>(vertex) = diffuse_t(color_);
    return vertex;
  }

 private:
  const std::uint32_t color_;
};

template <typename Drawable>
struct colored_adaptor : public drawable_adaptor<colored_adaptor<Drawable>, Drawable>,
                         private utility::nonsubstitutiable {
  colored_adaptor(const Drawable &drawable, const std::uint32_t col) 
      : drawable_adaptor<colored_adaptor<Drawable>, Drawable>(drawable), color_(col) {}

 private:
  template <typename Vertex>
  void transform(Vertex &vertex) const {
    boost::transform(vertex, vertex.begin(), color_);
  }

  const transform_color color_;

  friend class adaptor_access;
};

template <typename Drawable>
colored_adaptor<Drawable> make_colored(const Drawable &drawable, const std::uint32_t col) {
  return colored_adaptor<Drawable>(drawable, col);
}

struct colored : public utility::pipe_operator::base<colored>,
                 private utility::nonsubstitutiable {
  explicit colored(const std::uint32_t col) : color_(col) {}

  template <typename Drawable>
  colored_adaptor<Drawable> operator ()(const Drawable &drawable) const {
    return make_colored(drawable, color_);
  }

 private:
  const std::uint32_t color_;
};

template <typename Drawable>
struct colored_at_adaptor : public drawable_adaptor<colored_at_adaptor<Drawable>, Drawable> {
  colored_at_adaptor(const Drawable &drawable, const std::uint32_t col, const std::size_t at) 
      : drawable_adaptor<colored_at_adaptor<Drawable>, Drawable>(drawable), color_(col), at_(at) {}

 private:
  template <typename Vertex>
  void transform(Vertex &vertex) const {
    vertex_member_at<diffuse>(vertex[at_]) = diffuse_t(color_);
  }

  const std::uint32_t color_;
  const std::size_t at_;

  friend class adaptor_access;
};


template <typename Drawable>
colored_at_adaptor<Drawable> make_colored_at(const Drawable &drawable, const std::size_t at, const std::uint32_t col) {
  return colored_at_adaptor<Drawable>(drawable, col, at);
}

struct colored_at : public utility::pipe_operator::base<colored_at>,
                    private utility::nonsubstitutiable {  
  colored_at(const std::size_t at, const std::uint32_t col) : at_(at), color_(col) {}

  template <typename Drawable>
  colored_at_adaptor<Drawable> operator ()(const Drawable &drawable) const {
    return make_colored_at(drawable, at_, color_);
  }

 private:
  const std::size_t at_;
  const std::uint32_t color_;
};
}}

#endif
