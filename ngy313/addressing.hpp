#pragma once
#include "detail/addressing.hpp"

namespace ngy313 { namespace detail {
const addressing_adaptor<clamp_addressing_tag, clamp_addressing_tag> clamp_addressing = {};
const addressing_adaptor<mirror_addressing_tag, mirror_addressing_tag> mirror_addressing = {};
}}

namespace ngy313 {
using detail::addressing_tag;
using detail::wrap_addressing_tag;
using detail::mirror_addressing_tag;
using detail::clamp_addressing_tag;

using detail::addressing_adaptor;

using detail::clamp_addressing;
using detail::mirror_addressing;
}
