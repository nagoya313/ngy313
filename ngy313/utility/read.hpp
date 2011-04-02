#ifndef NGY313_UTILITY_READ_HPP_
#define NGY313_UTILITY_READ_HPP_
#include <type_traits>

namespace ngy313 { namespace utility {
// �ǂ����ɂ��̎�̃R�[�h�͂��肻���Ȃ��̂����E�E�E
// remove_const�̕ӂ�Ŗ�肪�u�����˂Ȃ��̂ŗ���
template <typename T, typename Stream>
typename std::remove_const<T>::type read(Stream &stream) {
  typename std::remove_const<T>::type t;
  stream.read(reinterpret_cast<char *>(&t), sizeof(t));
  return t;
}
}}

#endif

