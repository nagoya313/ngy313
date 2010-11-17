#pragma once
#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>
#include "string_piece.hpp"
#include "drawable_core_access.hpp"
#include "texture.hpp"

namespace ngy313 { namespace detail {
class image_base {
 public:
  typedef image_base image_type;
  typedef image_base image1_type;

  explicit image_base(const string_piece &file_name)
      : texture1_(init_key(file_name)) {}

  float width() const {
    return texture1_.get().width;
  }

  float height() const {
    return texture1_.get().height;
  }

 private:
  friend drawable_core_access;

  const texture_type texture1_;
};

class image2_base {
 public:
  typedef image_base image_type;
  typedef image_base image2_type;

  explicit image2_base(const string_piece &file_name1,
                       const string_piece &file_name2)
      : texture1_(init_key(file_name1)),
        texture2_(init_key(file_name2)) {}

 private:
  friend drawable_core_access;

  const texture_type texture1_;
  const texture_type texture2_;
};
}}