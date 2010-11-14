#pragma once
#include <boost/preprocessor/repeat.hpp>

namespace ngy313 { namespace expr { 
struct add_t {
  static float x(const float lhs, const float rhs) {
    return lhs + rhs;
  }

  static float y(const float lhs, const float rhs) {
    return lhs + rhs;
  }
};

struct sub_t {
  static float x(const float lhs, const float rhs) {
    return lhs - rhs;
  }

  static float y(const float lhs, const float rhs) {
    return lhs - rhs;
  }
};

struct mul_t {
  static float x(const float lhs, const float rhs) {
    return lhs * rhs;
  }

  static float y(const float lhs, const float rhs) {
    return lhs * rhs;
  }
};

struct div_t {
  static float x(const float lhs, const float rhs) {
    return lhs / rhs;
  }

  static float y(const float lhs, const float rhs) {
    return lhs / rhs;
  }
};

struct plus_t {
  static float x(const float rhs) {
    return rhs;
  }

  static float y(const float rhs) {
    return rhs;
  }
};

struct minus_t {
  static float x(const float rhs) {
    return -rhs;
  }

  static float y(const float rhs) {
    return -rhs;
  }
};

template <typename Rhs, typename Ope>
struct expr1 {
  explicit expr1(const Rhs &rhs) : rhs_(rhs) {}

  float x() const {
    return Ope::x(rhs_.x());
  }

  float y() const {
    return Ope::y(rhs_.y());
  }

 private:
  const Rhs &rhs_;
};

template <typename Lhs, typename Rhs, typename Ope>
struct expr2 {
  expr2(const Lhs &lhs, const Rhs &rhs) : lhs_(lhs), rhs_(rhs) {}

  float x() const {
    return Ope::x(lhs_.x(), rhs_.x());
  }

  float y() const {
    return Ope::y(lhs_.y(), rhs_.y());
  }

 private:
  const Lhs &lhs_;
  const Rhs &rhs_;
};

template <typename Lhs, typename Ope>
struct expr2<Lhs, float, Ope> {
  expr2(const Lhs &lhs, const float rhs) : lhs_(lhs), rhs_(rhs) {}

  float x() const {
    return Ope::x(lhs_.x(), rhs_);
  }

 private:
  const Lhs &lhs_;
  const float rhs_;
};

template <typename Rhs, typename Ope>
struct expr2<float, Rhs, Ope> {
  expr2(const float lhs, const Rhs &rhs) : lhs_(lhs), rhs_(rhs) {}

  float x() const {
    return Ope::x(lhs_, rhs_.x());
  }

 private:
  const float slhs_;
  const Rhs &rhs_;
};

template <typename Lhs, typename Rhs>
expr2<Lhs, Rhs, add_t> operator +(const Lhs &lhs, const Rhs &rhs) {
  return expr2<Lhs, Rhs, add_t>(lhs, rhs);
}

template <typename Lhs, typename Rhs>
expr2<Lhs, Rhs, sub_t> operator -(const Lhs &lhs, const Rhs &rhs) {
  return expr2<Lhs, Rhs, sub_t>(lhs, rhs);
}

template <typename Lhs, typename Rhs>
inline
expr2<Lhs, Rhs, mul_t> operator *(const Lhs &lhs, const Rhs &rhs) {
  return expr2<Lhs, Rhs, mul_t>(lhs, rhs);
}

template <typename Lhs, typename Rhs>
expr2<Lhs, Rhs, div_t> operator /(const Lhs &lhs, const Rhs &rhs) {
  return expr2<Lhs, Rhs, div_t>(lhs, rhs);
}

template <typename Rhs>
expr1<Rhs, plus_t> operator +(const Rhs &rhs) {
  return expr1<Rhs, plus_t>(rhs);
}

template <typename Rhs>
expr1<Rhs, minus_t> operator -(const Rhs &rhs) {
  return expr1<Rhs, minus_t>(rhs);
}
}}