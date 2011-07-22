#ifndef NGY313_DIRECT3D9_TYPES_HPP_
#define NGY313_DIRECT3D9_TYPES_HPP_

#include <boost/noncopyable.hpp>
#include <d3d9.h>

namespace ngy313 { namespace detail {
struct direct3d9_fvf_type : private boost::noncopyable {
  typedef DWORD value_type;

  static const value_type kXYZ_RHW = D3DFVF_XYZRHW;
  static const value_type kXYZ = D3DFVF_XYZ;
  static const value_type kNormal = D3DFVF_NORMAL;
  static const value_type kDiffuse = D3DFVF_DIFFUSE;
  static const value_type kSpecular = D3DFVF_SPECULAR;
  static const value_type kTexture = D3DFVF_TEX1;
  static const value_type kMultiTexture = D3DFVF_TEX2;
  
 private:
  direct3d9_fvf_type();
};

struct direct3d9_primitive_type : private boost::noncopyable {
  typedef D3DPRIMITIVETYPE value_type;

  static const value_type kPointList = D3DPT_POINTLIST;
  static const value_type kLineList = D3DPT_LINELIST;
  static const value_type kLineStrip = D3DPT_LINESTRIP;
  static const value_type kTriangleList = D3DPT_TRIANGLELIST;
  static const value_type kTriangleStrip = D3DPT_TRIANGLESTRIP;
  static const value_type kTriangleFan = D3DPT_TRIANGLEFAN;

 private:
  direct3d9_primitive_type();
};

struct direct3d9_blend_type : private boost::noncopyable {
  typedef D3DBLEND value_type;

  static const value_type kBlendOne = D3DBLEND_ONE;
  static const value_type kBlendSrcAlpha = D3DBLEND_SRCALPHA;
  static const value_type kBlendInvSrcAlpha = D3DBLEND_INVSRCALPHA;
  static const value_type kBlendDestAlpha =  D3DBLEND_DESTALPHA;
  static const value_type kBlendInvDestAlpha = D3DBLEND_INVDESTALPHA;
  static const value_type kBlendZero = D3DBLEND_ZERO;
  static const value_type kBlendSrcColor = D3DBLEND_SRCCOLOR;
  static const value_type kBlendInvSrcColor = D3DBLEND_INVSRCCOLOR;
  static const value_type kBlendDestColor = D3DBLEND_DESTCOLOR;
  static const value_type kBlendInvDestColor = D3DBLEND_INVDESTCOLOR;

 private:
  direct3d9_blend_type();
};
}}

#endif