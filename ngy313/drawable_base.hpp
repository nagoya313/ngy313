#pragma once
#include <cstdint>
#include <array>
#include <boost/mpl/inherit.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/integral_c.hpp>
#include <pstade/oven/any_range.hpp>
#include <pstade/oven/make_range.hpp>
#include <pstade/oven/transformed.hpp>
#include "detail/drawable_core_access.hpp"
#include "detail/fvf_tag.hpp"
#include "detail/fvf_traits.hpp"
#include "detail/primitive_tag.hpp"
#include "detail/graphic_device.hpp"

namespace ngy313 { namespace detail {
struct empty {};

struct blend_empty {};

struct meta_blend_empty {
  typedef blend_empty type;
};

struct stage_empty {};

struct meta_stage_empty {
  typedef stage_empty type;
};

template <typename Drawable>
struct meta_blend_type {
  typedef blend_type<typename Drawable::blend_pair_type> type;
};

template <typename Drawable>
struct meta_stage_type {
  typedef texture_stage_type<typename Drawable::texture_stage_pair_type> type;
};

template <typename Drawable, 
          std::size_t Size,
          std::uint32_t Count,
          typename FVFTag,
          typename PrimitiveTag>
struct drawable_base_type {
  typedef Drawable drawable_type;
  typedef boost::mpl::integral_c<std::size_t, Size> size_type;
  typedef boost::mpl::integral_c<std::uint32_t, Count> count_type;
  typedef FVFTag fvf_tag;
  typedef detail::fvf_traits<FVFTag> fvf_type;
  typedef typename fvf_type::type vertex_type;
  typedef PrimitiveTag primitive_type;
  typedef std::array<vertex_type, Size> vertex_array_type;
  typedef pstade::oven::any_range<vertex_type, boost::random_access_traversal_tag> vertex_range_type;
};

template <typename Drawable>
struct copy_drawable_type {
  typedef typename boost::mpl::inherit<drawable_base_type<Drawable,
                                                          Drawable::size_type::value,
                                                          Drawable::count_type::value,
                                                          typename Drawable::fvf_tag,
                                                          typename Drawable::primitive_type>,
                                       typename boost::mpl::eval_if<has_blend_pair_type<Drawable>, 
                                                                    meta_blend_type<Drawable>, 
                                                                    meta_blend_empty>::type,
                                       typename boost::mpl::eval_if<has_texture_stage_pair_type<Drawable>, 
                                                                    meta_stage_type<Drawable>, 
                                                                    meta_stage_empty>::type>::type type;
};
         
template <template <class, std::size_t, std::uint32_t, class, class> class DrawableBase,
          typename Drawable,
          std::size_t Size,
          std::uint32_t Count, 
          typename FVFTag,
          typename PrimitiveTag>
class drawable_base_impl 
    : public detail::drawable_base_type<Drawable, Size, Count, FVFTag, PrimitiveTag> {
 public:
  explicit drawable_base_impl(const vertex_array_type &vertex)
      : vertex_(vertex) {}

 private:
  friend DrawableBase<Drawable, Size, Count, FVFTag, PrimitiveTag>;

  const vertex_array_type vertex_;
};
}}

namespace ngy313 {
template <typename Drawable, std::size_t Size, std::uint32_t Count, typename FVFTag, typename PrimitiveTag>
class drawable_base
    : public detail::drawable_base_impl<drawable_base, Drawable, Size, Count, FVFTag, PrimitiveTag> {
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