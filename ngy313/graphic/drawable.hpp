#pragma once
#include <cstdint>
#include <array>
#include <type_traits>
#include <ngy313/graphic/fvf_traits.hpp>

namespace ngy313 { namespace graphic {
template <typename Drawable, 
          std::size_t Size,
          std::uint32_t Count, 
          typename FVFTag,
          typename PrimitiveTag,
          typename BlendPair = void,
          typename AddressingPair = void,
          typename TextureStagePair = void> // ˆø”‚Í‘½•ª‚à‚Á‚Æ‘‚¦‚éAImageType‚ÍÁ‚µ‹‚é
struct drawable {
  //static_assert(); primitive_tagŒŸ¸‚ğ‚·‚é
  typedef Drawable drawable_type;
  typedef std::integral_constant<std::size_t, Size> size_type;
  typedef std::integral_constant<std::uint32_t, Count> count_type;
  typedef FVFTag fvf_tag;
  typedef fvf_traits<FVFTag> fvf_type;
  typedef typename fvf_type::vertex_type vertex_type;
  typedef PrimitiveTag primitive_type;
  typedef std::array<vertex_type, Size> vertex_array_type;
  typedef BlendPair blend_pair_type;
  typedef AddressingPair addressing_tuple_type;
  typedef TextureStagePair texture_stage_tuple_type;
};

template <typename Drawable>
struct copy_drawable {
  typedef drawable<Drawable, 
                   Drawable::size_type::value, 
                   Drawable::count_type::value,
                   typename Drawable::fvf_tag,
                   typename Drawable::primitive_type,
                   typename Drawable::blend_pair_type,
                   typename Drawable::addressing_tuple_type,
                   typename Drawable::texture_stage_tuple_type> type;
};

template <typename Drawable, typename BlendPair>
struct add_blend_pair {
  typedef drawable<Drawable, 
                   Drawable::size_type::value, 
                   Drawable::count_type::value,
                   typename Drawable::fvf_tag,
                   typename Drawable::primitive_type,
                   BlendPair,
                   typename Drawable::addressing_tuple_type,
                   typename Drawable::texture_stage_tuple_type> type;
};

template <typename Drawable, typename AddressingTuple>
struct add_addressing_tuple {
  typedef drawable<Drawable, 
                   Drawable::size_type::value, 
                   Drawable::count_type::value,
                   typename Drawable::fvf_tag,
                   typename Drawable::primitive_type,
                   typename Drawable::blend_pair_type,
                   AddressingTuple,
                   typename Drawable::texture_stage_tuple_type> type;
};

template <typename Drawable, typename TextureStageTuple>
struct add_texture_stage_tuple {
  typedef drawable<Drawable, 
                   Drawable::size_type::value, 
                   Drawable::count_type::value,
                   typename Drawable::fvf_tag,
                   typename Drawable::primitive_type,
                   typename Drawable::blend_pair_type,
                   typename Drawable::addressing_tuple_type,
                   TextureStageTuple> type;
};
}}
