#ifndef NGY313_UTILITY_READ_HPP_
#define NGY313_UTILITY_READ_HPP_
#include <type_traits>

namespace ngy313 { namespace utility {
// どこかにこの手のコードはありそうなものだが・・・
// remove_constの辺りで問題が置きかねないので留意
template <typename T, typename Stream>
typename std::remove_const<T>::type read(Stream &stream) {
  typename std::remove_const<T>::type t;
  stream.read(reinterpret_cast<char *>(&t), sizeof(t));
  return t;
}
}}

#endif

