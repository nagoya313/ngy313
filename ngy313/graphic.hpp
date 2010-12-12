#pragma once
#include <functional>
#include <boost/noncopyable.hpp>
#include <boost/signals2/trackable.hpp>
#include <boost/bind.hpp>
#include "detail/window_singleton.hpp"
#include "detail/drawable_core_access.hpp"

namespace ngy313 {
class scoped_render : private boost::noncopyable {
 public:
  scoped_render() : succeeded_(detail::begin_scene(detail::graphic_device())) {}
  
  ~scoped_render() {
    detail::end_scene(detail::graphic_device());
  }

  bool succeeded() const {
    return succeeded_;
  }

 private:
  const bool succeeded_;
};

inline
void clear_screen(const std::uint32_t col) {
  detail::clear(detail::graphic_device(), col);
}

inline
void present() {
  detail::present(detail::window(), detail::graphic_device(), true, detail::before_reset(), detail::after_reset());
}

template <typename Drawable>
void draw(const Drawable &drawable) {
  detail::draw(detail::graphic_device(), drawable);
}

class render_target : public boost::signals2::trackable, private boost::noncopyable {
 public:
  render_target(const float width, const float height) 
      : width_(width),
        height_(height),
        target_(detail::create_texture(detail::graphic_device(), width_, height_)),
        target_surface_(detail::surface_level(target_)),
        z_and_stencil_(detail::create_z_and_stencil(detail::graphic_device(), width_, height_)),
        view_port_(detail::init_viewport(width_, height_)) {
    detail::before_reset().connect(boost::bind(&render_target::release, this));
    detail::after_reset().connect(boost::bind(&render_target::reset, this));
  }

  void begin() const {
    detail::set_render_target(detail::graphic_device(), target_surface_);
    detail::set_z_and_stencil(detail::graphic_device(), z_and_stencil_);
    detail::set_view_port(detail::graphic_device(), view_port_);
    detail::init_device(detail::graphic_device());
  }

  float width() const {
    return width_;
  }

  float height() const {
    return height_;
  }

  void release() {
    target_.reset();
    target_surface_.reset();
    z_and_stencil_.reset();
  }

  void reset() {
    target_ = detail::create_texture(detail::graphic_device(), width_, height_);
    target_surface_ = detail::surface_level(target_);
    z_and_stencil_ = detail::create_z_and_stencil(detail::graphic_device(), width_, height_);
  }

 private:
  friend detail::drawable_core_access;

  const detail::texture_handle &texture1() const {
    return target_;
  }

  const float width_;
  const float height_;
  detail::texture_handle target_;
  detail::surface_handle target_surface_;
  detail::surface_handle z_and_stencil_;
  const detail::viewport view_port_;
};

class scoped_render_target : private boost::noncopyable {
 public:
  explicit scoped_render_target(const render_target &target) 
      : viewport_(detail::graphic_device()),
        back_buffer_(detail::graphic_device()),
        back_z_and_stencil_(detail::graphic_device()) {
    target.begin();
  }

 private:
  const detail::scoped_viewport viewport_;
  const detail::scoped_back_buffer back_buffer_;
  const detail::scoped_back_z_and_stencil back_z_and_stencil_;
};
}