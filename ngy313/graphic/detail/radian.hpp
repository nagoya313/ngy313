#ifndef NGY313_GRAPHIC_DETAIL_RADIAN_HPP_
#define NGY313_GRAPHIC_DETAIL_RADIAN_HPP_
#include <boost/mpl/at.hpp>
#include <ngy313/graphic/detail/key.hpp>

namespace ngy313 { namespace graphic { namespace detail {
const float kPI = 3.141592654f;

template <typename Drawable, int Index>
struct vertex_radian {
  static const float value;
};

template <typename Drawable, int Index>
const float vertex_radian<Drawable, Index>::value = 
    kPI * 2.f * static_cast<float>(Index - 1) / static_cast<float>(boost::mpl::at<
                                                                       typename Drawable::list_type, 
                                                                       detail::count_key>::type::type::value - 2);

template <typename Drawable, int Index>
struct line_vertex_radian {
  static const float value;
};

template <typename Drawable, int Index>
const float line_vertex_radian<Drawable, Index>::value = 
    kPI * 2.f * static_cast<float>(Index) / static_cast<float>(boost::mpl::at<
                                                                   typename Drawable::list_type, 
                                                                   detail::count_key>::type::type::value - 1);
}}}

#endif
