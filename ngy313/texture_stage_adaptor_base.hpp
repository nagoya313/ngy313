#pragma once
#include "drawable_adaptor_base.hpp"

namespace ngy313 { namespace detail {
template <typename Drawable, typename ColorStage, typename AlphaStage>
struct texture_stage_adaptor_base
    : public all_vertex_adaptor<Drawable>, public texture_stage_type<texture_stage_pair<ColorStage, AlphaStage>> {
  explicit texture_stage_adaptor_base(const Drawable &drawable) : all_vertex_adaptor(drawable) {}
};
}}

namespace ngy313 {
template <typename ColorStage, typename AlphaStage = void>
struct texture_stage_adaptor {
  template <typename Signature>
  struct result {
    typedef detail::texture_stage_adaptor_base<typename detail::copy_argument<Signature>::type,
                                               ColorStage,
                                               AlphaStage> type;
  };

  template <typename Drawable>
  detail::texture_stage_adaptor_base<Drawable, ColorStage, AlphaStage> operator ()(const Drawable &drawable) const {
    return detail::texture_stage_adaptor_base<Drawable, ColorStage, AlphaStage>(drawable);
  }
};
}