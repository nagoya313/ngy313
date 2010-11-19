#pragma once
#include <boost/signals2/trackable.hpp>
#include <boost/bind.hpp>
#include "detail/window_singleton.hpp"
#include  "detail/drawable_core_access.hpp"

namespace ngy313 {
  void a() {}
class render_target : public boost::signals2::trackable {
 public:
  render_target(const float width, const float height) 
      : width_(width),
        height_(height),
        target_(detail::create_texture(detail::graphic_device(), width_, height_)),
        target_surface_(detail::surface_level(target_)),
        z_and_stencil_(detail::create_z_and_stencil(detail::graphic_device(), width_, height_)) {
    detail::before_reset().connect(boost::bind(&render_target::release, this));
    detail::after_reset().connect(boost::bind(&render_target::reset, this));
  }

  void begin() const {
    detail::set_render_target(detail::graphic_device(), target_surface_);
    detail::set_z_and_stencil(detail::graphic_device(), z_and_stencil_);
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
};

class scoeped_render_target {
 public:
  explicit scoeped_render_target(const render_target &target) 
      : view_port_(detail::view_port(detail::graphic_device())),
        back_buffer_(detail::render_target(detail::graphic_device())),
        back_z_and_stencil_(detail::z_and_stencil(detail::graphic_device())) {
    target.begin();
  }

  ~scoeped_render_target() {
    detail::set_view_port(detail::graphic_device(), view_port_);
    detail::set_render_target(detail::graphic_device(), back_buffer_);
    detail::set_z_and_stencil(detail::graphic_device(), back_z_and_stencil_);
  }

 private:
  const D3DVIEWPORT9 view_port_;
  const detail::surface_handle back_buffer_;
  const detail::surface_handle back_z_and_stencil_;
};
}
