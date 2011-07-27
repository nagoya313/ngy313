#ifndef NGY313_DETAIL_GTKMM_INITIALIZER_HPP_
#define NGY313_DETAIL_GTKMM_INITIALIZER_HPP_

#include <boost/noncopyable.hpp>
#include <gtkmm.h>

namespace ngy313 { namespace detail {
class gtkmm_initializer : boost::noncopyable {
 public:	
  gtkmm_initializer() {
    static Gtk::Main main(0, nullptr);
  }
};
}}

#endif
