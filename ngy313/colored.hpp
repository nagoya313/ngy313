#pragma once
#include <cstdint>
#include <pstade/oven/transformed.hpp>
#include "drawable_adaptor.hpp"

namespace ngy313 { namespace detail {
struct transform_color : public argument_result {
  explicit transform_color(const std::uint32_t col) : color_(col) {}

  template <typename Vertex>
  Vertex &operator ()(Vertex &vertex) const {
    vertex_member_at<diffuse_t>(vertex).diffuse = color_;
    return vertex;
  }

 private:
  const std::uint32_t color_;
};

template <typename Drawable>
struct colored_adaptor : public all_vertex_adaptor<Drawable> {
  colored_adaptor(const Drawable &drawable, const std::uint32_t col) 
      : all_vertex_adaptor(drawable, pstade::oven::transformed(detail::transform_color(col))) {}
};

template <typename Drawable>
struct colored_at_adaptor : public index_vertex_adaptor<Drawable> {
  colored_at_adaptor(const Drawable &drawable, const std::uint32_t col, const std::size_t at) 
      : index_vertex_adaptor(drawable, at, transform_color(col)) {}
};

struct colored : public adaptor_result<colored_adaptor> {
  explicit colored(const std::uint32_t col) : color_(col) {}

  template <typename Drawable>
  colored_adaptor<Drawable> operator ()(const Drawable &drawable) const {
    return colored_adaptor<Drawable>(drawable, color_);
  }

 private:
  const std::uint32_t color_;
};

struct colored_at : public adaptor_result<colored_at_adaptor> {  
  explicit colored_at(const std::size_t at, const std::uint32_t col) : at_(at), color_(col) {}

  template <typename Drawable>
  colored_at_adaptor<Drawable> operator ()(const Drawable &drawable) const {
    return colored_at_adaptor<Drawable>(drawable, color_, at_);
  }

 private:
  const std::size_t at_;
  const std::uint32_t color_;
};
}}

namespace ngy313 {
using detail::colored;
using detail::colored_at;
}