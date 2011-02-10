#pragma once
#include <cstddef>
#include <type_traits>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/vector.hpp>
#include <ngy313/graphic/detail/texture_stage_type.hpp>

namespace ngy313 { namespace graphic {
typedef std::integral_constant<detail::texture_option, detail::kTextureOptionDisable> disable_texture_operator_tag;
typedef std::integral_constant<detail::texture_option, detail::kTextureOptionSelectArg1> arg1_texture_operator_tag;
typedef std::integral_constant<detail::texture_option, detail::kTextureOptionSelectArg2> arg2_texture_operator_tag;
typedef std::integral_constant<detail::texture_option, detail::kTextureOptionModulate> modulate_texture_operator_tag;
typedef std::integral_constant<detail::texture_option, detail::kTextureOptionModulate2> modulate2_texture_operator_tag;
typedef std::integral_constant<detail::texture_option, detail::kTextureOptionModulate4> modulate4_texture_operator_tag;
typedef std::integral_constant<detail::texture_option, detail::kTextureOptionAdd> add_texture_operator_tag;

typedef std::integral_constant<detail::texture_arg, detail::kTextureArgDiffuse> diffuse_texture_arg_tag;
typedef std::integral_constant<detail::texture_arg, detail::kTextureArgTexture> texture_texture_arg_tag;
typedef std::integral_constant<detail::texture_arg, detail::kTextureArgCurrent> current_texture_arg_tag;

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

typedef texture_stage_tuple<0, 
                            color_stage<texture_texture_arg_tag,
                                        modulate_texture_operator_tag, 
                                        diffuse_texture_arg_tag>,
                            alpha_stage<texture_texture_arg_tag, 
                                        modulate_texture_operator_tag,
                                        diffuse_texture_arg_tag>> default_stage0;

typedef texture_stage_tuple<1, color_stage<texture_texture_arg_tag, arg1_texture_operator_tag>> default_stage1;
}}
