#pragma once
#include <ngy313/input/joypad.hpp>
#include <ngy313/input/keybord.hpp>
#include <ngy313/input/mouse.hpp>

namespace ngy313 { namespace input { namespace detail {
// ここいらは非公開化と名前をもう少しなんとかする
const struct pressed_functor_t : public boost::static_visitor<bool> {
  bool operator ()(const keybord::key_code code) const {
    return keybord::key_pressed(code);
  }

  bool operator ()(const mouse::key_code code) const {
    return mouse::key_pressed(code);
  }

  // ジョイパッドは頑張れば最適化かけられる可能性がある
  bool operator ()(const joypad::key_data &code) const {
    return false;//joypad::key_pressed(code.num, code.code);
  }
} pressed_functor = pressed_functor_t();

const struct pressed_pred_t {
  template <typename Fusion>
  bool operator ()(const Fusion &fusion) const {
    return boost::apply_visitor(pressed_functor, fusion);
  }
} pressed_pred = {};

const struct key_pressed_t : public boost::static_visitor<bool> {
  template <typename Fusion>
  bool operator ()(const Fusion &fusion) const {
    return boost::fusion::count_if(fusion, pressed_pred) != 0;
  }
} key_pressed = key_pressed_t();
}}}
