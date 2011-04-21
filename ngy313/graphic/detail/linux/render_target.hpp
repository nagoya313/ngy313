#ifndef NGY313_GRAPHIC_DETAIL_LINUX_RENDER_TARGET_HPP_
#define NGY313_GRAPHIC_DETAIL_LINUX_RENDER_TARGET_HPP_
#include <memory>
#include <stdexcept>
#include <boost/noncopyable.hpp>
#include <ngy313/graphic/detail/linux/texture.hpp>
#include <ngy313/graphic/detail/linux/scoped_viewport.hpp>
#include <ngy313/utility/call_once.hpp>
#include <iostream>

namespace ngy313 { namespace graphic { namespace detail {
struct frame_buffer_delete {
  explicit frame_buffer_delete(device_handle &device) : device_(device) {}
  
  void operator ()(const GLuint * const buffer) const {
    device_.begin_scene();
    glDeleteFramebuffersEXT(1, buffer); 
    device_.end_scene();
  }
  
 private:
  device_handle &device_;
};

struct render_buffer_delete {
  explicit render_buffer_delete(device_handle &device) : device_(device) {}
  
  void operator ()(const GLuint * const buffer) const {
    device_.begin_scene();
    glDeleteRenderbuffersEXT(1, buffer);
    device_.end_scene();
  }
  
 private:
  device_handle &device_;
};

typedef std::unique_ptr<GLuint, frame_buffer_delete> frame_buffer_handle;
typedef std::unique_ptr<GLuint, render_buffer_delete> render_buffer_handle;

inline
void glew_init(device_handle &device) {
  const utility::call_once init([&] {
    device.begin_scene();
    if (glewInit() != GLEW_OK) {
       throw std::runtime_error("GLEWの初期化に失敗しました");
    }
    device.end_scene();
  });
  
}

inline
frame_buffer_handle create_frame_buffer(device_handle &device) {
  glew_init(device);
  const utility::call_once init([] {
    if (!GLEW_EXT_framebuffer_object) {
      throw std::runtime_error("フレームバッファオブジェクトがサポートされていません");
    }
  });
  GLuint *frame = new GLuint();
  device.begin_scene();
  glGenFramebuffersEXT(1, frame);
  device.end_scene();
  return frame_buffer_handle(frame, frame_buffer_delete(device));
}

inline
render_buffer_handle create_render_buffer(device_handle &device, const int width, const int height) {
  glew_init(device);
  const utility::call_once init([] {
    if (!GLEW_EXT_framebuffer_object) {
      throw std::runtime_error("フレームバッファオブジェクトがサポートされていません");
    }
  });
  GLuint *frame = new GLuint();
  device.begin_scene();
  glGenRenderbuffersEXT(1, frame);
  glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, *frame);
  glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, width, height);
  device.end_scene();
  return render_buffer_handle(frame, render_buffer_delete(device));
}

class render_target : private boost::noncopyable {
 public:
  render_target(device_handle &device, const int width, const int height) 
      : width_(width),
        height_(height),
        target_(create_texture(device, width, height)),
        render_buffer_(create_render_buffer(device, width, height)),
        frame_buffer_(create_frame_buffer(device)) {
     device.begin_scene();
     glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, *frame_buffer_);
     glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, *target_, 0);
     glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, *render_buffer_);
     glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
     device.end_scene();
   }

  int width() const {
    return width_;
  }

  int height() const {
    return height_;
  }

 private:
  void begin(device_handle &device) const {
    device.begin_scene();
    //glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, *frame_buffer_);
    glViewport(0, 0, width(), height());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.f, static_cast<float>(width()), static_cast<float>(height()), 0.f, 0.f, 1.f);
    device.end_scene();
  }
  
  const texture_handle &texture1() const {
    return target_;
  }

  const int width_;
  const int height_;
  const texture_handle target_;
  const render_buffer_handle render_buffer_;
  const frame_buffer_handle frame_buffer_;

  friend class scoped_render_target;
  friend class texture_core_access;
};

class scoped_render_target : private boost::noncopyable {
 public:
  scoped_render_target(device_handle &device, const render_target &target) : device_(device), viwe_port_(device) {
    target.begin(device);
  }
  
  ~scoped_render_target() {
    device_.begin_scene();
    //glFlush();
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
    device_.end_scene();
  }

 private:
  device_handle &device_;
  const scoped_viewport viwe_port_;
};
}}}

#endif

