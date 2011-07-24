#ifndef NGY313_DETAIL_CAIROMM_TEXT_HPP_
#define NGY313_DETAIL_CAIROMM_TEXT_HPP_

#include <string>
#include <cairomm/cairomm.h>
#include <ngy313/fwd.hpp>
#include <ngy313/string_wrap.hpp>
#include <ngy313/detail/image.hpp>

namespace ngy313 { namespace detail {
template <typename Texture>
class cairomm_text_image : public image_base<Texture> {
	class creater {
	 public:
    template <typename Font>
    explicit creater(const basic_font<Font> &font,
                     const string_wrap &text) 
        : text_(text.string()), 
          extents_(extents(font)),
          surface_(Cairo::ImageSurface::create(
                       Cairo::FORMAT_ARGB32,
                       extents_.width, 
                       extents_.height)),
          context_(Cairo::Context::create(surface_)) {
      context_->select_font_face(font.name(),
                                 Cairo::FONT_SLANT_NORMAL,
                                 Cairo::FONT_WEIGHT_NORMAL );
      context_->set_font_size(font.size());
    }
    
    template <typename Device,
              typename Result = typename Texture::texture_tuple,
              typename Handle = typename std::remove_reference<
                                    typename Texture::handle_type>::type,
              typename Deleter = typename Texture::deleter_type>
    Result operator ()(const Device &device) const {  
      context_->set_source_rgba(1.0, 1.0, 1.0, 1.0);
      context_->move_to(-extents_.x_bearing, -extents_.y_bearing);
      context_->show_text(text_);
      const Handle id(new GLuint(), Deleter(device));
      glEnable(GL_TEXTURE_2D);
      glGenTextures(1, id.get());
      glBindTexture(GL_TEXTURE_2D, *id);
      gluBuild2DMipmaps(GL_TEXTURE_2D,
                        GL_RGBA,
                        surface_->get_width(),
                        surface_->get_height(),
                        GL_RGBA,
                        GL_UNSIGNED_BYTE,
                        surface_->get_data());
      return Result(id, surface_->get_width(), surface_->get_height());
    }

    
	 private:
    template <typename Font>
    Cairo::TextExtents extents(const basic_font<Font> &font) {
      Cairo::TextExtents text_extents;
      font.handle()->get_text_extents(text_, text_extents);
      return text_extents;
    }
    
    std::string text_;
    Cairo::TextExtents extents_;
    Cairo::RefPtr<Cairo::ImageSurface> surface_;
    Cairo::RefPtr<Cairo::Context> context_;
	};
	
 public:
	template <typename Font>
	explicit cairomm_text_image(const basic_font<Font> &font,
	                            const string_wrap &text)
	    : texture_(creater(font, text)) {}
	
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