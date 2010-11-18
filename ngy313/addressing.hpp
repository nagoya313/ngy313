#pragma once
#include "addressing_adaptor_base.hpp"

namespace ngy313 { namespace detail {
const addressing_adaptor<clamp_addressing_tag, clamp_addressing_tag> clamp_addressing = {};
}}

namespace ngy313 {
using detail::clamp_addressing;
}