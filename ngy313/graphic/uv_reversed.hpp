#pragma once
#include <ngy313/graphic/uv_extended.hpp>
#include <ngy313/graphic/base_point.hpp>

namespace ngy313 { namespace graphic {
const uv_extended_t<0, base_point_set_center_t> uv_reversed0(base_point_set_center, -1.f);
const uv_extended_one_t<0, base_point_set_center_t, tex_u> uv_reversed_u0(base_point_set_center, -1.f);
const uv_extended_one_t<0, base_point_set_center_t, tex_v> uv_reversed_v0(base_point_set_center, -1.f);
const uv_extended_t<0, base_point_set_center_t> uv_reversed1(base_point_set_center, -1.f);
const uv_extended_one_t<1, base_point_set_center_t, tex_u> uv_reversed_u1(base_point_set_center, -1.f);
const uv_extended_one_t<1, base_point_set_center_t, tex_v> uv_reversed_v1(base_point_set_center, -1.f);
}}
