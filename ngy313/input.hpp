#pragma once
#include <cstddef>
#include <array>
#include <bitset>
#include <boost/signals2/trackable.hpp>
#include <pstade/oven/algorithm.hpp>
#include <pstade/oven/counting.hpp>
#include "key_code.hpp"

namespace ngy313 { namespace detail {
template <std::size_t N>
struct controller_data : public boost::signals2::trackable {
  template <typename Range>
  explicit controller_data(const Range &range) : key_(), 
                                                 repeat_(),
                                                 repeat_cnt_(30),
                                                 down_bit_(0), 
                                                 before_bit_(0), 
                                                 up_bit_(0),
                                                 trig_bit_(0) {
    pstade::oven::copy(range, key_.begin());
  }

  void set() {
    before_bit_ = down_bit_;
    pstade::oven::for_each(pstade::oven::counting(0, N), [this](const int x) {
      down_bit_[x] = pressed(key_[x]);
      repeat_[x] = down_bit_[x] ? (std::min)(repeat_cnt_, repeat_[x] + 1) : 0;
    });
    trig_bit_ = down_bit_ & ~before_bit_;
    up_bit_ = ~down_bit_ & before_bit_;
  }

  std::array<key_code, N> key_;
  std::array<std::uint32_t, N> repeat_;
  std::uint32_t repeat_cnt_;
  std::bitset<N> down_bit_;
  std::bitset<N> before_bit_;
  std::bitset<N> up_bit_;
  std::bitset<N> trig_bit_;
};
}}

namespace ngy313 {
template <std::size_t N>
class controller {
 public:
  template <typename Range>
  explicit controller(const Range &range) : data_(range) {
    detail::input_callback().connect(boost::bind(&detail::controller_data<N>::set, &data_));
  }

  std::uint32_t repeat_count() const {
    return data_.repeat_cnt_;
  }

  void set_repeat_count(const std::uint32_t count) {
    return data_.repeat_cnt_ = count;
  }

  template <std::size_t M>
  key_code key() const {
    static_assert(N > M, "");
    return data_.key_[M];
  }

  template <std::size_t M>
  void change_key(const key_code key) {
    static_assert(N > M, "");
    data_.key_[M] = key;
  }

  template <std::size_t M>
  bool down() const {
    static_assert(N > M, "");
    return data_.down_bit_[M];
  }

  template <std::size_t M>
  bool triger() const {
    static_assert(N > M, "");
    return data_.trig_bit_[M];
  }

  template <std::size_t M>
  bool up() const {
    static_assert(N > M, "");
    return data_.up_bit_[M];
  }

  template <std::size_t M>
  bool repeat_triger() const {
    static_assert(N > M, "");
    return data_.trig_bit_[M] || data_.repeat_[M] == data_.repeat_cnt_;
  }

 private:
  detail::controller_data<N> data_;
};
}