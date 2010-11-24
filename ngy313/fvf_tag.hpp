#pragma once
#include "detail/fvf_tag.hpp"

namespace ngy313 {
using detail::dimension2_fvf_tag;
using detail::dimension3_fvf_tag;
using detail::normal_fvf_tag;
using detail::diffuse_fvf_tag;
using detail::specular_fvf_tag;
using detail::tex1_fvf_tag;
using detail::tex2_fvf_tag;

typedef make_fvf_tag<dimension2_fvf_tag, diffuse_fvf_tag> shape_2d_fvf_tag;
typedef make_fvf_tag<dimension2_fvf_tag, diffuse_fvf_tag, tex1_fvf_tag> image_2d_fvf_tag;
typedef make_fvf_tag<dimension2_fvf_tag, diffuse_fvf_tag, tex2_fvf_tag> multi_image_2d_fvf_tag;
typedef make_fvf_tag<dimension3_fvf_tag, diffuse_fvf_tag> shape_3d_fvf_tag;
typedef make_fvf_tag<dimension3_fvf_tag, diffuse_fvf_tag, tex1_fvf_tag> image_3d_fvf_tag;
typedef make_fvf_tag<dimension3_fvf_tag, diffuse_fvf_tag, tex2_fvf_tag> multi_image_3d_fvf_tag;
}