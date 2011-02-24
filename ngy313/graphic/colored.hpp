#pragma once
#include <cstdint>
#include <boost/range/algorithm/transform.hpp>
#include <ngy313/adaptor/adaptor.hpp>
#include <ngy313/graphic/adaptor.hpp>
#include <ngy313/graphic/fvf_traits.hpp>
#include <ngy313/graphic/vertex_member.hpp>

namespace ngy313 { namespace graphic {
#pragma warning(disable: 4512)

struct transform_color {
  explicit transform_color(const std::uint32_t color) : color_(color) {}

  template <typename Vertex>
  Vertex operator ()(Vertex vertex) const {
    vertex_member_at<diffuse>(vertex).color = color_;
    return vertex;
  }

 private:
  const std::uint32_t color_;
};

template <typename Drawable>
struct colored_adaptor : public drawable_adaptor<colored_adaptor<Drawable>, Drawable> {
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

#pragma warning(default: 4512)

template <typename Drawable>
colored_adaptor<Drawable> make_colored(const Drawable &drawable, const std::uint32_t col) {
  return colored_adaptor<Drawable>(drawable, col);
}

#pragma warning(disable: 4512)

struct colored : public adaptor::base<colored> {
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
    vertex_member_at<diffuse>(vertex[at]).color = color_;
  }

  const std::uint32_t color_;
  const std::size_t at_;

  friend class adaptor_access;
};

#pragma warning(default: 4512)

template <typename Drawable>
colored_at_adaptor<Drawable> make_colored_at(const Drawable &drawable, const std::size_t at, const std::uint32_t col) {
  return colored_at_adaptor<Drawable>(drawable, col, at);
}

#pragma warning(disable: 4512)

struct colored_at : public ngy313::adaptor::base<colored_at> {  
  colored_at(const std::size_t at, const std::uint32_t col) : at_(at), color_(col) {}

  template <typename Drawable>
  colored_at_adaptor<Drawable> operator ()(const Drawable &drawable) const {
    return make_colored_at(drawable, color_, at_);
  }

 private:
  const std::size_t at_;
  const std::uint32_t color_;
};

#pragma warning(default: 4512)
}}
