#pragma once
#include <d3d9.h>

namespace ngy313 {
struct blend_tag {
  typedef D3DBLEND value_type;
};

struct one_blend_tag : public blend_tag {
  static const value_type value = D3DBLEND_ONE;
};

struct src_alpha_blend_tag : public blend_tag {
  static const value_type value = D3DBLEND_SRCALPHA;
};

struct inv_src_alpha_blend_tag : public blend_tag {
  static const value_type value = D3DBLEND_INVSRCALPHA;
};

struct dest_alpha_blend_tag : public blend_tag {
  static const value_type value = D3DBLEND_DESTALPHA;
};

struct inv_dest_alpha_blend_tag : public blend_tag {
  static const value_type value = D3DBLEND_INVDESTALPHA;
};

struct zero_blend_tag : public blend_tag {
  static const value_type value = D3DBLEND_ZERO;
};

struct src_color_blend_tag : public blend_tag {
  static const value_type value = D3DBLEND_SRCCOLOR;
};

struct inv_src_color_blend_tag : public blend_tag {
  static const value_type value = D3DBLEND_INVSRCCOLOR;
};

struct dest_color_blend_tag : public blend_tag {
  static const value_type value = D3DBLEND_DESTCOLOR;
};

struct inv_dest_color_blend_tag : public blend_tag {
  static const value_type value = D3DBLEND_INVDESTCOLOR;
};
}