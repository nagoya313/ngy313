#ifndef NGY313_DRAWABLE_TRAITS_HPP_
#define NGY313_DRAWABLE_TRAITS_HPP_

#include <cstdint>
#include <array>
#include <type_traits>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/map.hpp>
#include <ngy313/fvf_traits.hpp>
#include <ngy313/types.hpp>
#include <ngy313/detail/drawable_traits_key.hpp>

namespace ngy313 {
template <typename Drawable, 
          std::size_t Size,
          std::uint32_t Count,
          typename FVFTag, 
          typename PrimitiveTag>
struct drawable_traits {
  static_assert(boost::mpl::contains<detail::primitive_type::tag_list,
                                     PrimitiveTag>::value, "");
  
  typedef boost::mpl::map<
      boost::mpl::pair<detail::drawable_key, Drawable>, 
      boost::mpl::pair<detail::size_key, 
                       std::integral_constant<std::size_t, Size>>,
      boost::mpl::pair<detail::count_key, 
                       std::integral_constant<std::uint32_t, Count>>,
      boost::mpl::pair<detail::fvf_key, FVFTag>,
      boost::mpl::pair<detail::primitive_key, PrimitiveTag>> list_type;

  typedef typename fvf_traits<FVFTag>::vertex_type vertex_type; 
  typedef std::array<vertex_type, Size> vertex_array_type;
};
}

#endif
