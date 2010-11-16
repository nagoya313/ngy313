#pragma once
#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>
#include "detail/window_singleton.hpp"
#include "detail/texture.hpp"

namespace ngy313 { namespace detail {
template <typename Image>
class image_base {
 public:
  explicit image_base(const string_piece &file_name)
      : texture_(init_key(file_name)) {}

 private:
  friend typename Image;

  texture_key init_key(const string_piece &file_name) {
    const detail::texture_key key = {
      detail::graphic_device(), file_name.string()
    };
    return key;
  }

  const boost::flyweights::flyweight<
            boost::flyweights::key_value<detail::texture_key, 
                                         detail::texture_data>> texture_;
};

}}