#pragma once
#include <cstdint>
#include <type_traits>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/filter_view.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/bitor.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/distance.hpp>
#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/repeat_from_to.hpp>
#include <boost/preprocessor/inc.hpp>
#include <boost/preprocessor/cat.hpp>
#include <d3d9.h>
#include "fvf_tag.hpp"
#include "vertex_member.hpp"

namespace ngy313 { namespace detail {
struct fvf_base {
  typedef std::uint32_t value_type;
  typedef boost::mpl::integral_c_tag tag;
};

struct dimension2_fvf : public fvf_base {
  static const value_type value = D3DFVF_XYZRHW;
  typedef rhw_position_t type;
};

struct diffuse_fvf : public fvf_base {
  static const value_type value = D3DFVF_DIFFUSE;
  typedef diffuse_t type;
};

struct tex1_fvf : public fvf_base {
  static const value_type value = D3DFVF_TEX1;
  typedef tex_t<1> type;
};

struct tex2_fvf : public fvf_base {
  static const value_type value = D3DFVF_TEX2;
  typedef tex_t<2> type;
};

typedef boost::mpl::vector<boost::mpl::pair<dimension2_fvf_tag, dimension2_fvf>,
                           boost::mpl::pair<diffuse_fvf_tag, diffuse_fvf>,
                           boost::mpl::pair<tex1_fvf_tag, tex1_fvf>,
                           boost::mpl::pair<tex2_fvf_tag, tex2_fvf>> fvf_map;

template <typename List, std::size_t Size>
struct vertex;

#define NGY313_VERTEX_MENBER_GEN(z, n, data)\
typename boost::mpl::at_c<data, n>::type BOOST_PP_CAT(m, n);

struct fvf_type {
  template <typename FVFTag>
  struct apply {
    typedef typename FVFTag::second::type type;
  };
};

#define NGY313_VERTEX_STRUCT_GEN(z, n, data)\
template <typename List>\
struct vertex<List, n> {\
  typedef boost::mpl::transform_view<List, fvf_type> list;\
  BOOST_PP_REPEAT(n, NGY313_VERTEX_MENBER_GEN, list)\
};

#define NGY313_MEMBER_MAX 3

BOOST_PP_REPEAT_FROM_TO(1, BOOST_PP_INC(NGY313_MEMBER_MAX), NGY313_VERTEX_STRUCT_GEN, _)

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
\
  static const Member &at(const Vertex &vertex) {\
    return vertex.BOOST_PP_CAT(m, n);\
  }\
};

BOOST_PP_REPEAT(NGY313_MEMBER_MAX, NGY313_MEMBER_GEN, _)

#undef NGY313_MEMBER_GEN

#undef NGY313_MEMBER_MAX

template <typename FVFTag>
struct fvf_is_inherit {
  template <typename Rhs>
  struct apply {
    typedef std::is_base_of<typename Rhs::first, FVFTag> type;
  };
};

struct fvf_value {
  template <typename FVFTag>
  struct apply {
    typedef typename FVFTag::second type;
  };
};

template <typename FVFTag>
struct fvf_traits {
  static_assert(std::is_base_of<fvf_tag, typename FVFTag::type>::value, "");
  typedef boost::mpl::filter_view<fvf_map, fvf_is_inherit<typename FVFTag::type>> fvf_map;
  typedef std::uint32_t value_type;
  static const value_type value = boost::mpl::fold<boost::mpl::transform_view<fvf_map, fvf_value>,
                                                   boost::mpl::integral_c<std::uint32_t, 0>,
                                                   boost::mpl::bitor_<>>::type::value;
  typedef vertex<fvf_map, boost::mpl::size<fvf_map>::value> type;
};

template <typename Member, typename Vertex, typename List>
struct member_at_impl {
  typedef member<Member,
                 Vertex,
                 boost::mpl::distance<typename boost::mpl::begin<List>::type,
                 typename boost::mpl::find<List, Member>::type>::value> type;
};
}}

namespace ngy313 {
template <typename Member, typename Vertex>
Member &vertex_member_at(Vertex &vertex) {
  return detail::member_at_impl<Member, Vertex, typename Vertex::list>::type::at(vertex);
}

template <typename Member, typename Vertex>
const Member &vertex_member_at(const Vertex &vertex) {
  return detail::member_at_impl<Member, Vertex, typename Vertex::list>::type::at(vertex);
}
}