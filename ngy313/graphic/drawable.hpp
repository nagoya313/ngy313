#ifndef NGY313_GRAPHIC_DRAWABLE_HPP_
#define NGY313_GRAPHIC_DRAWABLE_HPP_
#include <cstdint>
#include <array>
#include <type_traits>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/map.hpp>
#include <ngy313/graphic/detail/key.hpp>
#include <ngy313/graphic/fvf_traits.hpp>
#include <ngy313/graphic/vertex_member.hpp>

namespace ngy313 { namespace graphic {
template <typename Drawable, std::size_t Size, std::uint32_t Count, typename FVFTag, typename PrimitiveTag>
struct drawable {
  // static_assert(); primitive_tag検査をする
  // もう一つテクスチャの保持情報やら基点座標やらの情報を入れるかもしれない
  typedef boost::mpl::map<
      boost::mpl::pair<detail::drawable_key, Drawable>, 
      boost::mpl::pair<detail::size_key, std::integral_constant<std::size_t, Size>>,
      boost::mpl::pair<detail::count_key, std::integral_constant<std::uint32_t, Count>>,
      boost::mpl::pair<detail::fvf_key, FVFTag>,
      boost::mpl::pair<detail::primitive_key, PrimitiveTag>> list_type;
  typedef typename fvf_traits<FVFTag>::vertex_type vertex_type; 
  typedef std::array<vertex_type, Size> vertex_array_type;
};

template <typename Drawable>
struct copy_drawable {
  typedef typename Drawable::list_type list_type;
  typedef typename Drawable::vertex_type vertex_type;
  typedef typename Drawable::vertex_array_type vertex_array_type;
};

template <typename Drawable, typename AddPair>
struct add_drawable {
  typedef typename boost::mpl::insert<typename Drawable::list_type, AddPair>::type list_type;
  typedef typename Drawable::vertex_type vertex_type;
  typedef typename Drawable::vertex_array_type vertex_array_type;
};
}}

#endif

