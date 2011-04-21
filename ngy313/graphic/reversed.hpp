#ifndef NGY313_GRAPHIC_REVERSED_HPP_
#define NGY313_GRAPHIC_REVERSED_HPP_
#include <ngy313/graphic/extended.hpp>
#include <ngy313/graphic/base_point.hpp>

namespace ngy313 { namespace graphic {
const extended_t<base_point_set_center_t> reversed(base_point_set_center, -1.f, -1.f);
const extended_t<base_point_set_center_t> reversed(base_point_set_center, -1.f, 1.f);
const extended_t<base_point_set_center_t> reversed(base_point_set_center, 1.f, -1.f);
}}

#endif
