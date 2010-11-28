#pragma once
#include <type_traits>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/repeat_from_to.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/comma_if.hpp>
#include <boost/preprocessor/comparison/not_equal.hpp>
#include <boost/preprocessor/dec.hpp>
#include <d3dx9math.h>
#include "detail/math_expr.hpp"

namespace ngy313 { namespace expr {
#define NGY313_VECTOR_PARAM (x)(y)(z)(w)

#define NGY313_ACCESSER_GEN(z, n, data)\
float &BOOST_PP_SEQ_ELEM(n, NGY313_VECTOR_PARAM)() {\
  return BOOST_PP_CAT(data, BOOST_PP_SEQ_ELEM(n, NGY313_VECTOR_PARAM));\
}\
\
const float &BOOST_PP_SEQ_ELEM(n, NGY313_VECTOR_PARAM)() const {\
  return BOOST_PP_CAT(data, BOOST_PP_SEQ_ELEM(n, NGY313_VECTOR_PARAM));\
}\

#define NGY313_DEFAULT_CONSTRUCT_GEN(z, n, data)\
0.f BOOST_PP_COMMA_IF(BOOST_PP_NOT_EQUAL(n, BOOST_PP_DEC(data)))

#define NGY313_CONSTRUCT_GEN(z, n, data)\
expr.BOOST_PP_SEQ_ELEM(n, NGY313_VECTOR_PARAM)() BOOST_PP_COMMA_IF(BOOST_PP_NOT_EQUAL(n, BOOST_PP_DEC(data)))

#define NGY313_SUBSTITUTION_GEN(z, n, data)\
pos_.BOOST_PP_SEQ_ELEM(n, NGY313_VECTOR_PARAM) data expr.BOOST_PP_SEQ_ELEM(n, NGY313_VECTOR_PARAM)();\

#define NGY313_VECTOR_GEN(z, n, data)\
struct BOOST_PP_CAT(vector, n) {\
  typedef std::integral_constant<std::size_t, n> dimension_type;\
\
  BOOST_PP_CAT(vector, n)() : pos_(BOOST_PP_REPEAT(n, NGY313_DEFAULT_CONSTRUCT_GEN, n)) {}\
\
  BOOST_PP_CAT(vector, n)(BOOST_PP_ENUM_PARAMS(n, const float palam)) : pos_(BOOST_PP_ENUM_PARAMS(n, palam)) {}\
\
  template <typename Expr>\
  BOOST_PP_CAT(vector, n)(const Expr &expr) : pos_(BOOST_PP_REPEAT(n, NGY313_CONSTRUCT_GEN, n)) {}\
\
  template <typename Expr>\
  BOOST_PP_CAT(vector, n) &operator =(const Expr &expr) {\
    BOOST_PP_REPEAT(n, NGY313_SUBSTITUTION_GEN, =)\
    return *this;\
  }\
\
  template <typename Expr>\
  BOOST_PP_CAT(vector, n) &operator +=(const Expr &expr) {\
    BOOST_PP_REPEAT(n, NGY313_SUBSTITUTION_GEN, +=)\
    return *this;\
  }\
\
  template <typename Expr>\
  BOOST_PP_CAT(vector, n) &operator -=(const Expr &expr) {\
    BOOST_PP_REPEAT(n, NGY313_SUBSTITUTION_GEN, -=)\
    return *this;\
  }\
\
  BOOST_PP_CAT(vector, n) &operator *=(const float rhs) {\
    pos_ *= rhs;\
    return *this;\
  }\
\
  BOOST_PP_CAT(vector, n) &operator /=(const float rhs) {\
    pos_ /= rhs;\
    return *this;\
  }\
\
  bool operator ==(const BOOST_PP_CAT(vector, n) &rhs) const {\
    return (pos_ == rhs.pos_) != 0;\
  }\
\
  bool operator !=(const BOOST_PP_CAT(vector, n) &rhs) const {\
    return (pos_ != rhs.pos_) != 0;\
  }\
\
  BOOST_PP_REPEAT(n, NGY313_ACCESSER_GEN, pos_.)\
\
 private:\
  BOOST_PP_CAT(D3DXVECTOR, n) pos_;\
};

BOOST_PP_REPEAT_FROM_TO(2, 5, NGY313_VECTOR_GEN, _)

#undef NGY313_VECTOR_GEN

#undef NGY313_SUBSTITUTION_GEN

#undef NGY313_CONSTRUCT_GEN

#undef NGY313_DEFAULT_CONSTRUCT_GEN

#undef NGY313_ACCESSER_GEN

#undef NGY313_VECTOR_PARAM
}}

namespace ngy313 {
using expr::vector2;
using expr::vector3;
using expr::vector4;
}