#pragma once
#include "detail/drawable_filter.hpp"
#include "detail/drawable_core_access.hpp"
#include "drawable_adaptor.hpp"

namespace ngy313 {
template <typename Drawable>
struct drawable_filter_adaptor : public Drawable::adaptor_type {
  friend drawable_core_access;

  explicit drawable_filter_adaptor(const Drawable &drawable) 
    : drawable_(drawable) {
  }

 private:
  typename Drawable::vertex_range_type vertex_range() const {
    return drawable_core_access::vertex_range(drawable_);
  }

  const Drawable &drawable_;
};
}