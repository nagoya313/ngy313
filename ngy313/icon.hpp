#ifndef NGY313_ICON_HPP_
#define NGY313_ICON_HPP_

#include <boost/noncopyable.hpp>
#include <ngy313/string_wrap.hpp>
#include <ngy313/detail/ngy313.hpp>

#if defined(_WIN32)
#include <ngy313/detail/win32_icon.hpp>
#elif defined(__linux__)
#include <ngy313/detail/gtkmm_icon.hpp>
#endif

namespace ngy313 { namespace detail {
struct init_base {
	init_base() {
		detail::main_singleton::instance();
	}
};
}}

namespace ngy313 {
template <typename Icon>
class basic_icon : detail::init_base, boost::noncopyable {
 public:
  explicit basic_icon(const string_wrap &file_name)
      : icon_(file_name) {}
      
  typename Icon::handle_type handle() const {
    return icon_.handle();
  }
  
 private:
  const Icon icon_;
};

#if defined(_WIN32)
typedef basic_icon<detail::win32_icon> icon; 
#elif defined(__linux__)
typedef basic_icon<detail::gtkmm_icon> icon;
#endif
}

#endif