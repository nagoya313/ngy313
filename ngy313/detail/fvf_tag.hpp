#pragma once
#include <type_traits>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/inherit.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repeat_from_to.hpp>
#include <boost/preprocessor/enum_shifted_params.hpp>
#include <boost/preprocessor/comparison/not_equal.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/comma_if.hpp>

namespace ngy313 {
struct fvf_tag {};

struct position_fvf_tag : public fvf_tag {};

struct tex_fvf_tag : public fvf_tag {};

struct dimension2_fvf_tag : public position_fvf_tag {};

struct dimension3_fvf_tag : public position_fvf_tag {};

struct normal_fvf_tag : public fvf_tag {};

struct diffuse_fvf_tag : public fvf_tag {};

struct specular_fvf_tag : public fvf_tag {};

struct tex1_fvf_tag : public tex_fvf_tag {};

struct tex2_fvf_tag : public tex_fvf_tag {};
}

namespace ngy313 { namespace detail {
struct tag_inherit {
  template <typename Lhs, typename Rhs>
  struct apply {
    static_assert(!(std::is_base_of<position_fvf_tag, Lhs>::value && std::is_base_of<position_fvf_tag, Rhs>::value), 
                  "");
    static_assert(!(std::is_base_of<tex_fvf_tag, Lhs>::value && std::is_base_of<tex_fvf_tag, Rhs>::value), 
                  "");
    static_assert(std::is_base_of<fvf_tag, Lhs>::value,
                  "");
    typedef typename boost::mpl::inherit<Lhs, Rhs>::type type;
  };
};
}}

namespace ngy313 {
#define NGY313_TAG_MAX 16

#define NGY313_MAKE_TAG_GEN(z, n, data)\
typename BOOST_PP_CAT(T, n) = boost::mpl::na BOOST_PP_COMMA_IF(BOOST_PP_NOT_EQUAL(n, NGY313_TAG_MAX))

template <typename T0, BOOST_PP_REPEAT_FROM_TO(1, BOOST_PP_INC(NGY313_TAG_MAX), NGY313_MAKE_TAG_GEN, _)> 
struct make_fvf_tag {
  typedef typename boost::mpl::fold<boost::mpl::vector<BOOST_PP_ENUM_SHIFTED_PARAMS(NGY313_TAG_MAX, T)>,
                                    T0, 
                                    detail::tag_inherit>::type type;
};

#undef NGY313_MAKE_TAG_GEN

#undef NGY313_TAG_MAX

typedef make_fvf_tag<dimension2_fvf_tag, diffuse_fvf_tag> shape_2d_fvf_tag;
typedef make_fvf_tag<dimension2_fvf_tag, diffuse_fvf_tag, tex1_fvf_tag> image_2d_fvf_tag;
}