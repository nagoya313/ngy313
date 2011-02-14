#pragma once
#include <cstdint>
#include <algorithm>
#include <array>
#include <bitset>
#include <boost/fusion/include/count_if.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <boost/range/irange.hpp>
#include <boost/variant.hpp>
#include <ngy313/input/joypad.hpp>
#include <ngy313/input/keybord.hpp>
#include <ngy313/input/mouse.hpp>

namespace ngy313 { namespace input {
typedef boost::variant<keybord::key_code, mouse::key_code, joypad::key_data> key_code_type; 

typedef boost::variant<boost::fusion::vector<key_code_type>,
                       boost::fusion::vector<key_code_type, key_code_type>,
                       boost::fusion::vector<key_code_type, key_code_type, key_code_type>> controller_element;

inline
boost::fusion::vector<key_code_type> make_controller_element(const key_code_type code) {
  return boost::fusion::make_vector(code);
}

inline
boost::fusion::vector<key_code_type, key_code_type>
    make_controller_element(const key_code_type code1, const key_code_type code2) {
  return boost::fusion::make_vector(code1, code2);
}

inline
boost::fusion::vector<key_code_type, key_code_type, key_code_type>
    make_controller_element(const key_code_type code1, const key_code_type code2, const key_code_type code3) {
  return boost::fusion::make_vector(code1, code2, code3);
}

// ここいらは非公開化と名前をもう少しなんとかする
const struct pressed_t : public boost::static_visitor<bool> {
  bool operator ()(const keybord::key_code code) const {
    return keybord::key_pressed(code);
  }

  bool operator ()(const mouse::key_code code) const {
    return mouse::key_pressed(code);
  }

  // ジョイパッドは頑張れば最適化かけられる可能性がある
  bool operator ()(const joypad::key_data &code) const {
    return joypad::key_pressed(code.num, code.code);
  }
} pressed = pressed_t();

const struct pressed_pred_t {
  template <typename Fusion>
  bool operator ()(const Fusion &fusion) const {
    return boost::apply_visitor(pressed, fusion);
  }
} pressed_pred = {};

const struct key_pressed_t : public boost::static_visitor<bool> {
  template <typename Fusion>
  bool operator ()(const Fusion &fusion) const {
    return boost::fusion::count_if(fusion, pressed_pred) != 0;
  }
} key_pressed = key_pressed_t();
// なんとかするここまで

template <std::size_t N>
class controller {
 public:
  template <typename Range>
  explicit controller(const Range &range) : key_(),
                                            repeat_(),
                                            repeat_cnt_(30),
                                            down_bit_(0), 
                                            before_bit_(0), 
                                            up_bit_(0),
                                            trig_bit_(0) {
    boost::copy(range, key_.begin());
  }

  void pool() {
    before_bit_ = down_bit_;
    boost::for_each(boost::irange(0u, N), [this](const int x) {
      down_bit_[x] = boost::apply_visitor(key_pressed, key_[x]);
      repeat_[x] = down_bit_[x] ? (std::min)(repeat_cnt_, repeat_[x] + 1) : 0;
    });
    trig_bit_ = down_bit_ & ~before_bit_;
    up_bit_ = ~down_bit_ & before_bit_;
  }

  std::uint32_t repeat_count() const {
    return repeat_cnt_;
  }

  void set_repeat_count(const std::uint32_t count) {
    repeat_cnt_ = count;
  }

  controller_element key(const int index) const {
    return key_.at(index);
  }

  void change_key(const int index, const controller_element &key) {
    key_.at(index) = key;
  }

  bool down(const int index) const {
    return down_bit_.at(index);
  }

  bool triger(const int index) const {
    return trig_bit_.at(index);
  }

  bool up(const int index) const {
    return up_bit_.at(index);
  }

  bool repeat_triger(const int index) const {
    return trig_bit_.at(index) || repeat_.at(index) == repeat_cnt_;
  }

 private:
  std::array<controller_element, N> key_;
  std::array<std::uint32_t, N> repeat_;
  std::uint32_t repeat_cnt_;
  std::bitset<N> down_bit_;
  std::bitset<N> before_bit_;
  std::bitset<N> up_bit_;
  std::bitset<N> trig_bit_;
};
}}
