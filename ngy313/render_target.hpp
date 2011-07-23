#ifndef NGY313_RENDER_TARGET_HPP_
#define NGY313_RENDER_TARGET_HPP_

#include <boost/noncopyable.hpp>
#include <ngy313/texture.hpp>
#include <ngy313/detail/ngy313.hpp>

#if defined(_WIN32)
#include <ngy313/detail/direct3d9_render_target.hpp>
#elif defined(__linux__)
#endif

namespace ngy313 {
template <typename Target>
class basic_render_target : boost::noncopyable {
 public:
  explicit basic_render_target(int width, int height)
      : target_(std::make_shared<Target>(
                    detail::main_singleton::instance().graphic(),
                    width,
                    height)) {}

  int width() const {
    return target_->width();
  }

  int height() const {
    return target_->height();
  }

  void begin() {
    target_->begin();
  }

  void end() {
    target_->end();
  }

  const std::shared_ptr<Target> &get_image() const {
    return target_;
  }

 private:
  std::shared_ptr<Target> target_;
};

template <typename ScopedTarget>
class basic_scoped_render_target : boost::noncopyable {
 public:
  template <typename Target>
  explicit basic_scoped_render_target(basic_render_target<Target> &target)
      : target_(detail::main_singleton::instance().graphic(), target) {}

 private:
  ScopedTarget target_;
};

#if defined(_WIN32)
typedef basic_render_target<detail::direct3d9_render_target<texture>> render_target;
typedef basic_scoped_render_target<detail::direct3d9_scoped_render_target<render_target>> 
    scoped_render_target;
#elif defined(__linux__)
#endif
}

#endif
