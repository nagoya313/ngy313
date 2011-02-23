#pragma once
#include <ngy313/window/detail/message_box.hpp>

namespace ngy313 { namespace window {
class main_window;

inline
void message_box(const utility::string_piece &message, 
                 const utility::string_piece &caption,
                 const icon_code icon) {
  detail::message_box(message, caption, icon);
}

// �C���X�^���X�x�[�X�ł�������ق���������������Ȃ�
inline
void message_box(const main_window &main_wnd,
                 const utility::string_piece &message, 
                 const utility::string_piece &caption,
                 const icon_code icon) {
  // ������
  //detail::message_box(message, caption, icon);
}
}}
