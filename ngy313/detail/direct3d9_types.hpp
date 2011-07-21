#ifndef NGY313_DIRECT3D9_TYPES_HPP_
#define NGY313_DIRECT3D9_TYPES_HPP_

#include <type_traits>
#include <boost/noncopyable.hpp>
#include <d3d9.h>

namespace ngy313 { namespace detail {
struct direct3d9_fvf_type : private boost::noncopyable {
  typedef DWORD value_type;

  typedef boost::mpl::integral_c<value_type, D3DFVF_XYZRHW> xyz_rhw;
  typedef boost::mpl::integral_c<value_type, D3DFVF_XYZ> xyz;
  typedef boost::mpl::integral_c<value_type, D3DFVF_NORMAL> normal;
  typedef boost::mpl::integral_c<value_type, D3DFVF_DIFFUSE> diffuse;
  typedef boost::mpl::integral_c<value_type, D3DFVF_SPECULAR> specular;
  typedef boost::mpl::integral_c<value_type, D3DFVF_TEX1> texture;
  typedef boost::mpl::integral_c<value_type, D3DFVF_TEX2> multi_texture;
  
 private:
  direct3d9_fvf_type();
};

struct direct3d9_primitive_type : private boost::noncopyable {
  typedef D3DPRIMITIVETYPE value_type;

  typedef std::integral_constant<value_type, D3DPT_POINTLIST> point_list;
  typedef std::integral_constant<value_type, D3DPT_LINELIST> line_list;
  typedef std::integral_constant<value_type, D3DPT_LINESTRIP> line_strip;
  typedef std::integral_constant<value_type, D3DPT_TRIANGLELIST> triangle_list;
  typedef std::integral_constant<value_type, D3DPT_TRIANGLESTRIP> triangle_strip;
  typedef std::integral_constant<value_type, D3DPT_TRIANGLEFAN> triangle_fan;

 private:
  direct3d9_primitive_type();
};
}}

#endif