#pragma once
#include <type_traits>
#include <boost/mpl/if.hpp>
#include <boost/utility/enable_if.hpp>
#include <pstade/oven/at.hpp>
#include "detail/drawable_adaptor.hpp"
#include "detail/drawable_core_access.hpp"
#include "detail/texture_base.hpp"
#include "drawable_base.hpp"

namespace ngy313 {
template <typename Drawable>
class all_vertex_adaptor;

template <typename Drawable>
class index_vertex_adaptor;
}

namespace ngy313 { namespace detail {
template <typename Drawable>
class all_vertex_adaptor_base : public detail::copy_drawable_type<Drawable>::type {
 public:
  explicit all_vertex_adaptor_base(const Drawable &drawable)
      : vertex_range_(drawable_core_access::vertex_range(drawable)) {}

  template <typename Filter>
  all_vertex_adaptor_base(const Drawable &drawable, const Filter &filter)
      : vertex_range_(drawable_core_access::vertex_range(drawable) | filter) {}

 private:
  friend all_vertex_adaptor<Drawable>;

  typename Drawable::vertex_range_type vertex_range_;
};

template <typename Drawable>
class index_vertex_adaptor_base : public detail::copy_drawable_type<Drawable>::type {
 public:
  explicit index_vertex_adaptor_base(const Drawable &drawable)
      : vertex_array_(drawable_core_access::copy_vertex(drawable)) {}

 private:
  friend index_vertex_adaptor<Drawable>;

  typename Drawable::vertex_array_type vertex_array_;
};
}}

namespace ngy313 {
template <typename Drawable>
class all_vertex_adaptor
    : public detail::all_vertex_adaptor_base<Drawable>, 
      public boost::mpl::if_<detail::has_image_type<Drawable>, detail::texture_base, detail::empty>::type {
 public:
  template <typename Drawable>
  explicit all_vertex_adaptor(const Drawable &drawable,
                              typename boost::enable_if<detail::has_image_type<Drawable>>::type * = nullptr)
       : detail::all_vertex_adaptor_base<Drawable>(drawable), detail::texture_base(drawable) {}

  template <typename Drawable>
  explicit all_vertex_adaptor(const Drawable &drawable,
                              typename boost::disable_if<detail::has_image_type<Drawable>>::type * = nullptr)
       : detail::all_vertex_adaptor_base<Drawable>(drawable) {}

  template <typename Drawable, typename Filter>
  all_vertex_adaptor(const Drawable &drawable, 
                     const Filter &filter,
                     typename boost::enable_if<detail::has_image_type<Drawable>>::type * = nullptr)
       : detail::all_vertex_adaptor_base<Drawable>(drawable, filter), detail::texture_base(drawable) {}

  template <typename Drawable, typename Filter>
  all_vertex_adaptor(const Drawable &drawable, 
                     const Filter &filter,
                     typename boost::disable_if<detail::has_image_type<Drawable>>::type * = nullptr)
       : detail::all_vertex_adaptor_base<Drawable>(drawable, filter) {}
 
 private:
  friend detail::drawable_core_access;

  typename Drawable::vertex_range_type vertex_range() const {
    return vertex_range_;
  }
};

template <typename Drawable>
class index_vertex_adaptor
    : public detail::index_vertex_adaptor_base<Drawable>,
      public boost::mpl::if_<detail::has_image_type<Drawable>, detail::texture_base, detail::empty>::type {
 public:
  template <typename Drawable, typename Filter>
  index_vertex_adaptor(const Drawable &drawable,
                       const std::size_t at,
                       const Filter &filter,
                       typename boost::enable_if<detail::has_image_type<Drawable>>::type * = nullptr)
      : detail::index_vertex_adaptor_base<Drawable>(drawable), detail::texture_base(drawable) {
    filter(pstade::oven::at(vertex_array_, at));
  }

  template <typename Drawable, typename Filter>
  index_vertex_adaptor(const Drawable &drawable,
                       const std::size_t at,
                       const Filter &filter,
                       typename boost::disable_if<detail::has_image_type<Drawable>>::type * = nullptr)
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