#ifndef NGY313_DETAIL_DIRECT3D9_GRAPHIC_SYSTEM_HPP_
#define NGY313_DETAIL_DIRECT3D9_GRAPHIC_SYSTEM_HPP_

#include <cassert>
#include <cstdint>
#include <memory>
#include <boost/noncopyable.hpp>
#include <d3d9.h>
#include <ngy313/fwd.hpp>
#include <ngy313/detail/com.hpp>

namespace ngy313 { namespace detail {
class direct3d9_graphic_system : boost::noncopyable {
  typedef std::unique_ptr<IDirect3D9, com_delete> setup_handle;
  typedef std::unique_ptr<IDirect3DDevice9, com_delete> device_handle;
  typedef std::unique_ptr<IDirect3DSurface9, com_delete> surface_handle;
 
 public:
  typedef const device_handle &handle_type;

  class scoped_render : boost::noncopyable {
   public:
  	template <typename Graphic>
  	explicit scoped_render(const Graphic &system)
        : device_(system.handle()), succeeded_(begin_scene()) {}

    ~scoped_render() {
      if (succeeded()) {
        end_scene();
      }
    }

    bool succeeded() const {
      return succeeded_;
    }

   private:
    bool begin_scene() {
      assert(device_);
      return SUCCEEDED(device_->BeginScene());
    }

    void end_scene() {
      assert(device_);
      device_->EndScene();
    }
    
    const device_handle &device_;
    bool succeeded_;
  };
  
  template <typename Window>
  explicit direct3d9_graphic_system(const Window &window)
      : width_(window.width()),
        height_(window.height()),
        base_(create_base()),
        device_(create_device(window, base_)) {
    init_device();
  }

  void resize(int width_size, int height_size) {
    width_ = width_size;
    height_ = height_size;
    reset();
    assert(width_size == width() && height_size == height());
  }

  int width() const {
    return width_;
  }

  int height() const {
    return height_;
  }

  void present() {
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

  template <typename Wrap>
  void clear_screen(const basic_color_wrap<Wrap> &color) {
    assert(device_);
    device_->Clear(0,
                   nullptr,
                   D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
                   color.get_color_code(), 
                   1.f,
                   0);
  }

  std::uint32_t pixel_color(int x, int y) const {
    assert(device_);
    RECT rect = {x, y, x + 1, y + 1};
    D3DLOCKED_RECT lock_rect;
    const surface_handle target(back_buffer());
    if(SUCCEEDED(target->LockRect(&lock_rect, 
                                  &rect, 
                                  D3DLOCK_READONLY))) {
      const std::uint32_t * const color 
          = static_cast<const std::uint32_t *>(lock_rect.pBits);
      target->UnlockRect();
      return *color;
    } else {
      throw std::runtime_error("色の取得に失敗しました");
    }
  }

  template <typename Drawable>
  void draw_primitive(Drawable &&drawable) {
    assert(device_);
    device_->SetFVF(fvf_traits<typename boost::mpl::at<
                                   typename std::decay<Drawable>::type::list_type, 
                                   fvf_key>::type>::fvf_type::value);
    const auto vertex = drawable.vertex();
    device_->DrawPrimitiveUP(boost::mpl::at<typename std::decay<Drawable>::type::list_type,
                                            primitive_key>::type::type::value,
                             boost::mpl::at<typename std::decay<Drawable>::type::list_type,
                                            count_key>::type::type::value, 
                             vertex.data(), 
                             sizeof(vertex.front()));
  }

  template <typename Drawable>
  void set_texture(const Drawable &drawable) {
    assert(device_);
    device_->SetTexture(0, drawable.texture1().handle().get());
  }

  void unset_texture() {
    assert(device_);
    device_->SetTexture(0, nullptr);
  }

  const device_handle &handle() const {
    return device_;
  }

 private:
  static D3DPRESENT_PARAMETERS 
      init_present_parameters(bool windowed,
                              int width,
                              int height) {
    const D3DPRESENT_PARAMETERS present_parameters = {
      width,
      height,
      windowed ? D3DFMT_UNKNOWN : D3DFMT_X8R8G8B8,
      1,
      D3DMULTISAMPLE_NONE,
      0,
      D3DSWAPEFFECT_DISCARD,
      nullptr,
      windowed ? TRUE : FALSE,
      TRUE,
      D3DFMT_D24S8,
      D3DPRESENTFLAG_LOCKABLE_BACKBUFFER,
      D3DPRESENT_RATE_DEFAULT,
      D3DPRESENT_INTERVAL_DEFAULT
    };
    return present_parameters;
  }

  static setup_handle create_base() {
    const LPDIRECT3D9 direct3d = Direct3DCreate9(D3D_SDK_VERSION);
    if (!direct3d) {
      throw std::runtime_error("Direct3Dの初期化に失敗しました");
    }
    return setup_handle(direct3d);
  }

  template <typename Window>
  static device_handle create_device(const Window &window, 
                                     const setup_handle &direct3d) {
    assert(window.handle());
    assert(direct3d);
    D3DPRESENT_PARAMETERS present_parameters
        = init_present_parameters(true, window.width(), window.height());
    LPDIRECT3DDEVICE9 dev;
    const HRESULT hard_hal_hr 
        = direct3d->CreateDevice(D3DADAPTER_DEFAULT, 
                                 D3DDEVTYPE_HAL, 
                                 window.handle(), 
                                 D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                 &present_parameters,
                                 &dev);
    if (FAILED(hard_hal_hr)) {
      const HRESULT soft_hal_hr
          = direct3d->CreateDevice(D3DADAPTER_DEFAULT,
                                   D3DDEVTYPE_HAL, 
                                   window.handle(), 
                                   D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                   &present_parameters,
                                   &dev); 
      if (FAILED(soft_hal_hr)) {
        const HRESULT ref_hr =
            direct3d->CreateDevice(D3DADAPTER_DEFAULT,
                                   D3DDEVTYPE_REF,
                                   window.handle(), 
                                   D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                   &present_parameters, 
                                   &dev);
        if (FAILED(ref_hr)) {
          throw std::runtime_error(
              "Direct3Dデバイスの初期化に失敗しました");
	      }  
      }
    }
    return device_handle(dev);
  }

  void init_device() {
    assert(device_);
  }

  void reset() {
    assert(device_);
    D3DPRESENT_PARAMETERS present_parameter 
        = init_present_parameters(true, width(), height());
    if (FAILED(device_->Reset(&present_parameter))) {
      throw std::runtime_error("デバイスのリセットに失敗しました");
	  }
    init_device();
  }

  surface_handle back_buffer() const {
    assert(device_);
    LPDIRECT3DSURFACE9 back;
    if (FAILED(device_->GetBackBuffer(0,
                                      0,
                                      D3DBACKBUFFER_TYPE_MONO, 
                                      &back))) {
      throw std::runtime_error("バックバッファの取得に失敗しました");
    }
    return surface_handle(back);
  }

  int width_;
  int height_;
  setup_handle base_;
  device_handle device_;
};
}}

#endif
