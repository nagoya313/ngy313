#ifndef NGY313_UTILITY_DECLVAL_HPP_
#define NGY313_UTILITY_DECLVAL_HPP_
#include <type_traits>

namespace ngy313 { namespace utility {
// •W€‚Ì‚ª—ˆ‚½‚ç‚³‚Á‚³‚Æ”jŠü
template <typename T>
typename std::add_rvalue_reference<T>::type declval();
}}

#endif

