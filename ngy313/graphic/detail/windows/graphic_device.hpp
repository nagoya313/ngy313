#ifndef NGY313_GRAPHIC_DETAIL_WINDOWS_GRAPHIC_DEVICE_HPP_
#define NGY313_GRAPHIC_DETAIL_WINDOWS_GRAPHIC_DEVICE_HPP_
#include <cassert>
#include <boost/noncopyable.hpp>
#include <ngy313/graphic/detail/windows/device.hpp>
#include <ngy313/window/detail/windows/main_window.hpp>

namespace ngy313 { namespace graphic { namespace detail {
class graphic_device : private boost::noncopyable {
 public:
  explicit graphic_device(const window::detail::main_window &window)
      : before_reset(),
        after_reset(),
        windowed_(true),
        width_(window.width()),
        height_(window.height()),
        base_(create_base()),
        device_(create_device(window::detail::window(), base_, windowed_)) {
    init_device(device_);
  }

  bool windowed() const {
    return windowed_;
  }

  void present() const {
    assert(device_);
    switch (device_->Present(nullptr, nullptr, nullptr, nullptr)) {
      case D3DERR_DEVICELOST:
	      if (device_->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
          reset();
        }
	      break;
      case D3DERR_DRIVERINTERNALERROR:
	      throw std::runtime_error("内部ドライバエラーが発生しました");
	      break;
      default:
	      break;
    }
  }

  void resize(const int width_size, const int height_size) {
    width_ = width_size;
    height_ = height_size;
    reset();
    assert(width_size == width());
    assert(height_size == height());
  }

  void change_screen_mode(const bool flag) {
    windowed_ = flag;
    reset();
    assert(windowed() == flag);
  }

  int width() const {
    return width_;
  }

  int height() const {
    return height_;
  }

  void clear(const std::uint32_t col) const {
    assert(device_);
    device_->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, col, 1.f, 0);
  }

  bool begin_scene() const {
    assert(device_);
    return SUCCEEDED(device_->BeginScene());
  }

  void end_scene() const {
    assert(device_);
    device_->EndScene();
  }

  std::uint32_t pixel_color(const int x, const int y) const {
    assert(device_);
    RECT rect = {x, y, x + 1, y + 1};
    D3DLOCKED_RECT lock_rect;
    const surface_handle target(back_buffer(device_));
    if(SUCCEEDED(target->LockRect(&lock_rect, &rect, D3DLOCK_READONLY))) {
      const std::uint32_t *color = static_cast<std::uint32_t *>(lock_rect.pBits);
      target->UnlockRect();
      return *color;
    }
    return 0;
  }

  const device_handle &device() const {
    return device_;
  }

  boost::signals2::signal<void (const device_handle &)> before_reset;

  boost::signals2::signal<void (const device_handle &)> after_reset;

 private:
  void reset() const {
    assert(device_);
    D3DPRESENT_PARAMETERS present_parameter = init_present_parameters(windowed(), width(), height());
    before_reset(device_);
    if (FAILED(device_->Reset(&present_parameter))) {
      throw std::runtime_error("デバイスリセットに失敗しました");
	  }
    after_reset(device_);
    init_device(device_);
  }

  bool windowed_;
  int width_;
  int height_;
  const base_handle base_;
  const device_handle device_;
};
}}}

#endif
