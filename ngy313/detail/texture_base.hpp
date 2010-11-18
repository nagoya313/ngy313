#pragma once
#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>
#include "string_piece.hpp"
#include "drawable_core_access.hpp"
#include "texture.hpp"

namespace ngy313 { namespace detail {
class texture_base {
 public:
  typedef texture_base image_type;
  typedef texture_base image1_type;

  explicit texture_base(const texture_type &texture) : texture1_(texture) {}

 private:
  friend drawable_core_access;

  const texture_type texture1_;
};

class texture2_base {
 public:
  typedef texture2_base image_type;
  typedef texture2_base image2_type;

  texture2_base(const texture_type &texture1, const texture_type &texture2) 
      : texture1_(texture1), texture2_(texture2) {}

 private:
  friend drawable_core_access;

  const texture_type texture1_;
  const texture_type texture2_;
};
}}