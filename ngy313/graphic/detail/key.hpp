#ifndef NGY313_GRAPHIC_DETAIL_KEY_HPP_
#define NGY313_GRAPHIC_DETAIL_KEY_HPP_
#include <boost/fusion/include/map.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/include/size.hpp>
#include <boost/mpl/always.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/same_as.hpp>
#include <boost/mpl/switch.hpp>
#include <boost/mpl/vector.hpp>
#include <ngy313/graphic/fvf_traits.hpp>
#include <ngy313/graphic/texture_access.hpp>

namespace ngy313 { namespace graphic {
class texture;
}}

namespace ngy313 { namespace graphic { namespace detail {
struct drawable_key {};
struct size_key {};
struct count_key {};
struct fvf_key {};
struct primitive_key {};
struct fusion_key {};
struct blend_pair_key {};
struct addressing_tuple_key {};
struct texture_stage_tuple_key {};
struct texture_data_key {};
struct base_point_key {};

template <typename Drawable>
struct drawable_switch_body {
  typedef boost::mpl::vector<
      boost::mpl::pair<boost::mpl::same_as<boost::mpl::void_>,
                       boost::mpl::always<
                           boost::fusion::map<boost::fusion::pair<detail::drawable_key, const Drawable &>>>>,
      boost::mpl::pair<boost::mpl::same_as<tex_t<1>>,
                       boost::mpl::always<
                           boost::fusion::map<boost::fusion::pair<detail::drawable_key, const Drawable &>,
                                              boost::fusion::pair<detail::texture_data_key, const texture &>>>>> type;
};

template <typename Drawable>
struct drawable_switch_element {
  typedef typename fvf_traits<
              typename boost::mpl::at<typename Drawable::list_type, fvf_key>::type>::tex_type type;
};

template <typename Drawable>
struct drawable_fusion {
  typedef typename boost::mpl::switch_<typename drawable_switch_body<Drawable>::type,
                                       typename drawable_switch_element<Drawable>::type>::type type;
};

template <typename Drawable>
struct drawable_switch {
  typedef boost::fusion::result_of::size<typename drawable_fusion<Drawable>::type> type;
};

struct dummy {};

template <typename Drawable>
typename drawable_fusion<Drawable>::type 
    drawable_fusion_init(const Drawable &drawable,
                         typename std::enable_if<drawable_switch<Drawable>::type::value == 1, dummy>::type = dummy()) {
  return typename drawable_fusion<Drawable>::type(drawable);
}

template <typename Drawable>
typename drawable_fusion<Drawable>::type 
    drawable_fusion_init(const Drawable &drawable,
                         typename std::enable_if<drawable_switch<Drawable>::type::value == 2, dummy>::type = dummy()) {
  return typename drawable_fusion<Drawable>::type(drawable, graphic::texture_access::texture1(drawable));
}
}}}

#endif

