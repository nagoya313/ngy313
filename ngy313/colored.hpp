#pragma once
#include <cstdint>
#include <pstade/oven/any_range.hpp>
#include <pstade/oven/transformed.hpp>
#include "drawable_filter_adaptor.hpp"

namespace ngy313 {
template <typename Drawable>
class colored_filter : public drawable_filter_adaptor<Drawable> {
 public:
  colored_filter(const Drawable &drawable, const std::uint32_t color) 
      : drawable_filter_adaptor(drawable), 
        transform_color_(color) {}

 private:
  const struct transform_color {
    template <typename Signature>
    struct result {
      typedef typename std::remove_reference<Signature>::type type;
    };

    explicit transform_color(const std::uint32_t color) : color_(color) {}

    template <typename Vertex>
    Vertex operator ()(Vertex &vertex) const {
      member_at<diffuse_t>(vertex).diffuse = color_;
      return vertex;
    }

   private:
    const std::uint32_t color_;
  } transform_color_;
};
}

namespace ngy313 { namespace detail {
class colored {
 public:
  template <typename Signature>
  struct result {  
    typedef colored_filter<typename copy_argument<Signature>::type> type;
  };

  explicit colored(const std::uint32_t col) : color_(col) {}

  template <typename Drawable>
  colored_filter<Drawable> operator ()(const Drawable &drawable) const {
    return colored_filter<Drawable>(drawable, color_);
  }

 private:
  const std::uint32_t color_;
};
}}

namespace ngy313 {
using detail::colored;
}