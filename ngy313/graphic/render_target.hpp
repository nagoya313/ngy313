#pragma once
#include <cassert>
#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>
#include <boost/signals2/signal.hpp>
#include <boost/signals2/trackable.hpp>
#include <ngy313/graphic/detail/device.hpp>
#include <ngy313/graphic/detail/scoped_back_buffer.hpp>
#include <ngy313/graphic/detail/scoped_back_z_and_stencil.hpp>
#include <ngy313/graphic/detail/scoped_viewport.hpp>
#include <ngy313/graphic/detail/singleton.hpp>
#include <ngy313/graphic/detail/texture.hpp>

namespace ngy313 { namespace graphic {
typedef boost::signals2::signal<void ()> reseted_signal;

class render_target : public boost::signals2::trackable, private boost::noncopyable {
 public:
  render_target(const float width, const float height) 
      : width_(width),
        height_(height),
        target_(detail::create_texture(detail::device().device(), width_, height_)),
        target_surface_(detail::surface_level(target_)),
        z_and_stencil_(detail::create_z_and_stencil(detail::device().device(), width_, height_)),
        viewport_(detail::init_viewport(width_, height_)),
        after_reset_() {
    detail::device().before_reset.connect(boost::bind(&render_target::release, this, _1));
    detail::device().after_reset.connect(boost::bind(&render_target::reset, this, _1));
  }

  void begin() const {
    detail::set_render_target(detail::device().device(), target_surface_);
    detail::set_z_and_stencil(detail::device().device(), z_and_stencil_);
    detail::set_viewport(detail::device().device(), viewport_);
    detail::init_device(detail::device().device());
  }

  float width() const {
    return width_;
  }

  float height() const {
    return height_;
  }

  void release(const detail::device_handle &device) {
    UNREFERENCED_PARAMETER(device);
    target_.reset();
    target_surface_.reset();
    z_and_stencil_.reset();
  }

  void reset(const detail::device_handle &device) {
    assert(device);
    target_ = detail::create_texture(device, width_, height_);
    target_surface_ = detail::surface_level(target_);
    z_and_stencil_ = detail::create_z_and_stencil(device, width_, height_);
    after_reset_();
  }

  // ŠO•”‚©‚ç‚Ì()ŒÄ‚Ño‚µ‚ğ••ˆó‚µ‚½signal‚É•Ï‚¦‚é‚©‚à‚µ‚ê‚È‚¢
  void connect_after_reset(const reseted_signal::slot_type &slot) {
    after_reset_.connect(slot);
  }

 private:
  const detail::texture_handle &texture1() const {
    return target_;
  }

  const float width_;
  const float height_;
  detail::texture_handle target_;
  detail::surface_handle target_surface_;
  detail::surface_handle z_and_stencil_;
  const detail::viewport viewport_;
  reseted_signal after_reset_;

  friend class detail::texture_access;
  friend class detail::texture_core_access;
};

class scoped_render_target : private boost::noncopyable {
 public:
  explicit scoped_render_target(const render_target &target) : viewport_(detail::device().device()),
                                                               back_buffer_(detail::device().device()),
                                                               back_z_and_stencil_(detail::device().device()) {
    target.begin();
  }

 private:
  const detail::scoped_viewport viewport_;
  const detail::scoped_back_buffer back_buffer_;
  const detail::scoped_back_z_and_stencil back_z_and_stencil_;
};
}}
