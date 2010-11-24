#pragma once
#include <functional>
#include <type_traits>
#include <boost/type_traits/function_traits.hpp>
#include <boost/mpl/eval_if.hpp>
#include <pstade/oven/at.hpp>
#include "drawable_core_access.hpp"
#include "drawable.hpp"

namespace ngy313 { namespace detail {
template <typename Signature>
struct copy_argument {
  typedef typename std::remove_const<typename std::remove_reference<typename boost::function_traits<
                                                                        Signature>::arg1_type>::type>::type type;
};

template <typename Drawable, typename Adaptor>
typename std::result_of<Adaptor(const Drawable &)>::type operator |(const Drawable &drawable, const Adaptor &adaptor) {
  return adaptor(drawable);
}

template <template <class> class Adaptor>
struct adaptor_result {
  template <typename Signature>
  struct result {  
    typedef Adaptor<typename detail::copy_argument<Signature>::type> type;
  };
};

struct argument_result {
  template <typename Signature>
  struct result {  
    typedef typename detail::copy_argument<Signature>::type type;
  };
};

template <template <class> class Parent, typename Drawable>
class all_vertex_adaptor_base : public copy_drawable_type<Drawable>::type {
 public:
  explicit all_vertex_adaptor_base(const Drawable &drawable)
      : vertex_range_(drawable_core_access::vertex_range(drawable)) {}

  template <typename Filter>
  all_vertex_adaptor_base(const Drawable &drawable, const Filter &filter)
      : vertex_range_(drawable_core_access::vertex_range(drawable) | filter) {}

 private:
  friend Parent<Drawable>;

  typename Drawable::vertex_range_type vertex_range_;
};

template <template <class> class Parent, typename Drawable>
class index_vertex_adaptor_base : public copy_drawable_type<Drawable>::type {
 public:
  explicit index_vertex_adaptor_base(const Drawable &drawable)
      : vertex_array_(drawable_core_access::copy_vertex(drawable)) {}

 private:
  friend Parent<Drawable>;

  typename Drawable::vertex_array_type vertex_array_;
};

struct image_empty {};

struct meta_image_empty {
  typedef image_empty type;
};

template <typename Drawable>
struct meta_image_type {
  typedef typename Drawable::image_type type;
};

template <typename Drawable>
class all_vertex_adaptor
    : public all_vertex_adaptor_base<all_vertex_adaptor, Drawable>, 
      public boost::mpl::eval_if<has_image_type<Drawable>, meta_image_type<Drawable>, meta_image_empty>::type {
 public:
  template <typename Drawable>
  explicit all_vertex_adaptor(const Drawable &drawable,
                              typename std::enable_if<has_image_type<Drawable>::value>::type * = nullptr)
       : all_vertex_adaptor_base(drawable), Drawable::image_type(drawable) {}

  template <typename Drawable>
  explicit all_vertex_adaptor(const Drawable &drawable,
                              typename std::enable_if<!has_image_type<Drawable>::value>::type * = nullptr)
       : all_vertex_adaptor_base(drawable) {}

  template <typename Drawable, typename Filter>
  all_vertex_adaptor(const Drawable &drawable, 
                     const Filter &filter,
                     typename std::enable_if<has_image_type<Drawable>::value>::type * = nullptr)
       : all_vertex_adaptor_base(drawable, filter), Drawable::image_type(drawable) {}

  template <typename Drawable, typename Filter>
  all_vertex_adaptor(const Drawable &drawable, 
                     const Filter &filter,
                     typename std::enable_if<!has_image_type<Drawable>::value>::type * = nullptr)
       : all_vertex_adaptor_base(drawable, filter) {}
 
 private:
  friend drawable_core_access;

  typename Drawable::vertex_range_type vertex_range() const {
    return vertex_range_;
  }
};

template <typename Drawable>
class index_vertex_adaptor
    : public index_vertex_adaptor_base<index_vertex_adaptor, Drawable>,
      public boost::mpl::eval_if<has_image_type<Drawable>, meta_image_type<Drawable>, meta_image_empty>::type {
 public:
  template <typename Drawable, typename Filter>
  index_vertex_adaptor(const Drawable &drawable,
                       const std::size_t at,
                       const Filter &filter,
                       typename std::enable_if<has_image_type<Drawable>::value>::type * = nullptr)
      : index_vertex_adaptor_base(drawable), Drawable::image_type(drawable) {
    filter(pstade::oven::at(vertex_array_, at));
  }

  template <typename Drawable, typename Filter>
  index_vertex_adaptor(const Drawable &drawable,
                       const std::size_t at,
                       const Filter &filter,
                       typename std::enable_if<!has_image_type<Drawable>::value>::type * = nullptr)
      : index_vertex_adaptor_base(drawable) {
    filter(pstade::oven::at(vertex_array_, at));
  }
 
 private:
  friend drawable_core_access;

  typename Drawable::vertex_range_type vertex_range() const {
    return pstade::oven::make_range(vertex_array_);
  }
};
}}

