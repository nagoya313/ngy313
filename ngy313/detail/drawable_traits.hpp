#ifndef NGY313_DETAIL_DRAWABLE_TRAITS_HPP_
#define NGY313_DETAIL_DRAWABLE_TRAITS_HPP_

#include <boost/fusion/include/map.hpp>
#include <boost/fusion/include/pair.hpp>
#include <boost/mpl/always.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/same_as.hpp>
#include <boost/mpl/switch.hpp>
#include <boost/mpl/vector.hpp>
#include <ngy313/texture.hpp>
#include <ngy313/detail/drawable_traits_key.hpp>

namespace ngy313 { namespace detail {
template <typename Drawable>
struct drawable_switch_body {
  typedef boost::mpl::vector<
      boost::mpl::pair<
          boost::mpl::same_as<boost::mpl::void_>,
          boost::mpl::always<
              boost::fusion::map<
                  boost::fusion::pair<drawable_key,
                                      const Drawable &>>>>,
      boost::mpl::pair<
          boost::mpl::same_as<texture_t<1>>,
          boost::mpl::always<
              boost::fusion::map<
                  boost::fusion::pair<drawable_key,
                                      const Drawable &>,
                  boost::fusion::pair<texture_data_key,
                                      const texture &>>>>> type;
};

template <typename Drawable>
struct drawable_fusion {
  typedef typename boost::mpl::switch_<
  		 typename drawable_switch_body<Drawable>::type,
      typename drawable_switch_element<Drawable>::type>::type type;
};

template <typename Drawable>
struct drawable_switch {
  typedef boost::fusion::result_of::size<
  		 typename drawable_fusion<Drawable>::type> type;
};

class drawable_fusion_initializer {
  struct dummy {};

 public:
  template <typename Drawable>
  static typename drawable_fusion<Drawable>::type
      init(const Drawable &drawable,
           typename std::enable_if<drawable_switch<Drawable>::type::value == 1,
                                   dummy>::type = dummy()) {
    return typename drawable_fusion<Drawable>::type(drawable);
  }

  template <typename Drawable>
  static typename drawable_fusion<Drawable>::type
      init(const Drawable &drawable,
           typename std::enable_if<drawable_switch<Drawable>::type::value == 2,
                                   dummy>::type = dummy()) {
    return typename drawable_fusion<Drawable>::type(drawable,
    		                                             drawable.texture1());
  }
};
}}

#endif
