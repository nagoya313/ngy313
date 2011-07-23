#ifndef NGY313_DETAIL_IMAGE
#define NGY313_DETAIL_IMAGE

namespace ngy313 { namespace detail {
template <typename Texture>
class image_base {
public:
  virtual ~image_base() {}

  virtual int width() const = 0;
  virtual int height() const = 0;
  virtual const Texture &get_texture() const = 0;
};
}}

#endif