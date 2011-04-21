#ifndef NGY313_GRAPHIC_DETAIL_LINUX_SCOPED_ADDRESSING_HPP_
#define NGY313_GRAPHIC_DETAIL_LINUX_SCOPED_ADDRESSING_HPP_
#include <type_traits>
#include <boost/mpl/at.hpp>
#include <ngy313/graphic/detail/key.hpp>
#include <ngy313/graphic/detail/linux/addressing.hpp>
#include <ngy313/graphic/addressing_tag.hpp>

namespace ngy313 { namespace graphic { namespace detail {
template <typename List, typename T = void>
class scoped_addressing {
 public:
  explicit scoped_addressing() {}
};

template <typename List>
class scoped_addressing<List, 
                        typename std::enable_if<
                            !std::is_same<typename boost::mpl::at<List, detail::addressing_tuple_key>::type,
                                          boost::mpl::void_>::value>::type> {
 public:
  explicit scoped_addressing() {
    set_addressing_tuple<typename boost::mpl::at<List, addressing_tuple_key>::type>();
  }

  ~scoped_addressing() {
    set_addressing_tuple<
        typename default_addressing<
            boost::mpl::at<List, addressing_tuple_key>::type::stage_type::value>::type>();
  }
};
}}}

#endif

