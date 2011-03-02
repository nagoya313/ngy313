#pragma once
#include <cassert>
#include <type_traits>
#include <boost/mpl/at.hpp>
#include <ngy313/graphic/detail/key.hpp>
#include <ngy313/graphic/blend_tag.hpp>
#include <ngy313/graphic/detail/fwd.hpp>
#include <ngy313/utility/com_delete.hpp>
#include <ngy313/utility/intrusive_com_delete.hpp>

namespace ngy313 { namespace graphic { namespace detail {
inline
void set_blend_mode(const device_handle &device, const blend_type src, const blend_type dest) {
  assert(device);
  device->SetRenderState(D3DRS_SRCBLEND, src);
  device->SetRenderState(D3DRS_DESTBLEND, dest);
}

template <typename BlendPair>
void set_blend_pair(const device_handle &device) {
  assert(device);
  set_blend_mode(device, BlendPair::src_type::value, BlendPair::dest_type::value);
}

template <typename List, typename T = void>
class scoped_blend {
 public:
  explicit scoped_blend(const device_handle &) {}
};

template <typename List>
class scoped_blend<List, 
                   typename std::enable_if<!std::is_same<typename boost::mpl::at<List, detail::blend_pair_key>::type,
                                                         boost::mpl::void_>::value>::type> {
 public:
  explicit scoped_blend(const device_handle &device) : device_(device) {
    assert(device_);
    set_blend_pair<boost::mpl::at<List, detail::blend_pair_key>::type>(device_);
  }

  ~scoped_blend() {
    assert(device_);
    set_blend_pair<default_blend>(device_);
  }

 private:
  const device_handle &device_;
};
}}}
