#ifndef NGY313_GRAPHIC_TEXTURE_STAGE_TAG_HPP_
#define NGY313_GRAPHIC_TEXTURE_STAGE_TAG_HPP_
#include <cstddef>
#include <type_traits>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/vector.hpp>
#include <ngy313/graphic/detail/windows/texture_stage_type.hpp>

namespace ngy313 { namespace graphic {
typedef std::integral_constant<detail::texture_option, detail::kTextureOptionDisable> disable_texture_operator_tag;
typedef std::integral_constant<detail::texture_option, detail::kTextureOptionSelectArg1> arg1_texture_operator_tag;
typedef std::integral_constant<detail::texture_option, detail::kTextureOptionSelectArg2> arg2_texture_operator_tag;
typedef std::integral_constant<detail::texture_option, detail::kTextureOptionModulate> modulate_texture_operator_tag;
typedef std::integral_constant<detail::texture_option, detail::kTextureOptionModulate2> modulate2_texture_operator_tag;
typedef std::integral_constant<detail::texture_option, detail::kTextureOptionModulate4> modulate4_texture_operator_tag;
typedef std::integral_constant<detail::texture_option, detail::kTextureOptionAdd> add_texture_operator_tag;
typedef std::integral_constant<detail::texture_option, detail::kTextureOptionAddSigned> add_signed_texture_operator_tag;
typedef std::integral_constant<detail::texture_option, detail::kTextureOptionAddSigned2> add_signed2_texture_operator_tag;
typedef std::integral_constant<detail::texture_option, detail::kTextureOptionSubtract> subtract_texture_operator_tag;
typedef std::integral_constant<detail::texture_option, detail::kTextureOptionAddSmooth> add_smooth_texture_operator_tag;
typedef std::integral_constant<detail::texture_option, detail::kTextureOptionBlendDiffuseAlpha> blend_diffuse_alpha_texture_operator_tag;
typedef std::integral_constant<detail::texture_option, detail::kTextureOptionBlendTextureAlpha> blend_texture_alpha_texture_operator_tag;
typedef std::integral_constant<detail::texture_option, detail::kTextureOptionBlendFactorAlpha> blend_factor_alpha_texture_operator_tag;
typedef std::integral_constant<detail::texture_option, detail::kTextureOptionBlendTextureAlphaPM> blend_texture_alpha_pm_texture_operator_tag;
typedef std::integral_constant<detail::texture_option, detail::kTextureOptionBlendCurrentAlpha> blend_current_alpha_texture_operator_tag;
typedef std::integral_constant<detail::texture_option, detail::kTextureOptionPreModulate> pre_modulate_texture_operator_tag;
typedef std::integral_constant<detail::texture_option, detail::kTextureOptionModulateAlphaAddColor> modulate_alpha_add_color_texture_operator_tag;
typedef std::integral_constant<detail::texture_option, detail::kTextureOptionModulateColorAddAlpha> modulate_color_add_alpha_texture_operator_tag;
typedef std::integral_constant<detail::texture_option, detail::kTextureOptionModulateInvAlphaAddColor> modulate_inv_alpha_add_color_texture_operator_tag;
typedef std::integral_constant<detail::texture_option, detail::kTextureOptionModulateInvColorAddAlpha> modukate_inv_color_add_alpha_texture_operator_tag;
typedef std::integral_constant<detail::texture_option, detail::kTextureOptionBumpEnvMap> bump_env_map_texture_operator_tag;
typedef std::integral_constant<detail::texture_option, detail::kTextureOptionBumpEnvMapLuminance> bump_env_map_luminance_texture_operator_tag;
typedef std::integral_constant<detail::texture_option, detail::kTextureOptionDotProduct3> dot_product3_texture_operator_tag;
typedef std::integral_constant<detail::texture_option, detail::kTextureOptionMultiPlyadd> multi_plyadd_texture_operator_tag;
typedef std::integral_constant<detail::texture_option, detail::kTextureOptionLerp> lerp_texture_operator_tag;

typedef std::integral_constant<detail::texture_arg, detail::kTextureArgMask> mask_texture_arg_tag;
typedef std::integral_constant<detail::texture_arg, detail::kTextureArgDiffuse> diffuse_texture_arg_tag;
typedef std::integral_constant<detail::texture_arg, detail::kTextureArgCurrent> current_texture_arg_tag;
typedef std::integral_constant<detail::texture_arg, detail::kTextureArgTexture> texture_texture_arg_tag;
typedef std::integral_constant<detail::texture_arg, detail::kTextureArgTFactor> t_factor_texture_arg_tag;
typedef std::integral_constant<detail::texture_arg, detail::kTextureArgSpecular> specular_texture_arg_tag;
typedef std::integral_constant<detail::texture_arg, detail::kTextureArgTemp> temp_texture_arg_tag;
typedef std::integral_constant<detail::texture_arg, detail::kTextureArgConstant> constant_texture_arg_tag;
typedef std::integral_constant<detail::texture_arg, detail::kTextureArgComplement> complement_texture_arg_tag;
typedef std::integral_constant<detail::texture_arg, detail::kTextureArgAlphaReplicate> alpha_replicate_texture_arg_tag;

template <std::size_t Stage, typename Color, typename Alpha = void>
struct texture_stage_tuple {
  typedef std::integral_constant<std::size_t, Stage> stage_type;
  typedef Color color_type;
  typedef Alpha alpha_type;

 private:
  // リストではじく処理を入れる
  //typedef boost::mpl::vector<wrap_addressing_tag, mirror_addressing_tag, clamp_addressing_tag> addressing_tag_list;

  // エラーメッセージが日本語で書けないのはつらい
  //static_assert(boost::mpl::contains<addressing_tag_list, U>::value, "");
  //static_assert(boost::mpl::contains<addressing_tag_list, V>::value, "");
};

template <typename Op, typename Lhs = void, typename Rhs = void>
struct color_stage {
  typedef Lhs arg1_type;
  typedef Op operator_type;
  typedef Rhs arg2_type;
};

template <typename Op, typename Lhs = void, typename Rhs = void>
struct alpha_stage {
  typedef Lhs arg1_type;
  typedef Op operator_type;
  typedef Rhs arg2_type;
};

typedef texture_stage_tuple<0, 
                            color_stage<modulate_texture_operator_tag,
                                        diffuse_texture_arg_tag,
                                        texture_texture_arg_tag>,
                            alpha_stage<modulate_texture_operator_tag,
                                        diffuse_texture_arg_tag, 
                                        texture_texture_arg_tag>> default_stage0;

typedef texture_stage_tuple<1, 
                            color_stage<disable_texture_operator_tag>,
                            alpha_stage<disable_texture_operator_tag>> default_stage1;

typedef boost::mpl::vector<default_stage0, default_stage1> default_stage;
}}

#endif
