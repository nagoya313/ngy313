#ifndef NGY313_DETAIL_CAIROMM_FONT_HPP_
#define NGY313_DETAIL_CAIROMM_FONT_HPP_

#include <string>
#include <cairomm/cairomm.h>
#include <ngy313/string_wrap.hpp>

namespace ngy313 { namespace detail {
class cairomm_font {
public:
	typedef const Cairo::RefPtr<Cairo::Context> &handle_type;
	
	explicit cairomm_font(const string_wrap &name, int size)
      : name_(name.string()), size_(size) {}
	
	std::string name() const {
    return name_;
	}
	
	int size() const {
    return size_;
	}
	
	handle_type handle() const {
    static const auto image = Cairo::ImageSurface::create(
                                  Cairo::FORMAT_ARGB32, 0, 0);
    static const auto context = Cairo::Context::create(image);
    context->select_font_face(name(),
                               Cairo::FONT_SLANT_NORMAL,
                               Cairo::FONT_WEIGHT_NORMAL );
    context->set_font_size(size());
    return context;
	}
	
 private:
	std::string name_;
	int size_;
};
}}

#endif