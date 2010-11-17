#pragma once
#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/cat.hpp>

namespace ngy313 { namespace expr { 
#define NGY313_ELEM_MAX 4

#define NGY313_VECTOR_PARAM (x)(y)(z)(w)

#define NGY313_MEMBER2_GEN(z, n, data)\
static float BOOST_PP_SEQ_ELEM(n, NGY313_VECTOR_PARAM)(const float lhs, const float rhs) {\
  return lhs data rhs;\
}

struct add_t {
  BOOST_PP_REPEAT(NGY313_ELEM_MAX, NGY313_MEMBER2_GEN, +)
};

struct sub_t {
  BOOST_PP_REPEAT(NGY313_ELEM_MAX, NGY313_MEMBER2_GEN, -)
};

struct mul_t {
  BOOST_PP_REPEAT(NGY313_ELEM_MAX, NGY313_MEMBER2_GEN, *)
};

struct div_t {
  BOOST_PP_REPEAT(NGY313_ELEM_MAX, NGY313_MEMBER2_GEN, /)
};

#undef NGY313_MEMBER2_GEN

#define NGY313_MEMBER1_GEN(z, n, data)\
static float BOOST_PP_SEQ_ELEM(n, NGY313_VECTOR_PARAM)(const float rhs) {\
  return BOOST_PP_CAT(data, rhs);\
}

struct plus_t {
  BOOST_PP_REPEAT(NGY313_ELEM_MAX, NGY313_MEMBER1_GEN, +)
};

struct minus_t {
  BOOST_PP_REPEAT(NGY313_ELEM_MAX, NGY313_MEMBER1_GEN, -)
};

#undef NGY313_MEMBER1_GEN

#define NGY313_EXPR1_MEMBER_GEN(z, n, data)\
float BOOST_PP_SEQ_ELEM(n, NGY313_VECTOR_PARAM)() const {\
  return Ope::BOOST_PP_SEQ_ELEM(n, NGY313_VECTOR_PARAM)(rhs_.BOOST_PP_SEQ_ELEM(n, NGY313_VECTOR_PARAM)());\
}

template <typename Rhs, typename Ope>
struct expr1 {
  explicit expr1(const Rhs &rhs) : rhs_(rhs) {}

  BOOST_PP_REPEAT(NGY313_ELEM_MAX, NGY313_EXPR1_MEMBER_GEN, _)

 private:
  const Rhs &rhs_;
};

#undef NGY313_EXPR1_MEMBER_GEN

#define NGY313_EXPR_MEMBER_GEN(z, n, data)\
float BOOST_PP_SEQ_ELEM(n, NGY313_VECTOR_PARAM)() const {\
  return Ope::BOOST_PP_SEQ_ELEM(n, NGY313_VECTOR_PARAM)(lhs_.BOOST_PP_SEQ_ELEM(n, NGY313_VECTOR_PARAM)(),\
                                                        rhs_.BOOST_PP_SEQ_ELEM(n, NGY313_VECTOR_PARAM)());\
}

template <typename Lhs, typename Rhs, typename Ope>
struct expr2 {
  expr2(const Lhs &lhs, const Rhs &rhs) : lhs_(lhs), rhs_(rhs) {}

  BOOST_PP_REPEAT(NGY313_ELEM_MAX, NGY313_EXPR_MEMBER_GEN, _)

 private:
  const Lhs &lhs_;
  const Rhs &rhs_;
};

#undef NGY313_EXPR_MEMBER_GEN

#define NGY313_EXPR_RIGHT_FLOAT_MEMBER_GEN(z, n, data)\
float BOOST_PP_SEQ_ELEM(n, NGY313_VECTOR_PARAM)() const {\
  return Ope::BOOST_PP_SEQ_ELEM(n, NGY313_VECTOR_PARAM)(lhs_.BOOST_PP_SEQ_ELEM(n, NGY313_VECTOR_PARAM)(), rhs_);\
}

template <typename Lhs, typename Ope>
struct expr2<Lhs, float, Ope> {
  expr2(const Lhs &lhs, const float rhs) : lhs_(lhs), rhs_(rhs) {}

  BOOST_PP_REPEAT(NGY313_ELEM_MAX, NGY313_EXPR_RIGHT_FLOAT_MEMBER_GEN, _)

 private:
  const Lhs &lhs_;
  const float rhs_;
};

#undef NGY313_EXPR_RIGHT_FLOAT_MEMBER_GEN

#define NGY313_EXPR_LEFT_FLOAT_MEMBER_GEN(z, n, data)\
float BOOST_PP_SEQ_ELEM(n, NGY313_VECTOR_PARAM)() const {\
  return Ope::BOOST_PP_SEQ_ELEM(n, NGY313_VECTOR_PARAM)(lhs_, rhs_.BOOST_PP_SEQ_ELEM(n, NGY313_VECTOR_PARAM)());\
}

template <typename Rhs, typename Ope>
struct expr2<float, Rhs, Ope> {
  expr2(const float lhs, const Rhs &rhs) : lhs_(lhs), rhs_(rhs) {}

  BOOST_PP_REPEAT(NGY313_ELEM_MAX, NGY313_EXPR_LEFT_FLOAT_MEMBER_GEN, _)

 private:
  const float slhs_;
  const Rhs &rhs_;
};

#undef NGY313_EXPR_LEFT_FLOAT_MEMBER_GEN

#undef NGY313_VECTOR_PARAM

#undef NGY313_ELEM_MAX

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