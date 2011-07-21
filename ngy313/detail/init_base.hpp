#ifndef NGY313_DETAIL_INIT_BASE_HPP_
#define NGY313_DETAIL_INIT_BASE_HPP_

#include <ngy313/detail/ngy313.hpp>

namespace ngy313 { namespace detail {
struct init_base {
	init_base() {
		detail::main_singleton::instance().main();
	}
};
}}

#endif