#ifndef NGY313_GRAPHIC_DETAIL_WINDOWS_RENDER_TARGET_HPP_
#define NGY313_GRAPHIC_DETAIL_WINDOWS_RENDER_TARGET_HPP_
#include <cassert>
#include <stdexcept>
#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>
#include <boost/signals2/trackable.hpp>
#include <ngy313/graphic/detail/windows/device.hpp>
#include <ngy313/graphic/detail/windows/scoped_back_buffer.hpp>
#include <ngy313/graphic/detail/windows/scoped_back_z_and_stencil.hpp>
#include <ngy313/graphic/detail/windows/scoped_viewport.hpp>
#include <ngy313/graphic/detail/windows/texture.hpp>
#include <ngy313/graphic/detail/graphic.hpp>

namespace ngy313 { namespace graphic { namespace detail {
class render_target : public boost::signals2::trackable, private boost::noncopyable {
 public:
  render_target(graphic_device &device, const int width, const int height) 
      : width_(width),
        height_(height),
        target_(create_texture(device.device(), width_, height_)),
        target_surface_(surface_level(target_)),
        z_and_stencil_(create_z_and_stencil(device.device(), width_, height_)),
        viewport_(init_viewport(width_, height_)),
        device_(device.device()),
        after_reset() {
    device.before_reset.connect(boost::bind(&render_target::release, this, _1));
    device.after_reset.connect(boost::bind(&render_target::reset, this, _1));
  }

  int width() const {
    return width_;
  }

  int height() const {
    return height_;
  }

  boost::signals2::signal<void ()> after_reset;
  
 private:
  void begin(const device_handle &device) const {
    assert(device);
    set_render_surface(device, target_surface_);
    set_z_and_stencil(device, z_and_stencil_);
    set_viewport(device, viewport_);
    init_device(device);
  }

  void release(const device_handle &device) {
    UNREFERENCED_PARAMETER(device);
    target_.reset();
    target_surface_.reset();
    z_and_stencil_.reset();
  }

  void reset(const device_handle &device) {
    assert(device);
    target_ = create_texture(device, width_, height_);
    target_surface_ = surface_level(target_);
    z_and_stencil_ = create_z_and_stencil(device, width_, height_);
    after_reset();
  }

  const texture_handle &texture1() const {
    return target_;
  }

  const device_handle &device() const {
    return device_;
  }

  const int width_;
  const int height_;
  texture_handle target_;
  surface_handle target_surface_;
  surface_handle z_and_stencil_;
  const viewport viewport_;
  const device_handle &device_;

  friend class scoped_render_target;
  friend class texture_core_access;
};

class scoped_render_target : private boost::noncopyable {
 public:
  explicit scoped_render_target(const render_target &target)
     : viewport_(target.device()), back_buffer_(target.device()), back_z_and_stencil_(target.device()) {
    target.begin(target.device());
  }

 private:
  const scoped_viewport viewport_;
  const scoped_back_buffer back_buffer_;
  const scoped_back_z_and_stencil back_z_and_stencil_;
};
}}}

#endif
