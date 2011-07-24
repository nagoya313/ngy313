#ifndef NGY313_DETAIL_GTKMM_MAIN_HPP_
#define NGY313_DETAIL_GTKMM_MAIN_HPP_

#include <cstdint>
#include <exception>
#include <memory>
#include <boost/noncopyable.hpp>
#include <gtkmm.h>

namespace ngy313 { namespace detail {
class gtkmm_main : boost::noncopyable {
 public:
  gtkmm_main()
      : main_(0, nullptr), throw_(false), exception_() {}

  template <typename Pred>
  int run(const Pred pred) {
  	Glib::add_exception_handler(
  	    sigc::mem_fun(this, &gtkmm_main::error_handler));
    const main_loop<Pred> update(pred);
    Glib::signal_timeout().connect(
    		 sigc::mem_fun(&update,
                      &main_loop<Pred>::update),
                         16);
    Gtk::Main::run();
    if (throw_) {
      std::rethrow_exception(exception_);
    }
    return 0;
  }

  static void quit() {
    Gtk::Main::quit();
  }

  static void sleep(std::uint32_t time) {
    Glib::usleep(time);
  }

 private:
  void error_handler() {
   throw_ = true;
  	exception_ = std::current_exception();
   quit();
  }

  template <typename Pred> 
  class main_loop {
   public:
    explicit main_loop(const Pred pred) : pred_(pred) {}
       
    bool update() const {
      pred_();
      return true;
    }

   private:
    const Pred pred_;
  };

  Gtk::Main main_;
  bool throw_;
  std::exception_ptr exception_;
};
}}

#endif
