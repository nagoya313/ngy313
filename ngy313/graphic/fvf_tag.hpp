#pragma once
#include <type_traits>
#include <boost/mpl/find.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/preprocessor/enum_shifted_params.hpp>
#include <boost/preprocessor/enum_params_with_a_default.hpp>
#include <ngy313/graphic/detail/fvf_type.hpp>
#include <ngy313/graphic/vertex_member.hpp>

namespace ngy313 { namespace graphic {
// �ꕔ�^��������
struct fvf_tag {};

struct position_fvf_tag : public fvf_tag {};

struct tex_fvf_tag : public fvf_tag {};

// �����pair�p���ł悳������
struct dimension2_fvf_tag : public position_fvf_tag {
  typedef boost::mpl::pair<boost::mpl::integral_c<detail::fvf_type, detail::kXYZRHW>, rhw_position_t> type;
  typedef boost::mpl::integral_c<detail::fvf_type, detail::kXYZRHW> fvf_type;
  typedef rhw_position_t member_type;
};

struct dimension3_fvf_tag : public position_fvf_tag {
  typedef boost::mpl::pair<boost::mpl::integral_c<detail::fvf_type, detail::kXYZ>, position_t> type;
  typedef boost::mpl::integral_c<detail::fvf_type, detail::kXYZ> fvf_type;
  typedef position_t member_type;
};

struct normal_fvf_tag : public fvf_tag {
  typedef boost::mpl::pair<boost::mpl::integral_c<detail::fvf_type, detail::kNormal>, normal_t> type;
  typedef boost::mpl::integral_c<detail::fvf_type, detail::kNormal> fvf_type;
  typedef normal_t member_type;
};

struct diffuse_fvf_tag : public fvf_tag {
  typedef boost::mpl::pair<boost::mpl::integral_c<detail::fvf_type, detail::kDiffuse>,
                           diffuse_t> type;
  typedef boost::mpl::integral_c<detail::fvf_type, detail::kDiffuse> fvf_type;
  typedef diffuse_t member_type;
};

struct specular_fvf_tag : public fvf_tag {
  typedef boost::mpl::pair<boost::mpl::integral_c<detail::fvf_type, detail::kSpecular>, specular_t> type;
  typedef boost::mpl::integral_c<detail::fvf_type, detail::kSpecular> fvf_type;
  typedef specular_t member_type;
};

struct tex1_fvf_tag : public tex_fvf_tag {
  typedef boost::mpl::pair<boost::mpl::integral_c<detail::fvf_type, detail::kTex1>, tex_t<1>> type;
  typedef boost::mpl::integral_c<detail::fvf_type, detail::kTex1> fvf_type;
  typedef tex_t<1> member_type;
};

struct tex2_fvf_tag : public tex_fvf_tag {
  typedef boost::mpl::pair<boost::mpl::integral_c<detail::fvf_type, detail::kTex2>, tex_t<2>> type;
  typedef boost::mpl::integral_c<detail::fvf_type, detail::kTex2> fvf_type;
  typedef tex_t<2> member_type;
};

template <typename Tag>
struct find_base_of_fvf_tag {
  template <typename Rhs>
  struct apply {
    typedef std::is_base_of<Tag, Rhs> type;
  };
};

struct safe_tag_insert {
  typedef boost::mpl::vector<> fvf_tag_list;
  template <typename Lhs, typename Rhs>
  struct apply {
    static_assert(std::is_base_of<fvf_tag, Rhs>::value, "Rhs is not fvf tag.");
    /*
    // position_fvf_tag�������ɂȂ�悤�Ȃ炱��������
    static_assert(!(std::is_base_of<position_fvf_tag, Rhs>::value && 
                    boost::mpl::find_if<Lhs, find_base_of_tag<position_fvf_tag>>::value)), 
                  "");
    // tex_fvf_tag�������ɂȂ�悤�Ȃ炱��������
    static_assert(!(std::is_base_of<tex_fvf_tag, Rhs>::value && 
                    boost::mpl::find_if<Lhs, find_base_of_fvf_tag<tex_fvf_tag>>::value)), 
                  "");*/
    typedef typename boost::mpl::push_back<Lhs, Rhs>::type type;
  };
};

// �����̒l�����낱��ς�
#define NGY313_TAG_MAX 8

template <BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(NGY313_TAG_MAX, typename T, boost::mpl::na)> 
struct make_fvf_tag {
  typedef typename boost::mpl::fold<boost::mpl::vector<BOOST_PP_ENUM_SHIFTED_PARAMS(NGY313_TAG_MAX, T)>,
                                    boost::mpl::vector<T0>, 
                                    safe_tag_insert>::type type;
};

#undef NGY313_MAKE_TAG_GEN

#undef NGY313_TAG_MAX

typedef make_fvf_tag<dimension2_fvf_tag, diffuse_fvf_tag> shape_2d_fvf_tag;
typedef make_fvf_tag<dimension2_fvf_tag, diffuse_fvf_tag, tex1_fvf_tag> image_2d_fvf_tag;
typedef make_fvf_tag<dimension2_fvf_tag, diffuse_fvf_tag, tex2_fvf_tag> multi_image_2d_fvf_tag;
}}
