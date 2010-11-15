#pragma once
#include "blend_adaptor_base.hpp"

namespace ngy313 { namespace detail {
const blend_adaptor<src_alpha_blend_tag, one_blend_tag> add_blend = {};
}}

namespace ngy313 {
using detail::add_blend;
}