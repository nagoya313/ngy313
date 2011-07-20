#ifndef NGY313_DETAIL_GTKMM_ICON_HPP_
#define NGY313_DETAIL_GTKMM_ICON_HPP_

#include <stdexcept>
#include <boost/noncopyable.hpp>
#include <gtkmm.h>
#include <ngy313/string_wrap.hpp>

namespace ngy313 { namespace detail {
class gtkmm_icon : boost::noncopyable {
 public:
  typedef Glib::RefPtr<Gdk::Pixbuf> handle_type;

  explicit gtkmm_icon(const string_wrap &file_name)
      : pixel_(init_icon(file_name)) {}
      
  Glib::RefPtr<Gdk::Pixbuf> handle() const {
    return pixel_;
  }
  
 private:
  static Glib::RefPtr<Gdk::Pixbuf> init_icon(const string_wrap &file_name) {
    try {
    	return Gdk::Pixbuf::create_from_file(file_name.c_str());
    } catch(const Glib::Error &error) {
    	throw std::runtime_error("アイコンの読み込みに失敗しました");
    }
  }

  const Glib::RefPtr<Gdk::Pixbuf> pixel_;
};
}}

#endif
