#pragma once
#include "detail/texture_stage.hpp"

namespace ngy313 { namespace detail {
const texture_stage_adaptor<color_stage<texture_texture_arg_tag, 
                                        add_texture_operator_tag,
                                        diffuse_texture_arg_tag>> add_color = {};

const texture_stage_adaptor<color_stage<texture_texture_arg_tag, 
                                        modulate2_texture_operator_tag,
                                        diffuse_texture_arg_tag>> modultate2_color = {};

const texture_stage_adaptor<color_stage<texture_texture_arg_tag, 
                                        modulate4_texture_operator_tag,
                                        diffuse_texture_arg_tag>> modultate4_color = {};
}}

namespace ngy313 {
using detail::disable_texture_operator_tag;
using detail::arg1_texture_operator_tag;
using detail::modulate_texture_operator_tag;
using detail::modulate2_texture_operator_tag;
using detail::modulate4_texture_operator_tag;
using detail::add_texture_operator_tag;
using detail::add_signed_texture_operator_tag;
using detail::add_signed2_texture_operator_tag;
using detail::sub_texture_operator_tag;
using detail::add_smooth_texture_operator_tag;
using detail::blend_diffuse_alpha_texture_operator_tag;
using detail::blend_texture_alpha_texture_operator_tag;
using detail::blend_factor_alpha_texture_operator_tag;
using detail::blend_texture_alpha_pm_texture_operator_tag;
using detail::blend_currental_alpha_texture_operator_tag;
using detail::premodulate_texture_operator_tag;
using detail::modulate_alpha_add_color_texture_operator_tag;
using detail::modulate_alpha_add_alpha_texture_operator_tag;
using detail::modulate_inv_alpha_add_color_texture_operator_tag;
using detail::modulate_inv_alpha_add_alpha_texture_operator_tag;
using detail::bump_env_map_texture_operator_tag;
using detail::bump_env_map_luminance_texture_operator_tag;
using detail::dot_product3_texture_operator_tag;
using detail::multiplay_add_texture_operator_tag;
using detail::lerp_texture_operator_tag;

using detail::mask_texture_arg_tag;
using detail::diffuse_texture_arg_tag;
using detail::current_texture_arg_tag;
using detail::texture_texture_arg_tag;
using detail::texture_factor_texture_arg_tag;
using detail::specular_texture_arg_tag;
using detail::temp_texture_arg_tag;
using detail::const_texture_arg_tag;
using detail::complement_texture_arg_tag;
using detail::alpha_peplicate_texture_arg_tag;

using detail::texture_stage_adaptor;

using detail::add_color;
using detail::modultate2_color;
using detail::modultate4_color;
}