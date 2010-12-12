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
class vertex_adaptor_base : public copy_drawable_type<Drawable>::type {
 public:
  explicit vertex_adaptor_base(const Drawable &drawable)
      : vertex_(drawable_core_access::copy_vertex(drawable)) {}

  template <typename Filter>
  vertex_adaptor_base(const Drawable &drawable, const Filter &filter)
      : vertex_(drawable_core_access::copy_vertex(drawable, filter)) {}

 private:
  friend Parent<Drawable>;

  typename Drawable::vertex_array_type vertex_;
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
class vertex_adaptor
    : public vertex_adaptor_base<vertex_adaptor, Drawable>, 
      public boost::mpl::eval_if<has_image_type<Drawable>, meta_image_type<Drawable>, meta_image_empty>::type {
 public:
  template <typename Drawable>
  vertex_adaptor(const Drawable &drawable, typename std::enable_if<has_image_type<Drawable>::value>::type * = nullptr)
       : vertex_adaptor_base(drawable), Drawable::image_type(drawable) {}

  template <typename Drawable>
  vertex_adaptor(const Drawable &drawable, typename std::enable_if<!has_image_type<Drawable>::value>::type * = nullptr)
       : vertex_adaptor_base(drawable) {}

  template <typename Drawable, typename Filter>
  vertex_adaptor(const Drawable &drawable, 
                 const Filter &filter,
                 typename std::enable_if<has_image_type<Drawable>::value>::type * = nullptr)
       : vertex_adaptor_base(drawable, filter), Drawable::image_type(drawable) {}

  template <typename Drawable, typename Filter>
  vertex_adaptor(const Drawable &drawable, 
                 const Filter &filter,
                 typename std::enable_if<!has_image_type<Drawable>::value>::type * = nullptr)
       : vertex_adaptor_base(drawable, filter) {}

  template <typename Drawable, typename Filter>
  vertex_adaptor(const Drawable &drawable,
                 const std::size_t at,
                 const Filter &filter,
                 typename std::enable_if<has_image_type<Drawable>::value>::type * = nullptr)
      : vertex_adaptor_base(drawable), Drawable::image_type(drawable) {
    filter(pstade::oven::at(vertex_, at));
  }

  template <typename Drawable, typename Filter>
  vertex_adaptor(const Drawable &drawable,
                 const std::size_t at,
                 const Filter &filter,
                 typename std::enable_if<!has_image_type<Drawable>::value>::type * = nullptr)
      : vertex_adaptor_base(drawable) {
    filter(pstade::oven::at(vertex_, at));
  }
 
 private:
  friend drawable_core_access;

  typename Drawable::vertex_array_type vertex() const {
    return vertex_;
  }
};
}}

