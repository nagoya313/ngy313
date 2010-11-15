#pragma once
#include <cstdint>
#include <array>
#include <boost/mpl/integral_c.hpp>
#include <pstade/oven/any_range.hpp>
#include <pstade/oven/make_range.hpp>
#include <pstade/oven/transformed.hpp>
#include "detail/drawable_core_access.hpp"
#include "fvf_traits.hpp"
#include "primitive_tag.hpp"
#include "fvf_tag.hpp"


namespace ngy313 { namespace detail {
template <typename Drawable, 
          std::size_t Size,
          std::uint32_t Count, 
          typename FVFTag,
          typename PrimitiveTag>
struct drawable_base_type {
  typedef drawable_base_type<Drawable, Size, Count, FVFTag, PrimitiveTag> 
              base_type;
  typedef Drawable drawable_type;
  typedef boost::mpl::integral_c<std::size_t, Size> size_type;
  typedef boost::mpl::integral_c<std::uint32_t, Count> count_type;
  typedef detail::fvf_traits<FVFTag> fvf_type;
  typedef typename fvf_type::type vertex_type;
  typedef PrimitiveTag primitive_type;
  typedef std::array<vertex_type, Size> vertex_array_type;
  typedef pstade::oven::any_range<vertex_type, boost::random_access_traversal_tag> 
              vertex_range_type;
};
         
template <template <class, std::size_t, std::uint32_t, class, class>
              class DrawableBase,
          typename Drawable,
          std::size_t Size,
          std::uint32_t Count, 
          typename FVFTag,
          typename PrimitiveTag>
class drawable_base_impl 
    : public detail::drawable_base_type<Drawable,
                                        Size, 
                                        Count,
                                        FVFTag,
                                        PrimitiveTag> {
 public:
  explicit drawable_base_impl(const vertex_array_type &vertex)
      : vertex_(vertex) {}

 private:
  friend DrawableBase<Drawable, Size, Count, FVFTag, PrimitiveTag>;

  const vertex_array_type vertex_;
};
}}

namespace ngy313 {
template <typename Drawable, 
          std::size_t Size,
          std::uint32_t Count, 
          typename FVFTag,
          typename PrimitiveTag>
class drawable_base
    : public detail::drawable_base_impl<drawable_base,
                                        Drawable,
                                        Size,
                                        Count,
                                        FVFTag,
                                        PrimitiveTag> {
 public:
  explicit drawable_base(const vertex_array_type &vertex)
      : drawable_base_impl(vertex) {}

 private:
  friend detail::drawable_core_access;

  vertex_range_type vertex_range() const {
    return pstade::oven::make_range(vertex_);
  }
};
}