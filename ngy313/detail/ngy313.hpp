#ifndef NGY313_DETAIL_NGY313_HPP_
#define NGY313_DETAIL_NGY313_HPP_

#include <ngy313/detail/main_singleton.hpp>
#include <ngy313/detail/main.hpp>
#include <ngy313/detail/window.hpp>
#include <ngy313/detail/graphic.hpp>
#include <ngy313/detail/sound.hpp>

namespace ngy313 { namespace detail {
typedef basic_main_singleton<main,
                             window,
                             graphic_system,
                             sound_system> main_singleton; 
}}

#endif
