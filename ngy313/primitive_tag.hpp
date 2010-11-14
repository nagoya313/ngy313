#pragma once
#include <d3d9.h>

namespace ngy313 {
struct primitive_tag {
  typedef D3DPRIMITIVETYPE value_type;
};

struct point_list_primitive_tag : public primitive_tag {
  static const value_type value = D3DPT_POINTLIST;
};

struct line_list_primitive_tag : public primitive_tag {
  static const value_type value = D3DPT_LINELIST;
};

struct line_strip_primitive_tag  : public primitive_tag {
  static const value_type value = D3DPT_LINESTRIP;
};

struct triangle_list_primitive_tag : public primitive_tag {
  static const value_type value = D3DPT_TRIANGLELIST;
};

struct triangle_strip_primitive_tag : public primitive_tag {
  static const value_type value = D3DPT_TRIANGLESTRIP;
};

struct triangle_fan_primitive_tag : public primitive_tag {
  static const value_type value = D3DPT_TRIANGLEFAN;
};
}