#pragma once
#include <cstddef>
#include <boost/mpl/pair.hpp>
#include <ngy313/adaptor/adaptor.hpp>
#include <ngy313/graphic/detail/key.hpp>
#include <ngy313/graphic/adaptor.hpp>
#include <ngy313/graphic/addressing_tag.hpp>
#include <ngy313/graphic/drawable.hpp>

namespace ngy313 { namespace graphic {
template <typename Drawable, typename AddressingTuple>
struct addressing_adaptor {
  typedef add_drawable_adaptor<Drawable, boost::mpl::pair<detail::addressing_tuple_key, AddressingTuple>> type;
};

template <std::size_t Stage, typename Drawable, typename Address>
addressing_adaptor<Drawable, typename Address::tuple_type> make_addressing(const Drawable &drawable, const Address &) {
  return addressing_adaptor<Drawable, typename Address::tuple_type>(drawable);
}

template <std::size_t Stage, typename UAddressingTag, typename VAddressingTag>
struct addressing : public adaptor::base<addressing<Stage, UAddressingTag, VAddressingTag>> {
  typedef addressing_tuple<Stage, UAddressingTag, VAddressingTag> tuple_type;

  template <typename Drawable>
  typename addressing_adaptor<Drawable, tuple_type>::type operator ()(const Drawable &drawable) const {
    return addressing_adaptor<Drawable, tuple_type>::type(drawable);
  }
};

typedef addressing<0, wrap_addressing_tag, wrap_addressing_tag> wrap_addressing_t;
typedef addressing<0, mirror_addressing_tag, mirror_addressing_tag> mirror_addressing_t;
typedef addressing<0, clamp_addressing_tag, clamp_addressing_tag> clamp_addressing_t;

const wrap_addressing_t wrap_addressing = wrap_addressing_t();
const mirror_addressing_t mirror_addressing = mirror_addressing_t();
const clamp_addressing_t clamp_addressing = clamp_addressing_t();
}}
