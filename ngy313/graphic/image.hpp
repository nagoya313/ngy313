#pragma once
#include <ngy313/graphic/detail/texture.hpp>
#include <ngy313/utility/string_piece.hpp>

namespace ngy313 { namespace graphic {
class image {
 public: 
  explicit image(const utility::string_piece &file_name) : texture_(detail::init_texture_key(file_name)) {}

  float width() const {
    return texture_.get().width();
  }

  float height() const {
    return texture_.get().height();
  }

 private:
  const detail::texture_handle &texture1() const {
    return texture_.get().texture();
  }

  const detail::texture_type texture_;

  friend class detail::texture_access;
};
}}