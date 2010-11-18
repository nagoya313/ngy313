#pragma once
#include "detail/texture_base.hpp"
#include "detail/drawable_core_access.hpp"
#include "drawable_adaptor_base.hpp"
#include "image.hpp"

namespace ngy313 { namespace detail {
template <typename Drawable>
struct imaged_adaptor : public all_vertex_adaptor<Drawable>, public texture_base {
  imaged_adaptor(const Drawable &drawable, const image &img) 
      : all_vertex_adaptor(drawable), texture_base(drawable_core_access::texture1(img)) {}
};

struct imaged : public adaptor_result<imaged_adaptor> {
  explicit imaged(const image &img) : image_(img) {}

  template <typename Drawable>
  imaged_adaptor<Drawable> operator ()(const Drawable &drawable) const {
    return imaged_adaptor<Drawable>(drawable, image_);
  }

 private:
  const image image_;
};
}}

namespace ngy313 {
using detail::imaged;
}