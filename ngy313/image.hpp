#pragma once
#include "detail/string_piece.hpp"
#include "detail/drawable_core_access.hpp"
#include "detail/texture.hpp"

namespace ngy313 {
class image {
 public: 
  explicit image(const string_piece &file_name) : texture1_(detail::init_key(file_name)) {}

  float width() const {
    return texture1_.get().width;
  }

  float height() const {
    return texture1_.get().height;
  }

 private:
  friend detail::drawable_core_access;

  const detail::texture_type texture1_;
};
} 