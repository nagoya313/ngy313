#pragma once
#include <pstade/oven/at.hpp>
#include "detail/drawable_adaptor.hpp"
#include "detail/drawable_core_access.hpp"
#include "drawable_base.hpp"

namespace ngy313 {
template <typename Drawable, typename Inherit>
class all_vertex_adaptor;

template <typename Drawable>
class index_vertex_adaptor;
}

namespace ngy313 { namespace detail {
template <typename Drawable, typename Inherit>
class all_vertex_adaptor_base : public Inherit::type {
 public:
  explicit all_vertex_adaptor_base(const Drawable &drawable)
      : vertex_range_(drawable_core_access::vertex_range(drawable)) {}

  template <typename Filter>
  all_vertex_adaptor_base(const Drawable &drawable, const Filter &filter)
      : vertex_range_(drawable_core_access::vertex_range(drawable) | filter) {}

 private:
  friend all_vertex_adaptor<Drawable, Inherit>;

  typename Drawable::vertex_range_type vertex_range_;
};

template <typename Drawable>
class index_vertex_adaptor_base 
    : public detail::copy_drawable_type<Drawable>::type {
 public:
  explicit index_vertex_adaptor_base(const Drawable &drawable)
      : vertex_array_(drawable_core_access::copy_vertex(drawable)) {}

 private:
  friend index_vertex_adaptor<Drawable>;

  typename Drawable::vertex_array_type vertex_array_;
};
}}

namespace ngy313 {
template <
    typename Drawable,
    typename Inherit = detail::copy_drawable_type<Drawable>>
class all_vertex_adaptor : public detail::all_vertex_adaptor_base<Drawable,
                                                                  Inherit> {
 public:
  explicit all_vertex_adaptor(const Drawable &drawable)
      : detail::all_vertex_adaptor_base<Drawable, Inherit>(drawable) {}

  template <typename Filter>
  all_vertex_adaptor(const Drawable &drawable, const Filter &filter)
      : detail::all_vertex_adaptor_base<Drawable, Inherit>(drawable, filter) {}
 
 private:
  friend detail::drawable_core_access;

  typename Drawable::vertex_range_type vertex_range() const {
    return vertex_range_;
  }
};

template <typename Drawable>
class index_vertex_adaptor : public detail::index_vertex_adaptor_base<Drawable> {
 public:
  template <typename Filter>
  explicit index_vertex_adaptor(const Drawable &drawable,
                                const std::size_t at,
                                const Filter &filter)
      : detail::index_vertex_adaptor_base<Drawable>(drawable) {
    filter(pstade::oven::at(vertex_array_, at));
  }
 
 private:
  friend detail::drawable_core_access;

  typename Drawable::vertex_range_type vertex_range() const {
    return pstade::oven::make_range(vertex_array_);
  }
};
}