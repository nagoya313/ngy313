#pragma once

namespace ngy313 {
struct fvf_tag {};

struct position_fvf_tag : public fvf_tag {};

struct tex_fvf_tag : public fvf_tag {};

struct dimension2_fvf_tag : public position_fvf_tag {};

struct dimension3_fvf_tag : public position_fvf_tag {};

struct normal_fvf_tag : public fvf_tag {};

struct diffuse_fvf_tag : public fvf_tag {};

struct specular_fvf_tag : public fvf_tag {};

struct tex1_fvf_tag : public tex_fvf_tag {};

struct tex2_fvf_tag : public tex_fvf_tag {};
}

namespace ngy313 {
template <typename Src, typename Dest>
struct blend_pair {
  typedef Src src_type;
  typedef Dest dest_type;
};

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

typedef blend_pair<src_alpha_blend_tag, inv_src_alpha_blend_tag> default_blend;
}