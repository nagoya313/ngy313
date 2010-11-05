#pragma once
#include "drawable_adaptor.hpp"

namespace ngy313 {
template <typename Drawable>
struct drawable_filter_adaptor : public Drawable::adaptor_type {};
}