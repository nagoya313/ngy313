#ifndef NGY313_GRAPHIC_DETAIL_LINUX_SCOPED_RENDER_HPP_
#define NGY313_GRAPHIC_DETAIL_LINUX_SCOPED_RENDER_HPP_
#include <type_traits>
#include <boost/mpl/at.hpp>
#include <ngy313/graphic/detail/key.hpp>
#include <ngy313/graphic/blend_tag.hpp>
#include <ngy313/graphic/detail/linux/blend.hpp>

namespace ngy313 { namespace graphic { namespace detail {
template <typename List, typename T = void>
class scoped_blend {
 public:
  explicit scoped_blend() {}
};

template <typename List>
class scoped_blend<List, 
                   typename std::enable_if<!std::is_same<typename boost::mpl::at<List, detail::blend_pair_key>::type,
                                                         boost::mpl::void_>::value>::type> {
 public:
  explicit scoped_blend(const device_handle &device) : device_() {
    glEnable(GL_BLEND);
    set_blend_pair<boost::mpl::at<List, detail::blend_pair_key>::type>();
  }

  ~scoped_blend() {
    set_blend_pair<default_blend>();
    glDisable(GL_BLEND);
  }

 private:
  const device_handle &device_;
};
}}}

#endif

