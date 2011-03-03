#pragma once
#include <cstdint>
#include <type_traits>
#include <boost/mpl/at.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/bitor.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/distance.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/include/find_if.hpp>
#include <ngy313/graphic/vertex_member.hpp>

namespace ngy313 { namespace graphic {
template <typename FindMember>
struct find_fvf_member_type {
  template <typename Member>
  struct apply {
    typedef std::is_same<typename Member::type, FindMember> type;
  };
};

template <typename List>
struct find_texture_type {
  typedef typename boost::mpl::find_if<List, find_fvf_member_type<tex>>::type type;
};

struct element_insert {
  template <typename Lhs, typename Rhs>
  struct apply {
    typedef typename boost::mpl::push_back<Lhs, typename Rhs::member_type>::type type;
  };
};

template <typename FVFTag>
struct fvf_traits {
  typedef std::integral_constant<std::uint32_t, 
                                 boost::mpl::fold<typename FVFTag::type,
                                                  boost::mpl::integral_c<std::uint32_t, 0>,
                                                  boost::mpl::bitor_<>>::type::value> fvf_type;
  typedef typename boost::mpl::fold<typename FVFTag::type,
                                    boost::fusion::vector<>,
                                    element_insert>::type vertex_type;
  typedef typename find_texture_type<vertex_type>::type::type tex_type;
};

template <typename Member, typename Vertex>
typename boost::mpl::find_if<Vertex, find_fvf_member_type<Member>>::type::type &vertex_member_at(Vertex &vertex) {
  return *boost::fusion::find_if<find_fvf_member_type<Member>>(vertex);
}

template <typename Member, typename Vertex>
const typename boost::mpl::find_if<Vertex, find_fvf_member_type<Member>>::type::type
    &vertex_member_at(const Vertex &vertex) {
  return *boost::fusion::find_if<find_fvf_member_type<Member>>(vertex);
}

template <typename Drawable>
struct drawable_switch_element {
  typedef typename fvf_traits<
              typename boost::mpl::at<typename Drawable::list_type, detail::fvf_key>::type>::tex_type type;
};
}}
