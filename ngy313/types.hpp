#ifndef NGY313_TYPES_HPP_
#define NGY313_TYPES_HPP_

#include <type_traits>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/push_back.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/count_if.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/preprocessor/enum_shifted_params.hpp>
#include <boost/preprocessor/enum_params_with_a_default.hpp>
#include <ngy313/vertex_member.hpp>
#include <ngy313/detail/types.hpp>

namespace ngy313 {
struct position_fvf_tag {};
struct texture_fvf_tag {};

struct dimension2_fvf_tag
    : position_fvf_tag,
      boost::mpl::pair<detail::fvf_type::xyz_rhw,
                       rhw_position_t> {};

struct dimension3_fvf_tag
    : position_fvf_tag,
      boost::mpl::pair<detail::fvf_type::xyz,
                       position_t> {};

struct normal_fvf_tag
    : boost::mpl::pair<detail::fvf_type::normal,
                       normal_t> {};

struct diffuse_fvf_tag
    : boost::mpl::pair<detail::fvf_type::diffuse,
                       diffuse_t> {};

struct specular_fvf_tag
    : boost::mpl::pair<detail::fvf_type::specular,
                       specular_t> {};

struct texture1_fvf_tag
    : texture_fvf_tag,
      boost::mpl::pair<detail::fvf_type::texture,
                       texture_t<1>> {};
struct texture2_fvf_tag
    : texture_fvf_tag,
      boost::mpl::pair<detail::fvf_type::multi_texture,
                       texture_t<2>> {};

typedef detail::primitive_type::point_list
		point_list_primitive_tag;
typedef detail::primitive_type::line_list
		line_list_primitive_tag;
typedef detail::primitive_type::line_strip
		line_strip_primitive_tag;
typedef detail::primitive_type::triangle_list
		triangle_list_primitive_tag;
typedef detail::primitive_type::triangle_strip
		triangle_strip_primitive_tag;
typedef detail::primitive_type::triangle_fan
		triangle_fan_primitive_tag;

#define NGY313_TAG_MAX 8

template <BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(NGY313_TAG_MAX, typename T, boost::mpl::na)>
class make_fvf_tag {
  class safe_tag_insert {
    typedef boost::mpl::vector<dimension2_fvf_tag,
    		                       dimension3_fvf_tag,
    		                       normal_fvf_tag,
    		                       diffuse_fvf_tag,
    		                       specular_fvf_tag,
    		                       texture1_fvf_tag,
    		                       texture2_fvf_tag> tag_list;

   public:
    template <typename Lhs, typename Rhs>
    struct apply {
      static_assert(boost::mpl::contains<tag_list, Rhs>::value,
                    "Rhs is not fvf_tag.");
      static_assert(boost::mpl::count_if<
                        Lhs,
                        std::is_base_of<position_fvf_tag,
                                        boost::mpl::_1>>::value <= 1,
                    "position_fvf_tag overlaps.");
      static_assert(boost::mpl::count_if<
      		              Lhs,
      		              std::is_base_of<texture_fvf_tag,
      		                              boost::mpl::_1>>::value <= 1,
                    "texture_fvf_tag overlaps.");
      typedef typename boost::fusion::result_of::push_back<Lhs, 
                                                           Rhs>::type type;
    };
  };

 public:
  typedef typename boost::mpl::fold<
      boost::mpl::vector<BOOST_PP_ENUM_SHIFTED_PARAMS(NGY313_TAG_MAX, T)>,
      boost::fusion::vector<T0>,
      safe_tag_insert>::type type;
};

#undef NGY313_TAG_MAX

typedef make_fvf_tag<dimension2_fvf_tag,
                     diffuse_fvf_tag> shape_2d_fvf_tag;
typedef make_fvf_tag<dimension2_fvf_tag,
                     texture1_fvf_tag> image_2d_fvf_tag;
typedef make_fvf_tag<dimension2_fvf_tag,
                     diffuse_fvf_tag,
                     texture1_fvf_tag> bright_image_2d_fvf_tag;
}

#endif
