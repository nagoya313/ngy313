#pragma once
#include <ngy313/graphic/extended.hpp>
#include <ngy313/graphic/base_point.hpp>

namespace ngy313 { namespace graphic {
const extended_t<base_point_set_center_t> reversed(base_point_set_center, -1.f);
const extended_one_t<base_point_set_center_t, position_x> reversed_x(base_point_set_center, -1.f);
const extended_one_t<base_point_set_center_t, position_y> reversed_y(base_point_set_center, -1.f);
}}
