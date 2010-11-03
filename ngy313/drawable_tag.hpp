#pragma once
#include <boost/mpl/vector.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repeat_from_to.hpp>
#include <boost/preprocessor/inc.hpp>
#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/comparison/not_equal.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/comma_if.hpp>

namespace ngy313 {
struct fvf_tag {};
struct position_tag {};
struct tex_tag {};
struct dimension2_fvf_tag : public fvf_tag, public position_tag {};
struct dimension3_fvf_tag : public fvf_tag, public position_tag {};
struct normal_fvf_tag : public fvf_tag {};
struct diffuse_fvf_tag : public fvf_tag {};
struct speculer_fvf_tag : public fvf_tag {};
struct tex1_fvf_tag : public fvf_tag, public tex_tag {};
struct tex2_fvf_tag : public fvf_tag, public tex_tag {};

struct primitive_tag {};
struct point_list_primitive_tag : public primitive_tag {};
struct line_list_primitive_tag : public primitive_tag {};
struct line_strip_primitive_tag : public primitive_tag {};
struct triangle_list_primitive_tag : public primitive_tag {};
struct triangle_strip_primitive_tag : public primitive_tag {};
struct triangle_fan_primitive_tag : public primitive_tag {};

#define NGY313_TAG_MAX 16

#define NGY313_MAKE_TAG_GEN(z, n, data)\
typename BOOST_PP_CAT(T, n) = boost::mpl::na BOOST_PP_COMMA_IF(\
                                                 BOOST_PP_NOT_EQUAL(\
                                                     n,\
                                                     BOOST_PP_DEC(\
                                                         BOOST_PP_INC(\
                                                             NGY313_TAG_MAX))))

template <typename T0, 
          BOOST_PP_REPEAT_FROM_TO(1, 
              BOOST_PP_INC(NGY313_TAG_MAX), 
              NGY313_MAKE_TAG_GEN, _)> 
struct make_tag {
  typedef boost::mpl::vector<BOOST_PP_ENUM_PARAMS(
                                 BOOST_PP_INC(NGY313_TAG_MAX),
                                 T)> type;
};

#undef NGY313_MAKE_TAG_GEN

#undef NGY313_TAG_MAX
}