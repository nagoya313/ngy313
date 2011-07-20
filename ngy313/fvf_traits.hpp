#ifndef NGY313_FVF_TRAITS_HPP_
#define NGY313_FVF_TRAITS_HPP_

#include <cstdint>
#include <type_traits>
#include <boost/mpl/bitor.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/include/find_if.hpp>
#include <ngy313/vertex_member.hpp>

namespace ngy313 { namespace detail {
template <typename FindMember>
struct find_fvf_member_type {
  template <typename Member>
  struct apply {
    typedef std::is_same<typename Member::type, FindMember> type;
  };
};
}}

namespace ngy313 {
template <typename FVFTag>
struct fvf_traits {
 private:
	struct element_insert {
	  template <typename Lhs, typename Rhs>
	  struct apply {
	    typedef typename boost::mpl::push_back<
	    		 Lhs, typename Rhs::second>::type type;
	  };
	};
	
	template <typename List>
	struct find_texture_type {
	  typedef typename boost::mpl::find_if<
	  		 List,
	  		 detail::find_fvf_member_type<texture_member>>::type type;
	};
	
 public:
  typedef std::integral_constant<
  		 std::uint32_t,
      boost::mpl::fold<typename FVFTag::type,
          boost::mpl::integral_c<std::uint32_t, 0>,
          boost::mpl::bitor_<
              boost::mpl::_1,
              boost::mpl::first<boost::mpl::_2>>>::type::value> fvf_type;
  typedef typename boost::mpl::fold<typename FVFTag::type,
                                    boost::fusion::vector<>,
                                    element_insert>::type vertex_type;
  typedef typename find_texture_type<vertex_type>::type::type texture_type;
};

template <typename Member, typename Vertex>
typename boost::mpl::find_if<
    Vertex,
    detail::find_fvf_member_type<Member>>::type::type &
    vertex_member_at(Vertex &vertex) {
  return *boost::fusion::find_if<detail::find_fvf_member_type<Member>>(vertex);
}

template <typename Member, typename Vertex>
const typename boost::mpl::find_if<
    Vertex,
    detail::find_fvf_member_type<Member>>::type::type &
   vertex_member_at(const Vertex &vertex) {
  return *boost::fusion::find_if<detail::find_fvf_member_type<Member>>(vertex);
}
}

#endif
