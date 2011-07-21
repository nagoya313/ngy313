#ifndef NGY313_VECTOR_HPP_
#define NGY313_VECTOR_HPP_

#include <boost/config.hpp>
#include <boost/operators.hpp>

namespace ngy313 {
class vector2 : boost::equality_comparable<vector2>,
                boost::addable<vector2>,
                boost::subtractable<vector2>,
                boost::dividable2<vector2, float>,
                boost::multipliable2<vector2, float> {
 public:
	BOOST_CONSTEXPR vector2(float x, float y) : x_(x), y_(y) {}
  
	BOOST_CONSTEXPR float get_x() const {
  	return x_;
  }
  
	BOOST_CONSTEXPR float get_y() const {
  	return y_;
  }
  
  void set_x(float x) {
  	x_ = x;
  }
  
  void set_y(float y) {
  	y_ = y;
  }
  
  vector2 &operator +=(const vector2 &rhs) {
  	x_ += rhs.x_;
  	y_ += rhs.y_;
    return *this;
  }

  vector2 &operator -=(const vector2 &rhs) {
    x_ -= rhs.x_;
    y_ -= rhs.y_;
    return *this;
  }

  vector2 &operator *=(float rhs) {
    x_ *= rhs;
    y_ *= rhs;
    return *this;
  }

  vector2 &operator /=(float rhs) {
    x_ /= rhs;
    y_ /= rhs;
    return *this;
  }

  BOOST_CONSTEXPR vector2 operator -() const {
    return vector2(-x_, -y_);
  }
   
 private:
  float x_;
  float y_;
};

inline
bool operator ==(const vector2 &lhs, const vector2 &rhs) {
  return lhs.get_x() == rhs.get_x() && lhs.get_y() == rhs.get_y();
}
}

#endif
