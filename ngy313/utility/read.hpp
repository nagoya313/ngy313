#pragma once
#include <type_traits>

namespace ngy313 { namespace utility {
template <typename T, typename Stream>
typename std::remove_const<T>::type read(Stream &stream) {
  typename std::remove_const<T>::type t;
  stream.read(reinterpret_cast<char *>(&t), sizeof(t));
  return t;
}
}}