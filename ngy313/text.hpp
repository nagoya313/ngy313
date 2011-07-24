#ifndef NGY313_TEXT_HPP_
#define NGY313_TEXT_HPP_

#include <memory>
#include <ngy313/fwd.hpp>
#include <ngy313/string_wrap.hpp>
#include <ngy313/drawable_traits.hpp>
#include <ngy313/texture.hpp>
#include <ngy313/vector.hpp>
#include <ngy313/detail/image.hpp>

#if defined(_WIN32)
#elif defined(__linux__)
#include <ngy313/detail/cairomm_text.hpp>
#endif

namespace ngy313 {
template <typename Text>
class basic_text_image {
 public:
	template <typename Font>
  explicit basic_text_image(const basic_font<Font> &font,
                            const string_wrap &text)
	    : text_(std::make_shared<Text>(font, text)) {}
	
	int width() const {
    return text_->width();
	}

	int height() const {
	  return text_->height();
	}
	
	std::string text() const {
		return text_->text();
	}

	const std::shared_ptr<Text> &get_image() const {
	  return text_;
	}

 private:
  std::shared_ptr<Text> text_;
};

template <typename Text>
class basic_text : public drawable_traits<basic_text<Text>,
                                                4,
                                                2,
                                          image_2d_fvf_tag,
                                          triangle_strip_primitive_tag> {
	typedef typename basic_text::drawable_traits base_;
	typedef typename base_::vertex_type vertex_type_;
	typedef typename base_::vertex_array_type vertex_array_type_;
	
 public:
	template <typename Font>
  explicit basic_text(const basic_font<Font> &font,
                      const string_wrap &text)
      : text_(font, text), vertex_(init(text_.get_image()->get_texture())) {}

  vertex_array_type_ vertex() const {
    return vertex_;
  }

  const texture &texture1() const {
    return text_.get_image()->get_texture();
  }
  
 private:
  static vertex_array_type_ init(const texture &tex) {
    const vertex_array_type_ vertex = {{
      vertex_type_(rhw_position_t(vector2(0.f, 0.f)),
                   texture_t<1>(vector2(0.f, 0.f))),
      vertex_type_(rhw_position_t(
                       vector2(static_cast<float>(tex.width()), 0.f)),
                   texture_t<1>(vector2(1.f, 0.f))),
      vertex_type_(rhw_position_t(
                       vector2(0.f, static_cast<float>(tex.height()))),
                   texture_t<1>(vector2(0.f, 1.f))),
       vertex_type_(rhw_position_t(
                    vector2(static_cast<float>(tex.width()),
                            static_cast<float>(tex.height()))),
       		         texture_t<1>(vector2(1.f, 1.f)))
      }};
     return vertex;
    }

   basic_text_image<Text> text_;
   vertex_array_type_ vertex_;
};

#if defined(_WIN32)
#elif defined(__linux__)
typedef basic_text_image<detail::cairomm_text_image<texture>> text_image;
typedef basic_text<detail::cairomm_text_image<texture>> text;
#endif

}

#endif