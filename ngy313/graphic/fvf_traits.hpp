#pragma once
#include <cstdint>
#include <type_traits>
#include <boost/mpl/at.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/bitor.hpp>
#include <boost/mpl/distance.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/inc.hpp>
#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/repeat_from_to.hpp>

namespace ngy313 { namespace graphic {
template <typename List, std::size_t Size>
struct vertex;

#define NGY313_VERTEX_MENBER_GEN(z, n, data)\
typename boost::mpl::at_c<data, n>::type BOOST_PP_CAT(m, n);

struct fvf_type {
  template <typename FVFTag>
  struct apply {
    typedef typename FVFTag::member_type type;
  };
};

#define NGY313_VERTEX_STRUCT_GEN(z, n, data)\
template <typename List>\
struct vertex<List, n> {\
  typedef boost::mpl::transform_view<List, fvf_type> list_type;\
  BOOST_PP_REPEAT(n, NGY313_VERTEX_MENBER_GEN, list_type)\
};

// ‚±‚Ì’l‚Í‚±‚ë‚±‚ë•Ï‚é
#define NGY313_MEMBER_MAX 8

BOOST_PP_REPEAT_FROM_TO(1, BOOST_PP_INC(NGY313_MEMBER_MAX), NGY313_VERTEX_STRUCT_GEN, _)

#undef NGY313_VERTEX_MENBER_GEN

#undef NGY313_VERTEX_STRUCT_GEN

struct fvf_value {
  template <typename FVFTag>
  struct apply {
    typedef typename FVFTag::fvf_type type;
  };
};

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
struct fvf_traits {
  typedef std::integral_constant<std::uint32_t, 
                                 boost::mpl::fold<boost::mpl::transform_view<typename FVFTag::type, fvf_value>,
                                                  boost::mpl::integral_c<std::uint32_t, 0>,
                                                  boost::mpl::bitor_<>>::type::value> fvf_type;
  typedef vertex<typename FVFTag::type, boost::mpl::size<typename FVFTag::type>::value> vertex_type;
};

struct fvf_member_type {
  template <typename Member>
  struct apply {
    typedef typename Member::type type;
  };
};

template <typename FindMember>
struct find_fvf_member_type {
  template <typename Member>
  struct apply {
    typedef std::is_same<typename Member::type, FindMember> type;
  };
};

template <typename Member, typename Vertex>
struct member_at_impl {
  typedef boost::mpl::transform_view<typename Vertex::list_type, fvf_member_type> list_type;
  typedef typename boost::mpl::find_if<typename Vertex::list_type, 
                                       find_fvf_member_type<Member>>::type::type member_type;
  typedef member<member_type,
                 Vertex,
                 boost::mpl::distance<typename boost::mpl::begin<list_type>::type,
                                      typename boost::mpl::find<list_type, Member>::type>::value> type;
};

template <typename Member, typename Vertex>
typename member_at_impl<Member, Vertex>::member_type &vertex_member_at(Vertex &vertex) {
  return member_at_impl<Member, Vertex>::type::at(vertex);
}

template <typename Member, typename Vertex>
const typename member_at_impl<Member, Vertex>::member_type &vertex_member_at(const Vertex &vertex) {
  return member_at_impl<Member, Vertex>::type::at(vertex);
}
}}
