#pragma once
#include <pstade/oven/at.hpp>
#include "detail/drawable_filter.hpp"
#include "detail/drawable_core_access.hpp"
#include "drawable_adaptor.hpp"

namespace ngy313 {
template <typename Drawable>
class all_vertex_drawable_filter_adaptor;
template <typename Drawable>
class index_vertex_drawable_filter_adaptor;
}

namespace ngy313 { namespace detail {
template <typename Drawable>
struct drawable_filter_adaptor : public Drawable::adaptor_base_type {
};

template <typename Drawable>
class all_vertex_drawable_filter_adaptor_base
    : public drawable_filter_adaptor<Drawable> {
 public:
  explicit all_vertex_drawable_filter_adaptor_base(const Drawable &drawable)
      : vertex_range_(drawable_core_access::vertex_range(drawable)) {}

  template <typename Filter>
  explicit all_vertex_drawable_filter_adaptor_base(const Drawable &drawable,
                                                   const Filter &filter)
      : vertex_range_(drawable_core_access::vertex_range(drawable) | filter) {}

 private:
  friend all_vertex_drawable_filter_adaptor<Drawable>;

  typename Drawable::vertex_range_type vertex_range_;
};

template <typename Drawable>
class index_vertex_drawable_filter_adaptor_base
    : public drawable_filter_adaptor<Drawable> {
 public:
  explicit index_vertex_drawable_filter_adaptor_base(const Drawable &drawable)
      : vertex_array_(drawable_core_access::copy_vertex(drawable)) {}

 private:
  friend index_vertex_drawable_filter_adaptor<Drawable>;

  typename Drawable::vertex_array_type vertex_array_;
};
}}

namespace ngy313 {
template <typename Drawable>
class all_vertex_drawable_filter_adaptor
    : public detail::all_vertex_drawable_filter_adaptor_base<Drawable> {
 public:
  friend drawable_core_access;

  explicit all_vertex_drawable_filter_adaptor(const Drawable &drawable)
      : detail::all_vertex_drawable_filter_adaptor_base<Drawable>(drawable) {}

  template <typename Filter>
  explicit all_vertex_drawable_filter_adaptor(const Drawable &drawable,
                                              const Filter &filter)
      : detail::all_vertex_drawable_filter_adaptor_base<Drawable>(drawable, 
                                                                  filter) {}
 
 private:
  typename Drawable::vertex_range_type vertex_range() const {
    return vertex_range_;
  }
};

template <typename Drawable>
class index_vertex_drawable_filter_adaptor
    : public detail::index_vertex_drawable_filter_adaptor_base<Drawable> {
 public:
  friend drawable_core_access;

  template <typename Filter>
  explicit index_vertex_drawable_filter_adaptor(const Drawable &drawable,
                                                const std::size_t at,
                                                const Filter &filter)
      : detail::index_vertex_drawable_filter_adaptor_base<Drawable>(drawable) {
    filter(pstade::oven::at(vertex_array_, at));
  }
 
 private:
  typename Drawable::vertex_range_type vertex_range() const {
    return pstade::oven::make_range(vertex_array_);
  }
};
}