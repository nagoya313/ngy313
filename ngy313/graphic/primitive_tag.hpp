#ifndef NGY313_GRAPHIC_PRIMITIBE_TAG_HPP_
#define NGY313_GRAPHIC_PRIMITIBE_TAG_HPP_
#include <type_traits>
#include <boost/mpl/vector.hpp>
#include <ngy313/platform.hpp>
#if defined(NGY313_WINDOWS_VERSION)
#include <ngy313/graphic/detail/windows/primitive_type.hpp>
#elif defined(NGY313_LINUX_VERSION)
#include <ngy313/graphic/detail/linux/primitive_type.hpp>
#endif

namespace ngy313 { namespace graphic {
struct primitive_tag {};

// Ç±ÇÍÇ‡integral_constantåpè≥Ç≈ÇÊÇ≥Ç∞Ç©Ç»Çü
struct point_list_primitive_tag : public primitive_tag {
  typedef std::integral_constant<detail::primitive_type, detail::kPointList> type;
};

struct line_list_primitive_tag : public primitive_tag {
  typedef std::integral_constant<detail::primitive_type, detail::kLineList> type;
};

struct line_strip_primitive_tag  : public primitive_tag {
  typedef std::integral_constant<detail::primitive_type, detail::kLineStrip> type;
};

struct triangle_list_primitive_tag : public primitive_tag {
  typedef std::integral_constant<detail::primitive_type, detail::kTriangleList> type;
};

struct triangle_strip_primitive_tag : public primitive_tag {
  typedef std::integral_constant<detail::primitive_type, detail::kTriangleStrip> type;
};

struct triangle_fan_primitive_tag : public primitive_tag {
  typedef std::integral_constant<detail::primitive_type, detail::KTriangleFan> type;
};

typedef boost::mpl::vector<point_list_primitive_tag,
                           line_list_primitive_tag,
                           line_strip_primitive_tag,
                           triangle_list_primitive_tag,
                           triangle_strip_primitive_tag,
                           triangle_fan_primitive_tag> primitive_tag_list;
}}

#endif
