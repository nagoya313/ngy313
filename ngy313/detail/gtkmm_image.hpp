#ifndef NGY313_DETAIL_GTKMM_IMAGE_HPP_
#define NGY313_DETAIL_GTKMM_IMAGE_HPP_

#include <stdexcept>
#include <type_traits>
#include <gtkmm.h>
#include <ngy313/string_wrap.hpp>
#include <ngy313/detail/image.hpp>
#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/io/png_io.hpp>

namespace ngy313 { namespace detail {
template <typename Texture>
class gtkmm_image : public image_base<Texture> {
  class loader {
   public:
    explicit loader(const string_wrap &file_name)
	    : file_name_(file_name.string()) {}

   template <typename Device,
                    typename Result = typename Texture::texture_tuple,
                    typename Handle = typename std::remove_reference<
                                                       typename Texture::handle_type>::type,
                    typename Deleter = typename Texture::deleter_type>
    Result operator ()(const Device &device) const {
      try {
        const Glib::RefPtr<Gdk::Pixbuf> pixel(
  	  	  	Gdk::Pixbuf::create_from_file(file_name_.c_str()));
        const Handle id(new GLuint(), Deleter(device));
        glEnable(GL_TEXTURE_2D);
        glGenTextures(1, id.get());
        glBindTexture(GL_TEXTURE_2D, *id);
        gluBuild2DMipmaps(GL_TEXTURE_2D,
                                    GL_RGBA,
                                    pixel->get_width(),
                                    pixel->get_height(),
                                    GL_RGBA,
                                    GL_UNSIGNED_BYTE,
                                    pixel->get_pixels());
        return Result(id, pixel->get_width(), pixel->get_height());
     } catch(const Glib::Error &error) {
  	throw std::runtime_error("画像の読み込みに失敗しました");
     }
   }

   private:
    std::string file_name_;
  };
 public:
  explicit gtkmm_image(const string_wrap &file_name)
	    : texture_(loader(file_name)) {}

  virtual int width() const {
    return texture_.width();
  }

  virtual int height() const {
    return texture_.height();
  }

  virtual const Texture &get_texture() const {
    return texture_;
  }

 private:
  Texture texture_;
};
}}

#endif
