#pragma once
#include <cstdint>
#include <d3d9.h>
#include "drawable_adaptor.hpp"

namespace ngy313 { namespace detail {
struct texture_operator_tag {
  typedef D3DTEXTUREOP value_type;
};

struct disable_texture_operator_tag : public texture_operator_tag {
  static const value_type value = D3DTOP_DISABLE;
};

struct arg1_texture_operator_tag : public texture_operator_tag {
  static const value_type value = D3DTOP_SELECTARG1;
};

struct modulate_texture_operator_tag : public texture_operator_tag {
  static const value_type value = D3DTOP_MODULATE;
};

struct modulate2_texture_operator_tag : public texture_operator_tag {
  static const value_type value = D3DTOP_MODULATE2X;
};

struct modulate4_texture_operator_tag : public texture_operator_tag {
  static const value_type value = D3DTOP_MODULATE4X;
};

struct add_texture_operator_tag : public texture_operator_tag {
  static const value_type value = D3DTOP_ADD;
};

struct add_signed_texture_operator_tag : public texture_operator_tag {
  static const value_type value = D3DTOP_ADDSIGNED;
};

struct add_signed2_texture_operator_tag : public texture_operator_tag {
  static const value_type value = D3DTOP_ADDSIGNED2X;
};

struct sub_texture_operator_tag : public texture_operator_tag {
  static const value_type value = D3DTOP_SUBTRACT;
};

struct add_smooth_texture_operator_tag : public texture_operator_tag {
  static const value_type value = D3DTOP_ADDSMOOTH;
};

struct blend_diffuse_alpha_texture_operator_tag : public texture_operator_tag {
  static const value_type value = D3DTOP_BLENDDIFFUSEALPHA;
};

struct blend_texture_alpha_texture_operator_tag : public texture_operator_tag {
  static const value_type value = D3DTOP_BLENDTEXTUREALPHA;
};

struct blend_factor_alpha_texture_operator_tag : public texture_operator_tag {
  static const value_type value = D3DTOP_BLENDFACTORALPHA;
};

struct blend_texture_alpha_pm_texture_operator_tag : public texture_operator_tag {
  static const value_type value = D3DTOP_BLENDTEXTUREALPHAPM;
};

struct blend_currental_alpha_texture_operator_tag : public texture_operator_tag {
  static const value_type value = D3DTOP_BLENDCURRENTALPHA;
};

struct premodulate_texture_operator_tag : public texture_operator_tag {
  static const value_type value = D3DTOP_PREMODULATE;
};

struct modulate_alpha_add_color_texture_operator_tag : public texture_operator_tag {
  static const value_type value = D3DTOP_MODULATEALPHA_ADDCOLOR;
};

struct modulate_alpha_add_alpha_texture_operator_tag : public texture_operator_tag {
  static const value_type value = D3DTOP_MODULATECOLOR_ADDALPHA;
};
 
struct modulate_inv_alpha_add_color_texture_operator_tag : public texture_operator_tag {
  static const value_type value = D3DTOP_MODULATEINVALPHA_ADDCOLOR;
};

struct modulate_inv_alpha_add_alpha_texture_operator_tag : public texture_operator_tag {
  static const value_type value = D3DTOP_MODULATEINVCOLOR_ADDALPHA;
};

struct bump_env_map_texture_operator_tag : public texture_operator_tag {
  static const value_type value = D3DTOP_BUMPENVMAP;
};

struct bump_env_map_luminance_texture_operator_tag : public texture_operator_tag {
  static const value_type value = D3DTOP_BUMPENVMAPLUMINANCE;
};

struct dot_product3_texture_operator_tag : public texture_operator_tag {
  static const value_type value = D3DTOP_DOTPRODUCT3;
};

struct multiplay_add_texture_operator_tag : public texture_operator_tag {
  static const value_type value = D3DTOP_MULTIPLYADD;
};
 
struct lerp_texture_operator_tag : public texture_operator_tag {
  static const value_type value = D3DTOP_LERP;
};
 
struct texture_arg_tag {
  typedef std::uint32_t value_type;
};

struct mask_texture_arg_tag : public texture_arg_tag {
  static const value_type value = D3DTA_SELECTMASK;
};

struct diffuse_texture_arg_tag : public texture_arg_tag {
  static const value_type value = D3DTA_DIFFUSE;
};

struct current_texture_arg_tag : public texture_arg_tag {
  static const value_type value = D3DTA_CURRENT;
};

struct texture_texture_arg_tag : public texture_arg_tag {
  static const value_type value = D3DTA_TEXTURE;
};

struct texture_factor_texture_arg_tag : public texture_arg_tag {
  static const value_type value = D3DTA_TFACTOR;
};

struct specular_texture_arg_tag : public texture_arg_tag {
  static const value_type value = D3DTA_SPECULAR;
};

struct temp_texture_arg_tag : public texture_arg_tag {
  static const value_type value = D3DTA_TEMP;
};

struct const_texture_arg_tag : public texture_arg_tag {
  static const value_type value = D3DTA_CONSTANT;
};

struct complement_texture_arg_tag : public texture_arg_tag {
  static const value_type value = D3DTA_COMPLEMENT;
};

struct alpha_peplicate_texture_arg_tag : public texture_arg_tag {
  static const value_type value = D3DTA_ALPHAREPLICATE;
};

template <typename TextureStagePair>
struct texture_stage_type {
  typedef TextureStagePair texture_stage_pair_type;
};

template <typename Lhs, typename Op, typename Rhs = void>
struct color_stage {
  typedef Lhs arg1_type;
  typedef Op operator_type;
  typedef Rhs arg2_type;
};

template <typename Lhs, typename Op, typename Rhs = void>
struct alpha_stage {
  typedef Lhs arg1_type;
  typedef Op operator_type;
  typedef Rhs arg2_type;
};

template <typename ColorStage, typename AlphaStage = void>
struct texture_stage_pair {
  typedef ColorStage color_type;
  typedef AlphaStage alpha_type;
};

typedef texture_stage_pair<color_stage<texture_texture_arg_tag,
                                       modulate_texture_operator_tag, 
                                       diffuse_texture_arg_tag>,
                           alpha_stage<texture_texture_arg_tag, arg1_texture_operator_tag>> default_stage0;

typedef texture_stage_pair<color_stage<texture_texture_arg_tag, arg1_texture_operator_tag>> default_stage1;

template <typename Drawable, typename ColorStage, typename AlphaStage>
struct texture_stage_adaptor_base
    : public vertex_adaptor<Drawable>, public texture_stage_type<texture_stage_pair<ColorStage, AlphaStage>> {
  explicit texture_stage_adaptor_base(const Drawable &drawable) : all_vertex_adaptor(drawable) {}
};

template <typename ColorStage, typename AlphaStage = void>
struct texture_stage_adaptor {
  template <typename Signature>
  struct result {
    typedef texture_stage_adaptor_base<typename copy_argument<Signature>::type, ColorStage, AlphaStage> type;
  };

  template <typename Drawable>
  texture_stage_adaptor_base<Drawable, ColorStage, AlphaStage> operator ()(const Drawable &drawable) const {
    return texture_stage_adaptor_base<Drawable, ColorStage, AlphaStage>(drawable);
  }
};
}}