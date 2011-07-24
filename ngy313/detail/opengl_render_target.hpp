#ifndef NGY313_OPENGL_RENDER_TARGET_HPP_
#define NGY313_OPENGL_RENDER_TARGET_HPP_

#include <cassert>
#include <stdexcept>
#include <thread>
#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>
#include <boost/signals2/trackable.hpp>
#include <ngy313/detail/graphic.hpp>
#include <ngy313/detail/image.hpp>

namespace ngy313 { namespace detail {
template <typename Target>
class opengl_scoped_render_target : boost::noncopyable {
 public:
  explicit opengl_scoped_render_target(graphic_system &device,
                                                         Target &target) 
      : device_(device), target_(target) {
    target_.begin();
  }

  ~opengl_scoped_render_target() {
    target_.end();
  }

 private:
  graphic_system &device_;
  Target &target_;
};

struct base_fbo {
  template <typename Device>
  base_fbo(Device &device) {
    static std::once_flag flag;
    std::call_once(flag, [&] {this->init_fbo(device);});
  }

 private:
  template <typename Device>
  static void init_fbo(Device &device) {
    const typename Device::scoped_render render(device);
    if (glewInit() != GLEW_OK) {
      throw std::runtime_error("GLEWの初期化に失敗しました");
    }
    if (!GLEW_EXT_framebuffer_object) {
      throw std::runtime_error("フレームバッファオブジェクトがサポートされていません");
    }
  }
};

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

struct gl_viewport {
  GLint x;
  GLint y;
  GLint width;
  GLint height;
};

struct state_viewport {
  static gl_viewport save(graphic_system &device) {
    const graphic_system::scoped_render render(device);
    gl_viewport viewport;
    glGetIntegerv(GL_VIEWPORT, reinterpret_cast<GLint *>(&viewport));
    return viewport;
  }

  static void reset(graphic_system &device, const gl_viewport &viewport) {
    const graphic_system::scoped_render render(device);
    glViewport(viewport.x, viewport.y, viewport.width, viewport.height);
  }
};

template <typename Texture>
class opengl_render_target
    : public boost::signals2::trackable, 
      public image_base<Texture>,
      base_fbo,
      boost::noncopyable {
  struct frame_buffer_delete {
    explicit frame_buffer_delete(graphic_system &device) : device_(device) {}
  
    void operator ()(const GLuint *buffer) const {
      const graphic_system::scoped_render render(device_);
      glDeleteFramebuffersEXT(1, buffer); 
    }
  
   private:
    graphic_system &device_;
  };

  struct render_buffer_delete {
    explicit render_buffer_delete(graphic_system &device) : device_(device) {}
  
    void operator ()(const GLuint *buffer) const {
      const graphic_system::scoped_render render(device_);
      glDeleteRenderbuffersEXT(1, buffer);
    }
  
   private:
    graphic_system &device_;
  };

  typedef std::unique_ptr<GLuint, frame_buffer_delete> frame_buffer_handle;
  typedef std::unique_ptr<GLuint, render_buffer_delete> render_buffer_handle;
  typedef std::shared_ptr<GLuint> texture_handle;

 public:
  explicit opengl_render_target(graphic_system &device,
                                   int width,
                                   int height) 
      : base_fbo(device),
        device_(device),
        width_(width),
        height_(height),
        target_(width, height),
        render_buffer_(create_render_buffer(device, width, height)),
        frame_buffer_(create_frame_buffer(device)) {
     const graphic_system::scoped_render render(device);
     glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, *frame_buffer_);
     glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, *target_.handle(), 0);
     glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, *render_buffer_);
     glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
  }

  virtual int width() const {
    return width_;
  }

  virtual int height() const {
    return height_;
  }

  void begin() {
    const graphic_system::scoped_render render(device_);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, *frame_buffer_);
    glViewport(0, 0, width(), height());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.f, static_cast<float>(width()), 0.f, static_cast<float>(height()), 0.f, 1.f);
  }

  void end() {
    const graphic_system::scoped_render render(device_);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
  }

  virtual const Texture &get_texture() const {
    return target_;
  }
  
 private:
  template <typename Device>
  static frame_buffer_handle create_frame_buffer(Device &device) {
    const typename Device::scoped_render render(device);
    GLuint * const frame = new GLuint();
    glGenFramebuffersEXT(1, frame);
    return frame_buffer_handle(frame, frame_buffer_delete(device));
  }

  template <typename Device>
  static render_buffer_handle create_render_buffer(Device &device, int width, int height) {
    const typename Device::scoped_render render(device);
    GLuint * const frame = new GLuint();
    glGenRenderbuffersEXT(1, frame);
    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, *frame);
    glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, width, height);
    return render_buffer_handle(frame, render_buffer_delete(device));
  }

  graphic_system &device_;
  int width_;
  int height_;
  Texture target_;
  render_buffer_handle render_buffer_;
  frame_buffer_handle frame_buffer_;
};
}}

#endif
