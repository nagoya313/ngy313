#pragma once
#include "detail/blend.hpp"

namespace ngy313 { namespace detail {
const blend_adaptor<src_alpha_blend_tag, one_blend_tag> add_blend = {};
const blend_adaptor<zero_blend_tag, inv_src_color_blend_tag> sub_blend = {};
const blend_adaptor<zero_blend_tag, src_color_blend_tag> mul_blend = {};
const blend_adaptor<dest_color_blend_tag, src_color_blend_tag> mul2_blend = {};
const blend_adaptor<inv_dest_color_blend_tag, one_blend_tag> screen_blend = {};
const blend_adaptor<inv_dest_color_blend_tag, inv_src_color_blend_tag> reverse_blend = {};
}}

namespace ngy313 {
using detail::one_blend_tag;
using detail::src_alpha_blend_tag;
using detail::inv_src_alpha_blend_tag;
using detail::dest_alpha_blend_tag;
using detail::inv_dest_alpha_blend_tag;
using detail::zero_blend_tag;
using detail::src_color_blend_tag;
using detail::inv_src_color_blend_tag;
using detail::dest_color_blend_tag;
using detail::inv_dest_color_blend_tag;

using detail::blend_adaptor;

using detail::add_blend;
using detail::sub_blend;
using detail::mul_blend;
using detail::mul2_blend;
using detail::screen_blend;
using detail::reverse_blend;
}