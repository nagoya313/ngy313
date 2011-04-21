#ifndef NGY313_GRAPHIC_UV_REVERSED_HPP_
#define NGY313_GRAPHIC_UV_REVERSED_HPP_
#include <ngy313/graphic/uv_extended.hpp>
#include <ngy313/graphic/base_point.hpp>

namespace ngy313 { namespace graphic {
const uv_extended_t<0, base_point_set_center_t> uv_reversed0(base_point_set_center, -1.f, -1.f);
const uv_extended_t<0, base_point_set_center_t> uv_reversed0(base_point_set_center, -1.f, 1.f);
const uv_extended_t<0, base_point_set_center_t> uv_reversed0(base_point_set_center, 1.f, -1.f);
const uv_extended_t<0, base_point_set_center_t> uv_reversed1(base_point_set_center, -1.f);
const uv_extended_t<1, base_point_set_center_t> uv_reversed1(base_point_set_center, -1.f, 1.f);
const uv_extended_t<1, base_point_set_center_t> uv_reversed1(base_point_set_center, 1.f, -1.f);
}}

#endif
