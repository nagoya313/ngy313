#pragma once
#include <functional>
#include <boost/function_types/parameter_types.hpp>
#include <boost/mpl/front.hpp>

namespace ngy313 { namespace detail {
template <typename Signature>
struct copy_argument {
  typedef typename std::remove_const<
      typename std::remove_reference<
          typename boost::mpl::front<
              typename boost::function_types::parameter_types<
                  Signature>::type>::type>::type>::type type;
};

template <typename Drawable, typename Filter>
typename std::result_of<Filter(const Drawable &)>::type operator |(
    const Drawable &drawable,
    const Filter &filter) {
  return filter(drawable);
}
}}
