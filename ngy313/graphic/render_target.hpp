#ifndef NGY313_GRAPHIC_RENDER_TARGET_HPP_
#define NGY313_GRAPHIC_RENDER_TARGET_HPP_
#include <boost/noncopyable.hpp>
#include <ngy313/platform.hpp>
#if defined(NGY313_WINDOWS_VERSION)
#include <ngy313/graphic/detail/windows/render_target.hpp>
#elif defined(NGY313_LINUX_VERSION)
#include <ngy313/graphic/detail/linux/render_target.hpp>
#endif
#include <ngy313/graphic/detail/graphic.hpp>

namespace ngy313 { namespace graphic {
class render_target : private boost::noncopyable {
 public:
  render_target(const int width, const int height) : target_(detail::device(), width, height) {}

  int width() const {
    return target_.width();
  }

  int height() const {
    return target_.height();
  }

  void connect_after_reset(const boost::signals2::signal<void ()>::slot_type &slot) {
    target_.after_reset.connect(slot);
  }

 private:
  const detail::render_target &target() const {
    return target_;
  }
  
  const detail::texture_handle &texture1() const {
    return detail::texture_core_access::texture1(target_);
  }

  detail::render_target target_;

  friend class scoped_render_target;
  friend class detail::texture_core_access;
};

class scoped_render_target : private boost::noncopyable {
 public:
  explicit scoped_render_target(const render_target &target) : target_(target.target()) {}

 private:
  const detail::scoped_render_target target_;
};
}}

#endif
