#pragma once
#include <cstdint>
#include <array>
#include <boost/mpl/integral_c.hpp>
#include <pstade/oven/any_range.hpp>
#include <pstade/oven/transformed.hpp>
#include "detail/drawable_core_access.hpp"
#include "drawable_traits.hpp"
#include "drawable_tag.hpp"

namespace ngy313 { namespace detail {
template <typename Drawable, 
          std::size_t Size,
          std::uint32_t Count, 
          typename DrawableTag>
struct drawable_adaptor_base {
  typedef drawable_adaptor_base<Drawable, 
                           Size,
                           Count,
                           DrawableTag> adaptor_type;
  typedef Drawable drawable_type;
  typedef boost::mpl::integral_c<std::size_t, Size> size_type;
  typedef boost::mpl::integral_c<std::uint32_t, Count> count_type;
  typedef typename DrawableTag::type drawable_tag;
  typedef typename detail::fvf_traits<drawable_tag>::type fvf_type;
  typedef typename detail::vertex_traits<drawable_tag>::type vertex_type;
  typedef typename detail::primitive_traits<drawable_tag>::type primitive_type;
  typedef std::array<vertex_type, Size> vertex_array_type;
  typedef pstade::oven::any_range<
              vertex_type, 
              boost::forward_traversal_tag> vertex_range_type;
};
}}

namespace ngy313 {
template <typename Drawable, 
          std::size_t Size,
          std::uint32_t Count, 
          typename DrawableTag>
class drawable_adaptor
    : public detail::drawable_adaptor_base<Drawable,
                                           Size,
                                           Count,
                                           DrawableTag> {
 public:
  friend drawable_core_access;

  explicit drawable_adaptor(const vertex_array_type &vertex)
      : vertex_(vertex) {}

  template <typename Filter>
  explicit drawable_adaptor(const Filter &filter)
      : vertex_(drawable_core_access::copy_vertex(filter)) {}
 
 private:
  vertex_range_type vertex_range() const {
    return pstade::oven::make_range(vertex_);
  }

  const vertex_array_type vertex_;
};
}