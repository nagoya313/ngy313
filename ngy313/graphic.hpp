#pragma once
#include <boost/noncopyable.hpp>
#include <boost/signals2/trackable.hpp>
#include <boost/bind.hpp>
#include "detail/window_singleton.hpp"
#include "detail/drawable_core_access.hpp"
#include "vector.hpp"

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

template <typename Camera>
void set_camera(const Camera &cam) {
  detail::set_camera(detail::graphic_device(), cam);
}

class render_target : public boost::signals2::trackable, private boost::noncopyable {
 public:
  render_target(const vector2 &size) 
      : size_(size),
        target_(detail::create_texture(detail::graphic_device(), size_.x(), size_.y())),
        target_surface_(detail::surface_level(target_)),
        z_and_stencil_(detail::create_z_and_stencil(detail::graphic_device(), size_.x(), size_.y())),
        view_port_(detail::init_viewport(size_.x(), size_.y())) {
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
    return size_.x();
  }

  float height() const {
    return size_.y();
  }

  void release() {
    target_.reset();
    target_surface_.reset();
    z_and_stencil_.reset();
  }

  void reset() {
    target_ = detail::create_texture(detail::graphic_device(), size_.x(), size_.y());
    target_surface_ = detail::surface_level(target_);
    z_and_stencil_ = detail::create_z_and_stencil(detail::graphic_device(), size_.x(), size_.y());
  }

 private:
  friend detail::drawable_core_access;

  const detail::texture_handle &texture1() const {
    return target_;
  }

  const vector2 size_;
  detail::texture_handle target_;
  detail::surface_handle target_surface_;
  detail::surface_handle z_and_stencil_;
  const detail::viewport view_port_;
};

class scoped_render_target : private boost::noncopyable {
 public:
  explicit scoped_render_target(const render_target &target) 
      : view_port_(detail::view_port(detail::graphic_device())),
        back_buffer_(detail::render_target(detail::graphic_device())),
        back_z_and_stencil_(detail::z_and_stencil(detail::graphic_device())) {
    target.begin();
  }

  ~scoped_render_target() {
    detail::set_view_port(detail::graphic_device(), view_port_);
    detail::set_render_target(detail::graphic_device(), back_buffer_);
    detail::set_z_and_stencil(detail::graphic_device(), back_z_and_stencil_);
  }

 private:
  const detail::viewport view_port_;
  const detail::surface_handle back_buffer_;
  const detail::surface_handle back_z_and_stencil_;
};
}