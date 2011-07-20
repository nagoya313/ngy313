#ifndef NGY313_DETAIL_TYPES_HPP_
#define NGY313_DETAIL_TYPES_HPP_

#include <boost/noncopyable.hpp>
#include <boost/mpl/vector.hpp>

#if defined(_WIN32)
#include <ngy313/detail/direct3d9_types.hpp>
#elif defined(__linux__)
#include <ngy313/detail/opengl_types.hpp>
#endif

namespace ngy313 { namespace detail {
template <typename FVF>
struct basic_fvf_type : private boost::noncopyable {
  typedef typename FVF::xyz_rhw xyz_rhw;
  typedef typename FVF::xyz xyz;
  typedef typename FVF::normal normal;
  typedef typename FVF::diffuse diffuse;
  typedef typename FVF::specular specular;
  typedef typename FVF::texture texture;
  typedef typename FVF::multi_texture multi_texture;

 private:
  basic_fvf_type();
};

template <typename Primitve>
struct basic_primitive_type : private boost::noncopyable {
  typedef typename Primitve::point_list point_list;
  typedef typename Primitve::line_list line_list;
  typedef typename Primitve::line_strip line_strip;
  typedef typename Primitve::triangle_list triangle_list;
  typedef typename Primitve::triangle_strip triangle_strip;
  typedef typename Primitve::triangle_fan triangle_fan;
  typedef boost::mpl::vector<point_list,
  		                        line_list,
  		                        line_strip,
  		                        triangle_list,
  		                        triangle_strip,
  		                        triangle_fan> tag_list;

 private:
  basic_primitive_type();
};

template <typename Blend>
struct basic_blend_type : private boost::noncopyable {

 private:
  basic_blend_type();
};

#if defined(_WIN32)
typedef basic_fvf_type<direct3d9_fvf_type> fvf_type;
typedef basic_primitive_type<direct3d9_primitive_type>
    primitive_type;
#elif defined(__linux__)
typedef basic_fvf_type<opengl_fvf_type> fvf_type;
typedef basic_primitive_type<opengl_primitive_type>
   primitive_type;
#endif
}}

#endif
