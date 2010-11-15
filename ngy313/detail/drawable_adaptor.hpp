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

template <typename Drawable, typename Adaptor>
typename std::result_of<Adaptor(const Drawable &)>::type operator |(
    const Drawable &drawable, const Adaptor &adaptor) {
  return adaptor(drawable);
}
}}

namespace ngy313 {
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
}

