#ifndef NGY313_DETAIL_TYPES_HPP_
#define NGY313_DETAIL_TYPES_HPP_

#include <type_traits>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/vector.hpp>

#if defined(_WIN32)
#include <ngy313/detail/direct3d9_types.hpp>
#elif defined(__linux__)
#include <ngy313/detail/opengl_types.hpp>
#endif

namespace ngy313 { namespace detail {
template <typename FVF>
struct basic_fvf_type {
  typedef typename FVF::value_type value_type;

  typedef boost::mpl::integral_c<value_type, FVF::kXYZ_RHW> xyz_rhw;
  typedef boost::mpl::integral_c<value_type, FVF::kXYZ> xyz;
  typedef boost::mpl::integral_c<value_type, FVF::kNormal> normal;
  typedef boost::mpl::integral_c<value_type, FVF::kDiffuse> diffuse;
  typedef boost::mpl::integral_c<value_type, FVF::kSpecular> specular;
  typedef boost::mpl::integral_c<value_type, FVF::kTexture> texture;
  typedef boost::mpl::integral_c<value_type, FVF::kMultiTexture> multi_texture;
};

template <typename Primitive>
struct basic_primitive_type {
  typedef typename Primitive::value_type value_type;

  typedef std::integral_constant<value_type, Primitive::kPointList> point_list;
  typedef std::integral_constant<value_type, Primitive::kLineList> line_list;
  typedef std::integral_constant<value_type, Primitive::kLineStrip> line_strip;
  typedef std::integral_constant<value_type,
                                 Primitive::kTriangleList> triangle_list;
  typedef std::integral_constant<value_type,
                                 Primitive::kTriangleStrip> triangle_strip;
  typedef std::integral_constant<value_type,
                                 Primitive::kTriangleFan> triangle_fan;
  
  typedef boost::mpl::vector<point_list,
                             line_list,
                             line_strip,
                             triangle_list,
                             triangle_strip,
                             triangle_fan> tag_list;
};

template <typename Blend>
struct basic_blend_type {
  typedef typename Blend::value_type value_type;

  typedef std::integral_constant<value_type, 
                                 Blend::kBlendOne> one_blend;
  typedef std::integral_constant<value_type, 
                                 Blend::kBlendSrcAlpha> src_alpha_blend;
  typedef std::integral_constant<
              value_type,
              Blend::kBlendInvSrcAlpha> inv_src_alpha_blend;
  typedef std::integral_constant<value_type, 
                                 Blend::kBlendZero> zero_blend;
  typedef std::integral_constant<value_type,
                                 Blend::kBlendSrcColor> src_color_blend;
  typedef std::integral_constant<
              value_type,
              Blend::kBlendInvSrcColor> inv_src_color_blend;
  typedef std::integral_constant<value_type, 
                                 Blend::kBlendDestColor> dest_color_blend;
  typedef std::integral_constant<
              value_type, 
              Blend::kBlendInvDestColor> inv_dest_color_blend;
              
  typedef boost::mpl::vector<one_blend,
                             src_alpha_blend,
                             inv_src_alpha_blend,
                             zero_blend,
                             src_color_blend,
                             inv_src_color_blend,
                             dest_color_blend, 
                             inv_dest_color_blend> tag_list;
};

template <typename Addressing>
struct basic_addressing_type {
  typedef typename Addressing::value_type value_type;

  typedef std::integral_constant<value_type, 
                                 Addressing::kAddressWrap> wrap_addressing;
  typedef std::integral_constant<value_type, 
                                 Addressing::kAddressClamp> clamp_addressing;
              
  typedef boost::mpl::vector<wrap_addressing,
                             clamp_addressing> tag_list;
};

#if defined(_WIN32)
typedef basic_fvf_type<direct3d9_fvf_type> fvf_type;
typedef basic_primitive_type<direct3d9_primitive_type>
    primitive_type;
typedef basic_blend_type<direct3d9_blend_type>
    blend_type;
#elif defined(__linux__)
typedef basic_fvf_type<opengl_fvf_type> fvf_type;
typedef basic_primitive_type<opengl_primitive_type>
   primitive_type;
typedef basic_blend_type<opengl_blend_type>
    blend_type;
#endif
}}

#endif
