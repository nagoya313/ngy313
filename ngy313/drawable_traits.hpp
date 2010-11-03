#pragma once
#include <cstdint>
#include <type_traits>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/remove_if.hpp>
#include <boost/mpl/count_if.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/bitor.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/distance.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/inherit_linearly.hpp>
#include <boost/mpl/inherit.hpp>
#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/repeat_from_to.hpp>
#include <boost/preprocessor/inc.hpp>
#include <boost/preprocessor/cat.hpp>
#include <d3d9.h>
#include "drawable_tag.hpp"
#include "vertex_member.hpp"

namespace ngy313 { namespace detail {
typedef boost::mpl::vector<
    boost::mpl::vector<
        dimension2_fvf_tag, 
        boost::mpl::integral_c<std::uint32_t, D3DFVF_XYZRHW>,
        rhw_position_t>,
    boost::mpl::vector<
        dimension3_fvf_tag, 
        boost::mpl::integral_c<std::uint32_t, D3DFVF_XYZ>,
        position_t>,
    boost::mpl::vector<
        normal_fvf_tag, 
        boost::mpl::integral_c<std::uint32_t, D3DFVF_NORMAL>,
        normal_t>,
    boost::mpl::vector<
        diffuse_fvf_tag, 
        boost::mpl::integral_c<std::uint32_t, D3DFVF_DIFFUSE>,
        diffuse_t>,
    boost::mpl::vector<
        speculer_fvf_tag, 
        boost::mpl::integral_c<std::uint32_t, D3DFVF_SPECULAR>,
        specular_t>,
    boost::mpl::vector<
        tex1_fvf_tag, 
        boost::mpl::integral_c<std::uint32_t, D3DFVF_TEX1>,
        tex_t<1>>,
    boost::mpl::vector<
        tex2_fvf_tag, 
        boost::mpl::integral_c<std::uint32_t, D3DFVF_TEX2>,
        tex_t<2>>> tag_list;

typedef boost::mpl::map<
    boost::mpl::pair<
        point_list_primitive_tag, 
        boost::mpl::integral_c<D3DPRIMITIVETYPE, 
                               D3DPT_POINTLIST>>,
    boost::mpl::pair<
        point_list_primitive_tag, 
        boost::mpl::integral_c<D3DPRIMITIVETYPE,
                               D3DPT_LINELIST>>,
    boost::mpl::pair<
        point_list_primitive_tag, 
        boost::mpl::integral_c<D3DPRIMITIVETYPE,
                               D3DPT_LINESTRIP>>,
    boost::mpl::pair<
        point_list_primitive_tag, 
        boost::mpl::integral_c<D3DPRIMITIVETYPE, 
                               D3DPT_TRIANGLELIST>>,
    boost::mpl::pair<
        point_list_primitive_tag, 
        boost::mpl::integral_c<D3DPRIMITIVETYPE, 
                               D3DPT_TRIANGLESTRIP>>,
    boost::mpl::pair<
        point_list_primitive_tag, 
        boost::mpl::integral_c<D3DPRIMITIVETYPE, 
                               D3DPT_TRIANGLEFAN>>> primitive_map;

enum tag_list_index {
  kTag,
  kValue,
  kType
};

template <typename List, std::size_t Size>
struct vertex;

#define NGY313_MEMBER_MAX 8

#define NGY313_VERTEX_MENBER_GEN(z, n, data)\
typename boost::mpl::at_c<list, n>::type BOOST_PP_CAT(m, n);

#define NGY313_VERTEX_STRUCT_GEN(z, n, data)\
template <typename List>\
struct vertex<List, n> {\
  typedef List list;\
  BOOST_PP_REPEAT(n, NGY313_VERTEX_MENBER_GEN, _)\
};

BOOST_PP_REPEAT_FROM_TO(1, 
                        BOOST_PP_INC(NGY313_MEMBER_MAX),
                        NGY313_VERTEX_STRUCT_GEN, _)

#undef NGY313_VERTEX_MENBER_GEN
#undef NGY313_VERTEX_STRUCT_GEN

template <typename Member, typename Vertex, std::size_t Size>
struct member;

#define NGY313_MEMBER_GEN(z, n, data)\
template <typename Member, typename Vertex>\
struct member<Member, Vertex, n> {\
  static Member &at(Vertex &vertex) {\
    return vertex.BOOST_PP_CAT(m, n);\
  }\
  static const Member &at(const Vertex &vertex) {\
    return vertex.BOOST_PP_CAT(m, n);\
  }\
};

BOOST_PP_REPEAT(BOOST_PP_INC(NGY313_MEMBER_MAX), NGY313_MEMBER_GEN, _)

#undef NGY313_MEMBER_GEN

#undef NGY313_MEMBER_MAX

template <typename Lhs, typename Rhs>
struct tag_is_base_of {
  typedef bool value_type;
  static const value_type value = !std::is_base_of<typename boost::mpl::at_c<
                                                       Lhs,
                                                       kTag>::type, 
                                                   Rhs>::value;
};

template <typename T, long Pos>
struct tag_transformed {
  template <typename U>
  struct apply {
    typedef typename boost::mpl::at_c<U, Pos>::type type;
  };
};

template <typename List, typename DrawableTag>
struct remove_tag_list {
  typedef typename boost::mpl::remove_if<tag_list, 
                                         tag_is_base_of<
                                             boost::mpl::_1, 
                                             DrawableTag>>::type type;
};

template <typename DrawableTag>
struct tag_inherit {
  typedef typename boost::mpl::inherit_linearly<
      typename DrawableTag, 
      boost::mpl::inherit2<boost::mpl::_, 
                           boost::mpl::_>>::type type;
};

template <typename DrawableTag>
struct fvf_traits {
  static_assert(std::is_base_of<
                    fvf_tag,
                    typename tag_inherit<DrawableTag>::type>::value, 
                "DrawableTag not has FVFTag");
  typedef typename boost::mpl::fold<
      typename boost::mpl::transform<
          typename remove_tag_list<
              tag_list, 
              typename tag_inherit<DrawableTag>::type>::type, 
              tag_transformed<boost::mpl::_1, kValue>>::type, 
              boost::mpl::integral_c<std::uint32_t, 0>, 
              boost::mpl::bitor_<boost::mpl::_1, boost::mpl::_2>>::type type;
};

template <typename DrawableTag>
struct vertex_traits {
  static_assert(std::is_base_of<
                    fvf_tag, 
                    typename tag_inherit<DrawableTag>::type>::value,
                "DrawableTag not has FVFTag");
  typedef typename boost::mpl::transform<
      typename remove_tag_list<
          tag_list, 
          typename tag_inherit<DrawableTag>::type>::type, 
          tag_transformed<boost::mpl::_1, kType>>::type type_list;
  typedef typename vertex<type_list, boost::mpl::size<type_list>::value> type;
};

template <typename DrawableTag>
struct primitve_traits {
  static_assert(std::is_base_of<
                    primitive_tag, 
                    typename tag_inherit<DrawableTag>::type>::value,
                "DrawableTag not has PrimitiveTag");
  typedef DrawableTag type;
};

template <typename Member, typename Vertex, typename List>
struct member_at {
  typedef typename member<Member,
                          Vertex,
                          boost::mpl::distance<
                              typename boost::mpl::begin<List>::type,
                              typename boost::mpl::find<
                                  List, 
                                  Member>::type>::value> type;
};
}}

namespace ngy313 {
template <typename Member, typename Vertex>
Member &member_at(Vertex &vertex) {
  return detail::member_at<Member, 
                           Vertex, 
                           typename Vertex::list>::type::at(vertex);
}

template <typename Member, typename Vertex>
const Member &member_at(const Vertex &vertex) {
  return detail::member_at<Member,
                           Vertex,
                           typename Vertex::list>::type::at(vertex);
}
}