#pragma once
#include <functional>
#include <boost/type_traits/function_traits.hpp>

namespace ngy313 { namespace detail {
template <typename Signature>
struct copy_argument {
  typedef typename std::remove_const<
      typename std::remove_reference<
          typename boost::function_traits<
              Signature>::arg1_type>::type>::type type;
};

template <typename Drawable, typename Filter>
typename std::result_of<Filter(const Drawable &)>::type operator |(
    const Drawable &drawable,
    const Filter &filter) {
  return filter(drawable);
}
}}

namespace ngy313 {
template <template <class T> class Filter>
struct filtered_base {
  template <typename Signature>
  struct result {  
    typedef Filter<typename detail::copy_argument<Signature>::type> type;
  };
};

struct copy_argument_base {
  template <typename Signature>
  struct result {  
    typedef typename detail::copy_argument<Signature>::type type;
  };
};
}

