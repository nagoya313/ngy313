#ifndef NGY313_DIRECT3D9_RENDER_TARGET_HPP_
#define NGY313_DIRECT3D9_RENDER_TARGET_HPP_

#include <cassert>
#include <stdexcept>
#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>
#include <boost/signals2/trackable.hpp>
#include <ngy313/detail/graphic.hpp>
#include <ngy313/detail/image.hpp>

namespace ngy313 { namespace detail {
template <typename Statas, typename SaveReset>
class scoped_statas : boost::noncopyable {
 public:
  explicit scoped_statas(graphic_system &device) 
      : device_(device), current_statas_(SaveReset::save(device_)) {
  }

  ~scoped_statas() {
    SaveReset::reset(device_, current_statas_);
  }

 private:
  graphic_system &device_;
  Statas current_statas_;
};

template <typename Target>
class direct3d9_scoped_render_target : boost::noncopyable {
  typedef std::unique_ptr<IDirect3DSurface9, com_delete> surface_handle;

 public:
  explicit direct3d9_scoped_render_target(graphic_system &device,
                                          Target &target) 
      : target_(target),
        target_surface_(device),
        z_and_stencil_(device),
        viewport_(device) {
    target_.begin();
  }

  ~direct3d9_scoped_render_target() {
    target_.end();
  }

 private:
  struct state_render_surface {
    static surface_handle save(graphic_system &device) {
      assert(device.handle());
      LPDIRECT3DSURFACE9 target;
      if (FAILED(device.handle()->GetRenderTarget(0, &target))) {
        throw std::runtime_error(
                  "レンダリングターゲットのサーフエイスの取得に失敗しました");
      }
      return surface_handle(target);
    }

    static void reset(graphic_system &device, const surface_handle &surface) {
      assert(device.handle());
      assert(surface);
      device.handle()->SetRenderTarget(0, surface.get());
    }
  };

  struct state_z_and_stencil {
    static surface_handle save(graphic_system &device) {
      assert(device.handle());
      assert(device.handle());
      LPDIRECT3DSURFACE9 z_s;
      if (FAILED(device.handle()->GetDepthStencilSurface(&z_s))) {
        throw std::runtime_error(
                  "レンダリングターゲットの深度及びステンシルバッファの取得に失敗しました");
      }
      return surface_handle(z_s);
    }

    static void reset(graphic_system &device, const surface_handle &surface) {
      assert(device.handle());
      assert(surface);
      device.handle()->SetDepthStencilSurface(surface.get());
    }
  };

  struct state_viewport {
    static D3DVIEWPORT9 save(graphic_system &device) {
      assert(device.handle());
      D3DVIEWPORT9 viewport;
      device.handle()->GetViewport(&viewport);
      return viewport;
    }

    static void reset(graphic_system &device, const D3DVIEWPORT9 &viewport) {
      assert(device.handle());
      device.handle()->SetViewport(&viewport);
    }
  };

  Target &target_;
  scoped_statas<surface_handle, state_render_surface> target_surface_;
  scoped_statas<surface_handle, state_z_and_stencil> z_and_stencil_;
  scoped_statas<D3DVIEWPORT9, state_viewport> viewport_;
};

template <typename Texture>
class direct3d9_render_target
    : public boost::signals2::trackable, 
      public image_base<Texture>,
      boost::noncopyable {
  typedef std::unique_ptr<IDirect3DTexture9, com_delete> texture_handle;
  typedef std::unique_ptr<IDirect3DSurface9, com_delete> surface_handle;

 public:
  explicit direct3d9_render_target(graphic_system &device,
                                   int width,
                                   int height) 
      : device_(device),
        width_(width),
        height_(height),
        target_(new Texture(width_, height_)),
        copy_target_(create_texture(width_, height_)),
        target_surface_(surface_level(target_->handle())),
        z_and_stencil_(create_z_and_stencil(width_, height_)),
        viewport_(init_viewport(width_, height_)) {
    device.before_reset().connect(
        boost::bind(&direct3d9_render_target::release, this));
    device.after_reset().connect(
        boost::bind(&direct3d9_render_target::reset, this));
  }

  virtual int width() const {
    return width_;
  }

  virtual int height() const {
    return height_;
  }

  void begin() {
    set_render_surface(target_surface_);
    set_z_and_stencil(z_and_stencil_);
    set_viewport(viewport_);
  }

  void end() {
    assert(device_.handle());
    device_.handle()->GetRenderTargetData(target_surface_.get(),
                                          surface_level(copy_target_).get());
  }

  virtual const Texture &get_texture() const {
    return *target_;
  }
  
 private:
  void release() {
    target_.reset();
    target_surface_.reset();
    z_and_stencil_.reset();
  }

  void reset() {
    target_.reset(new Texture(width_, height_));
    target_surface_ = surface_level(target_->handle());
    z_and_stencil_ = create_z_and_stencil(width_, height_);
    assert(device_.handle());
    device_.handle()->UpdateTexture(copy_target_.get(),
                                    target_->handle().get());
  }

  template <typename Texture>
  static surface_handle surface_level(const Texture &tex) {
    assert(tex);
    LPDIRECT3DSURFACE9 surface;
    if (FAILED(tex->GetSurfaceLevel(0, &surface))) {
      throw std::runtime_error("サーフェイスレベルの取得に失敗しました");
    }
    return surface_handle(surface);
  }

  static D3DVIEWPORT9 init_viewport(int width, int height) {
    const D3DVIEWPORT9 viewport = {0, 0, width, height, 0.f, 1.f};
    return viewport;
  }
  
  void set_viewport(const D3DVIEWPORT9 &viewport) {
    assert(device_.handle());
    device_.handle()->SetViewport(&viewport);
  }

  surface_handle create_z_and_stencil(int width, int height) {
    assert(device_.handle());
    LPDIRECT3DSURFACE9 surface;
    if (FAILED(device_.handle()->CreateDepthStencilSurface(width, 
                                                           height,
                                                           D3DFMT_D24S8,
                                                           D3DMULTISAMPLE_NONE,
                                                           0, 
                                                           TRUE, 
                                                           &surface, 
                                                           nullptr))) {
      throw std::runtime_error("深度及びステンシルバッファの作成に失敗しました");
    }
    return surface_handle(surface);
  }

  void set_render_surface(const surface_handle &surface) {
    assert(device_.handle());
    assert(surface);
    device_.handle()->SetRenderTarget(0, surface.get());
  }

  void set_z_and_stencil(const surface_handle &surface) {
    assert(device_.handle());
    assert(surface);
    device_.handle()->SetDepthStencilSurface(surface.get());
  }

  texture_handle create_texture(int width, int height) {
    assert(device_.handle());
    LPDIRECT3DTEXTURE9 tex;
    if (FAILED(D3DXCreateTexture(device_.handle().get(),
                                 width, 
                                 height,
                                 1,
                                 0,
                                 D3DFMT_A8R8G8B8, 
                                 D3DPOOL_SYSTEMMEM, 
                                 &tex))) {
      throw std::runtime_error("バックアップテクスチャの作成に失敗しました");
    }
    return texture_handle(tex);
  }

  graphic_system &device_;
  int width_;
  int height_;
  std::unique_ptr<Texture> target_;
  texture_handle copy_target_;
  surface_handle target_surface_;
  surface_handle z_and_stencil_;
  D3DVIEWPORT9 viewport_;
};
}}

#endif
