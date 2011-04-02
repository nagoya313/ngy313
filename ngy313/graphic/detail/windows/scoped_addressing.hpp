#ifndef NGY313_GRAPHIC_DETAIL_WINDOWS_SCOPED_ADDRESSING_HPP_
#define NGY313_GRAPHIC_DETAIL_WINDOWS_SCOPED_ADDRESSING_HPP_
#include <cassert>
#include <cstdint>
#include <type_traits>
#include <boost/mpl/at.hpp>
#include <ngy313/graphic/detail/key.hpp>
#include <ngy313/graphic/addressing_tag.hpp>
#include <ngy313/graphic/detail/windows/fwd.hpp>
#include <ngy313/utility/detail/windows/com_delete.hpp>

namespace ngy313 { namespace graphic { namespace detail {
template <typename List, typename T = void>
class scoped_addressing {
 public:
  explicit scoped_addressing(const device_handle &) {}
};

template <typename List>
class scoped_addressing<List, 
                        typename std::enable_if<
                            !std::is_same<typename boost::mpl::at<List, detail::addressing_tuple_key>::type,
                                          boost::mpl::void_>::value>::type> {
 public:
  explicit scoped_addressing(const device_handle &device) : device_(device) {
    assert(device_);
    set_addressing_tuple<typename boost::mpl::at<List, detail::addressing_tuple_key>::type>(device_);
  }

  ~scoped_addressing() {
    assert(device_);
    set_blend_pair<
        default_addressing<
            typename boost::mpl::at<List, detail::addressing_tuple_key>::type::stage_type::value>::type>(device_);
  }

 private:
  const device_handle &device_;
};
}}}

#endif
