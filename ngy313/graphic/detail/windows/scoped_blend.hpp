#ifndef NGY313_GRAPHIC_DETAIL_WINDOWS_SCOPED_BLEND_HPP_
#define NGY313_GRAPHIC_DETAIL_WINDOWS_SCOPED_BLEND_HPP_
#include <cassert>
#include <type_traits>
#include <boost/mpl/at.hpp>
#include <ngy313/graphic/detail/key.hpp>
#include <ngy313/graphic/blend_tag.hpp>
#include <ngy313/graphic/detail/windows/blend.hpp>
#include <ngy313/graphic/detail/windows/device.hpp>

namespace ngy313 { namespace graphic { namespace detail {
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

#endif
