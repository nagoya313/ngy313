#ifndef NGY313_SHAPE_HPP_
#define NGY313_SHAPE_HPP_

#include <cmath>
#include <type_traits>
#include <boost/config.hpp>
#include <boost/mpl/at.hpp>
#include <boost/preprocessor/repeat_from_to.hpp>
#include <ngy313/drawable_traits.hpp>
#include <ngy313/vector.hpp>

namespace ngy313 { namespace detail {
BOOST_CONSTEXPR_OR_CONST float kPI = 3.141592654f;

template <typename Drawable>
BOOST_CONSTEXPR float vertex_radian(int index) {
  return kPI * 2.f * static_cast<float>(index - 1) /
         static_cast<float>(
        		   boost::mpl::at<
        		       typename Drawable::list_type,
        		       count_key>::type::type::value - 2);
}

template <typename Drawable>
BOOST_CONSTEXPR float line_vertex_radian(int index) {
  return kPI * 2.f * static_cast<float>(index) /
         static_cast<float>(
        		   boost::mpl::at<
        		       typename Drawable::list_type,
        		       count_key>::type::type::value - 1);
}
}}

namespace ngy313 {
class pixel : public drawable_traits<pixel, 
                                          1,
                                          1, 
                                     shape_2d_fvf_tag,
                                     point_list_primitive_tag> {
 public:
  explicit pixel(const vector2 &base) : vertex_(init(base)) {}
  
  vertex_array_type vertex() const {
    return vertex_;
  }

 private:
  static vertex_array_type init(const vector2 &base) {
    const vertex_array_type vertex = {{
      vertex_type(rhw_position_t(base), diffuse_t())
     }};
    return vertex;
   }
  
  vertex_array_type vertex_;
};

class line : public drawable_traits<line,
                                         2,
                                         2,
                                    shape_2d_fvf_tag,
                                    line_list_primitive_tag> {
 public:
  explicit line(const vector2 &base1, const vector2 &base2)
      : vertex_(init(base1, base2)) {}

  vertex_array_type vertex() const {
    return vertex_;
  }

 private:
  static vertex_array_type init(const vector2 &base1, const vector2 &base2) {
    const vertex_array_type vertex = {{
      vertex_type(rhw_position_t(base1), diffuse_t()),
      vertex_type(rhw_position_t(base2), diffuse_t())
    }};
   return vertex;
  }
  
  vertex_array_type vertex_;
};

template <bool Filled>
class triangle_base
   : public std::conditional<Filled,
                             drawable_traits<triangle_base<Filled>, 
                                                   3,
                                                   1,
                                             shape_2d_fvf_tag, 
                                             triangle_list_primitive_tag>,
                             drawable_traits<triangle_base<Filled>, 
                                                   4,
                                                   3,
                                             shape_2d_fvf_tag,
                                             line_strip_primitive_tag>>::type {
  typedef typename triangle_base::drawable_traits base;

 public:
  typedef typename base::vertex_type vertex_type;
  typedef typename base::vertex_array_type vertex_array_type;
  
  explicit triangle_base(const vector2 &p1,
  		                    const vector2 &p2,
  		                    const vector2 &p3)
      : vertex_(init<Filled>(p1, p2, p3)) {}

  vertex_array_type vertex() const {
    return vertex_;
  }

 private:
  template <bool Fill>
  static vertex_array_type init(const vector2 &p1,
  		                           const vector2 &p2,
  		                           const vector2 &p3,
  		                           typename std::enable_if<Fill>::type * = nullptr) {
    const vertex_array_type vertex = {{
      vertex_type(rhw_position_t(p1), diffuse_t()),
      vertex_type(rhw_position_t(p2), diffuse_t()),
      vertex_type(rhw_position_t(p3), diffuse_t())
    }};
    return vertex;
  }

  template <bool Fill>
  static vertex_array_type init(const vector2 &p1,
                                const vector2 &p2,
                                const vector2 &p3,
  		                           typename std::enable_if<!Fill>::type * = nullptr) {
    const vertex_array_type vertex = {{
      vertex_type(rhw_position_t(p1), diffuse_t()),
      vertex_type(rhw_position_t(p2), diffuse_t()),
      vertex_type(rhw_position_t(p3), diffuse_t()),
      vertex_type(rhw_position_t(p1), diffuse_t())
    }};
    return vertex;
  }

  vertex_array_type vertex_;
};

typedef triangle_base<true> triangle;
typedef triangle_base<false> line_triangle;

template <bool Filled>
class box_base
    : public std::conditional<Filled,
                              drawable_traits<box_base<Filled>,
                                                    4,
                                                    2,
                                              shape_2d_fvf_tag,
                                              triangle_strip_primitive_tag>,
                              drawable_traits<box_base<Filled>,
                                                    5,
                                                    4,
                                              shape_2d_fvf_tag,
                                              line_strip_primitive_tag>>::type {
  typedef typename box_base::drawable_traits base;

 public:
  typedef typename base::vertex_type vertex_type;
  typedef typename base::vertex_array_type vertex_array_type;

  explicit box_base(const vector2 &size) : vertex_(init<Filled>(size)) {}

  vertex_array_type vertex() const {
    return vertex_;
  }

 private:
  template <bool Fill>
  static vertex_array_type init(const vector2 &size,
  		                           typename std::enable_if<Fill>::type * = nullptr) {
    const vertex_array_type vertex = {{
      vertex_type(rhw_position_t(vector2(0.f, 0.f)), diffuse_t()),
      vertex_type(rhw_position_t(vector2(size.x(), 0.f)), diffuse_t()),
      vertex_type(rhw_position_t(vector2(0.f, size.y())), diffuse_t()),
      vertex_type(rhw_position_t(size), diffuse_t())
    }};
    return vertex;
  }

  template <bool Fill>
  static vertex_array_type init(const vector2 &size,
  		                           typename std::enable_if<!Fill>::type * = nullptr) {
    const vertex_array_type vertex = {{
      vertex_type(rhw_position_t(vector2(0.f, 0.f)), diffuse_t()),
      vertex_type(rhw_position_t(vector2(size.x(), 0.f)), diffuse_t()),
      vertex_type(rhw_position_t(size), diffuse_t()),
      vertex_type(rhw_position_t(vector2(0.f, size.y())), diffuse_t()),
      vertex_type(rhw_position_t(vector2(0.f, 0.f)), diffuse_t())
    }};
    return vertex;
  }

  vertex_array_type vertex_;
};

typedef box_base<true> box;
typedef box_base<false> line_box;

#define NGY313_CIRCLE_VERTEX_SIZE 62

#define NGY313_CIRCLE_VERTEX_ELEM_GEN(z, n, data)\
vertex_type(\
		 rhw_position_t(\
				  vector2(std::cos(detail::vertex_radian<data>(n)) * r,\
                 std::sin(detail::vertex_radian<data>(n)) * r)),\
         diffuse_t()),

#define NGY313_LINE_CIRCLE_VERTEX_SIZE 60

#define NGY313_LINE_CIRCLE_VERTEX_ELEM_GEN(z, n, data)\
vertex_type(\
		 rhw_position_t(\
				  vector2(std::cos(detail::line_vertex_radian<data>(n)) * r,\
                 std::sin(detail::line_vertex_radian<data>(n)) * r)),\
         diffuse_t()),

template <bool Filled>
class circle_base
    : public std::conditional<Filled,
                              drawable_traits<circle_base<Filled>,
                                                     62,
                                                     60,
                                              shape_2d_fvf_tag,
                                              triangle_fan_primitive_tag>,
                              drawable_traits<circle_base<Filled>,
                                                    60,
                                                    59,
                                              shape_2d_fvf_tag,
                                              line_strip_primitive_tag>>::type {
  typedef typename circle_base::drawable_traits base;

 public:
  typedef typename base::vertex_type vertex_type;
  typedef typename base::vertex_array_type vertex_array_type;

  explicit circle_base(const float r) : vertex_(init<Filled>(r)) {}

  vertex_array_type vertex() const {
    return vertex_;
  }

 private:
  template <bool Fill>
  static vertex_array_type init(const float r,
  		                           typename std::enable_if<Fill>::type * = nullptr) {
    const vertex_array_type vertex = {{
      vertex_type(rhw_position_t(vector2(0.f, 0.f)), diffuse_t()),
      BOOST_PP_REPEAT_FROM_TO(1, NGY313_CIRCLE_VERTEX_SIZE, NGY313_CIRCLE_VERTEX_ELEM_GEN, circle_base)
    }};
    return vertex;
  }

  template <bool Fill>
  static vertex_array_type init(const float r,
  		                           typename std::enable_if<!Fill>::type * = nullptr) {
    const vertex_array_type vertex = {{
      BOOST_PP_REPEAT(NGY313_LINE_CIRCLE_VERTEX_SIZE, NGY313_LINE_CIRCLE_VERTEX_ELEM_GEN, circle_base)
    }};
    return vertex;
  }

  vertex_array_type vertex_;
};

#undef NGY313_CIRCLE_VERTEX_ELEM_GEN
#undef NGY313_CIRCLE_VERTEX_SIZE
#undef NGY313_LINE_CIRCLE_VERTEX_ELEM_GEN
#undef NGY313_LINE_CIRCLE_VERTEX_SIZE

typedef circle_base<true> circle;
typedef circle_base<false> line_circle;

#define NGY313_OVAL_VERTEX_SIZE 62

#define NGY313_OVAL_VERTEX_ELEM_GEN(z, n, data)\
vertex_type(\
		rhw_position_t(\
			  vector2(std::cos(detail::vertex_radian<data>(n)) * r.x(),\
               std::sin(detail::vertex_radian<data>(n)) * r.y())),\
        diffuse_t()),

#define NGY313_LINE_OVAL_VERTEX_SIZE 60

#define NGY313_LINE_OVAL_VERTEX_ELEM_GEN(z, n, data)\
vertex_type(\
		rhw_position_t(\
       vector2(std::cos(detail::line_vertex_radian<data>(n)) * r.x(),\
               std::sin(detail::line_vertex_radian<data>(n)) * r.y())),\
       diffuse_t()),

template <bool Filled>
class oval_base
    : public std::conditional<Filled,
                              drawable_traits<oval_base<Filled>,
                                                     62,
                                                     60,
                                              shape_2d_fvf_tag,
                                              triangle_fan_primitive_tag>,
                              drawable_traits<oval_base<Filled>,
                                                     60,
                                                     59,
                                              shape_2d_fvf_tag,
                                              line_strip_primitive_tag>>::type {
 typedef typename oval_base::drawable_traits base;

 public:
  typedef typename base::vertex_type vertex_type;
  typedef typename base::vertex_array_type vertex_array_type;

  explicit oval_base(const vector2 &r) : vertex_(init<Filled>(r)) {}

  vertex_array_type vertex() const {
    return vertex_;
  }

 private:
  template <bool Fill>
  static vertex_array_type init(const vector2 &r,
  		                           typename std::enable_if<Fill>::type * = nullptr) {
    const vertex_array_type vertex = {{
      vertex_type(rhw_position_t(vector2(0.f, 0.f)), diffuse_t()),
      BOOST_PP_REPEAT_FROM_TO(1, NGY313_OVAL_VERTEX_SIZE, NGY313_OVAL_VERTEX_ELEM_GEN, oval_base)
    }};
    return vertex;
  }

  template <bool Fill>
  static vertex_array_type init(const vector2 &r,
  		                           typename std::enable_if<!Fill>::type * = nullptr) {
    const vertex_array_type vertex = {{
      BOOST_PP_REPEAT(NGY313_LINE_OVAL_VERTEX_SIZE, NGY313_LINE_OVAL_VERTEX_ELEM_GEN, oval_base)
    }};
    return vertex;
  }

  vertex_array_type vertex_;
};

#undef NGY313_OVAL_VERTEX_ELEM_GEN
#undef NGY313_OVAL_VERTEX_SIZE
#undef NGY313_LINE_OVAL_VERTEX_ELEM_GEN
#undef NGY313_LINE_OVAL_VERTEX_SIZE

typedef oval_base<true> oval;
typedef oval_base<false> line_oval;
}

#endif
