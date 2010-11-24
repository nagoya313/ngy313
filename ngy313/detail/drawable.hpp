#pragma once
#include <cstdint>
#include <array>
#include <type_traits>
#include <boost/mpl/inherit.hpp>
#include <boost/mpl/eval_if.hpp>
#include <pstade/oven/any_range.hpp>
#include <pstade/oven/make_range.hpp>
#include <pstade/oven/transformed.hpp>
#include "drawable_core_access.hpp"
#include "fvf_tag.hpp"
#include "fvf_traits.hpp"
#include "primitive_tag.hpp"
#include "com_fwd.hpp"

namespace ngy313 { namespace detail {
struct blend_empty {};

struct meta_blend_empty {
  typedef blend_empty type;
};

struct addressing_empty {};

struct meta_addressing_empty {
  typedef addressing_empty type;
};

struct stage_empty {};

struct meta_stage_empty {
  typedef stage_empty type;
};

template <typename BlendPairType>
struct blend_type;

template <typename AddressingPair>
struct addressing_type;

template <typename TextureStagePair>
struct texture_stage_type;

template <typename Drawable>
struct meta_blend_type {
  typedef blend_type<typename Drawable::blend_pair_type> type;
};

template <typename Drawable>
struct meta_addressing_type {
  typedef addressing_type<typename Drawable::addressing_pair_type> type;
};

template <typename Drawable>
struct meta_stage_type {
  typedef texture_stage_type<typename Drawable::texture_stage_pair_type> type;
};

template <typename Drawable, std::size_t Size, std::uint32_t Count, typename FVFTag, typename PrimitiveTag>
struct drawable_base_type {
  typedef Drawable drawable_type;
  typedef std::integral_constant<std::size_t, Size> size_type;
  typedef std::integral_constant<std::uint32_t, Count> count_type;
  typedef FVFTag fvf_tag;
  typedef fvf_traits<FVFTag> fvf_type;
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
                                       typename boost::mpl::eval_if<has_addressing_pair_type<Drawable>, 
                                                                    meta_addressing_type<Drawable>, 
                                                                    meta_addressing_empty>::type,
                                       typename boost::mpl::eval_if<has_texture_stage_pair_type<Drawable>, 
                                                                    meta_stage_type<Drawable>, 
                                                                    meta_stage_empty>::type>::type type;
};

template <typename Drawable, std::size_t Size, std::uint32_t Count, typename FVFTag, typename PrimitiveTag>
class drawable_base : public drawable_base_type<Drawable, Size, Count, FVFTag, PrimitiveTag> {
 public:
  explicit drawable_base(const vertex_array_type &vertex) : vertex_(vertex) {}

 private:
  friend drawable_core_access;

  vertex_range_type vertex_range() const {
    return pstade::oven::make_range(vertex_);
  }

  const vertex_array_type vertex_;
};
}}

namespace ngy313 {
using detail::drawable_base;
}