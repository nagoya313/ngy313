#pragma once
#include <cstdint>
#include <pstade/oven/transformed.hpp>
#include "drawable_filter_adaptor.hpp"

namespace ngy313 { namespace detail {
struct transform_color : public copy_argument_base {
  explicit transform_color(const std::uint32_t col) : color_(col) {}

  template <typename Vertex>
  Vertex &operator ()(Vertex &vertex) const {
    member_at<diffuse_t>(vertex).diffuse = color_;
    return vertex;
  }

 private:
  const std::uint32_t color_;
};

template <typename Drawable>
struct colored_filter : public all_vertex_drawable_filter_adaptor<Drawable> {
  colored_filter(const Drawable &drawable, const std::uint32_t col) 
      : all_vertex_drawable_filter_adaptor(
            drawable,
            pstade::oven::transformed(detail::transform_color(col))) {}
};

template <typename Drawable>
struct colored_at_filter
    : public index_vertex_drawable_filter_adaptor<Drawable> {
  friend drawable_core_access;

  colored_at_filter(const Drawable &drawable,
                    const std::uint32_t col,
                    const std::size_t at) 
      : index_vertex_drawable_filter_adaptor(drawable,
                                             at,
                                             transform_color(col)) {}
};

struct colored : public filtered_base<colored_filter> {
  explicit colored(const std::uint32_t col) : color_(col) {}

  template <typename Drawable>
  colored_filter<Drawable> operator ()(const Drawable &drawable) const {
    return colored_filter<Drawable>(drawable, color_);
  }

 private:
  const std::uint32_t color_;
};

struct colored_at : public filtered_base<colored_at_filter> {  
  explicit colored_at(const std::size_t at, const std::uint32_t col)
      : at_(at), color_(col) {}

  template <typename Drawable>
  colored_at_filter<Drawable> operator ()(const Drawable &drawable) const {
    return colored_at_filter<Drawable>(drawable, color_, at_);
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