#pragma once
#include "texture_stage_adaptor_base.hpp"

namespace ngy313 { namespace detail {
const texture_stage_adaptor<color_stage<texture_texture_arg_tag, 
                                        add_texture_operator_tag,
                                        diffuse_texture_arg_tag>> add_color = {};
}}

namespace ngy313 {
using detail::add_color;
}