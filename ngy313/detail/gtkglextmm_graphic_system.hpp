#ifndef NGY313_DETAIL_GTKGLEXTMM_GRAPHIC_SYSTEM_HPP_
#define NGY313_DETAIL_GTKGLEXTMM_GRAPHIC_SYSTEM_HPP_

#include <cassert>
#include <cstdint>
#include <memory>
#include <stdexcept>
#include <thread>
#include <type_traits>
#include <boost/mpl/at.hpp>
#include <boost/noncopyable.hpp>
#include <boost/signals2.hpp>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <gtkglmm.h>
#include <ngy313/fwd.hpp>
#include <ngy313/fvf_traits.hpp>
#include <ngy313/vertex_member.hpp>
#include <ngy313/detail/fwd.hpp>
#include <ngy313/detail/drawable_traits_key.hpp>

namespace ngy313 { namespace detail {
class gtkglextmm_graphic_system : boost::noncopyable {
  class system_impl;
  
 public:
  typedef const std::unique_ptr<system_impl> &handle_type;
  
  class scoped_render : boost::noncopyable {
   public:
    template <typename Graphic>
    explicit scoped_render(const basic_graphic_system<Graphic> &system)
        : gl_window_(system.handle()->realized() ?
                     system.handle()->get_gl_window() :
                     Glib::RefPtr<Gdk::GL::Window>()),
          succeeded_(begin_scene(*system.handle())) {}

    ~scoped_render() {
      if (succeeded()) {
      	end_scene();
      }
    }

    bool succeeded() const {
      return succeeded_;
    }

   private:
    bool begin_scene(Gtk::GL::DrawingArea &area) {
      return gl_window_ ? gl_window_->gl_begin(area.get_gl_context()) : false;
    }

    void end_scene() {
      assert(gl_window_);
      gl_window_->gl_end();
    }
    
    Glib::RefPtr<Gdk::GL::Window> gl_window_;
    bool succeeded_;
  };

  class enable_texture : boost::noncopyable {
   public:
    template <typename Drawable>
    explicit enable_texture(gtkglextmm_graphic_system &device,
                            const Drawable &drawable) {
      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, *drawable.texture1().handle().get());
    }

    ~enable_texture() {
      glDisable(GL_TEXTURE_2D);
    }
  };

  class scoped_blend : boost::noncopyable {
   public:
    template <typename BlendPair>
    explicit scoped_blend(gtkglextmm_graphic_system &device, BlendPair &&)
        : enable_alpha_(glIsEnabled(GL_BLEND)),
          src_blend_(get_src_blend_mode()),
          dest_blend_(get_dest_blend_mode()) {
      glEnable(GL_BLEND);
      set_blend_pair<BlendPair>();
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	  glEnable(GL_BLEND);
    }

    ~scoped_blend() {
      set_blend_mode(src_blend_, dest_blend_);
      glDisable(GL_BLEND);
    }

   private:
    static void set_blend_mode(GLenum src, GLenum dest) {
      glBlendFunc(src, dest);
    }

    template <typename BlendPair>
    static void set_blend_pair() {
      set_blend_mode(BlendPair::src_type::value, BlendPair::dest_type::value);
    }

    static GLenum get_src_blend_mode() {
      GLint temp;
      glGetIntegerv(GL_BLEND_SRC, &temp);
      return static_cast<GLenum>(temp);
    }

    static GLenum get_dest_blend_mode() {
      GLint temp;
      glGetIntegerv(GL_BLEND_DST, &temp);
      return static_cast<GLenum>(temp);
    }

    bool enable_alpha_;
    GLenum src_blend_;
    GLenum dest_blend_;
  };

  template <typename Window>
  explicit gtkglextmm_graphic_system(const basic_window<Window> &window)
      : graphic_(new system_impl(window)) {}

  void resize(int width, int height) {
    graphic_->resize(width, height);
    assert(width == this->width() && height == this->height());
  }

  int width() const {
    return graphic_->width();
  }

  int height() const {
    return graphic_->height();
  }

  void present() {
    graphic_->present();
  }

  template <typename Wrap>
  void clear_screen(const basic_color_wrap<Wrap> &color) {
    graphic_->clear(color);
  }

  std::uint32_t pixel_color(int x, int y) const {
    return graphic_->pixel_color(x, y);
  }

  template <typename Drawable, 
            typename List = typename std::decay<Drawable>::type::list_type>
  void draw_primitive(Drawable &&drawable) {
    const auto vertex = drawable.vertex();
    const scoped_list<
        fvf_traits<
            typename boost::mpl::at<
                List,
                fvf_key>::type>::fvf_type::value> list(vertex);
    glDrawArrays(boost::mpl::at<List, primitive_key>::type::type::value,
                 0,
                 boost::mpl::at<List, size_key>::type::type::value);
  }

  const handle_type &handle() const {
    return graphic_;
  }

  boost::signals2::signal<void ()> &before_reset() {
    return graphic_->before_reset();
  }

  boost::signals2::signal<void ()> &after_reset() {
    return graphic_->after_reset();
  }

 private:
  class system_impl : public Gtk::GL::DrawingArea,
                      boost::noncopyable {
   public:
    template <typename Window>
    explicit system_impl(const basic_window<Window> &window) 
        : width_(window.width()),
          height_(window.height()),
          realized_(false) {
	  static std::once_flag flag_;
      std::call_once(flag_, [] {Gtk::GL::init(0, 0);});
      const Glib::RefPtr<Gdk::GL::Config> gl_config
          = Gdk::GL::Config::create(
                Gdk::GL::MODE_RGB
                    | Gdk::GL::MODE_DEPTH
                        | Gdk::GL::MODE_DOUBLE);
      if (!gl_config) {
        throw std::runtime_error("OpenGLの初期化に失敗しました");
      }
      set_gl_capability(gl_config);
      window.handle()->add(*this);
      window.handle()->show_all_children();
    }

    template <typename Wrap>
    void clear(const basic_color_wrap<Wrap> &color) {
      glClearColor(color.get_blue_float(),
                   color.get_green_float(),
                   color.get_red_float(),
                   color.get_alpha_float());
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    std::uint32_t pixel_color(int x, int y) const {
      return 0;
    }
    
    void present() {
      scoped_gl gl(*this);
      gl.swap_buffers();
    }

    void resize(int width, int height) {
      width_ = width;
      height_ = height;
      glViewport(0, 0, width_, height_);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(0.f,
              static_cast<float>(width_),
              static_cast<float>(height_),
              0.f, 
              0.f,
              1.f);
      assert(width == this->width() && height == this->height());
    }

    int width() const {
      return width_;
    }

    int height() const {
      return height_;
    }

    bool realized() const {
    	return realized_;
    }

    boost::signals2::signal<void ()> &before_reset() {
      return before_reset_;
    }

    boost::signals2::signal<void ()> &after_reset() {
      return after_reset_;
    }

   protected:
    virtual bool on_configure_event(GdkEventConfigure *event) {
      const scoped_gl gl(*this);
      glViewport(0, 0, width_, height_);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(0.f,
              static_cast<float>(width_),
              static_cast<float>(height_),
              0.f, 
              0.f,
              1.f);
      return true;
    }

    virtual void on_realize() {
      Gtk::DrawingArea::on_realize();
      after_reset_();
      realized_ = true;
    }
  
    virtual bool on_expose_event(GdkEventExpose *event) {
      scoped_gl gl(*this);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      gl.swap_buffers();
      return true;
    }

   private:
    int width_;
    int height_;
    bool realized_;
    boost::signals2::signal<void ()> before_reset_;
    boost::signals2::signal<void ()> after_reset_;
  };
  
  class scoped_gl : boost::noncopyable {
   public:
    explicit scoped_gl(Gtk::GL::DrawingArea &area) 
        : gl_window_(area.get_gl_window()) {
      assert(gl_window_);
      gl_window_->gl_begin(area.get_gl_context());
    }
    
    ~scoped_gl() {
      assert(gl_window_);
      gl_window_->gl_end();
    }

    void swap_buffers() {
      assert(gl_window_);
      gl_window_->swap_buffers();
    }

   private:
    Glib::RefPtr<Gdk::GL::Window> gl_window_;
  };
  
  struct scoped_vertex_enable {
    template <typename Vertex>
    explicit scoped_vertex_enable(const Vertex &vertex) {
      glEnableClientState(GL_VERTEX_ARRAY);
      glVertexPointer(3,
    		          GL_FLOAT,
    		          sizeof(vertex.front()),
                      &vertex_member_at<position_member>(vertex[0]).x_);
    }

    ~scoped_vertex_enable() {
      glDisableClientState(GL_VERTEX_ARRAY);
    }
  };

  template <std::uint32_t FVF, typename T = void>
  struct scoped_color_enable : private scoped_vertex_enable {
    template <typename Vertex>
    explicit scoped_color_enable(const Vertex &vertex)
        : scoped_vertex_enable(vertex) {}
  };

  template <std::uint32_t FVF>
  struct scoped_color_enable<FVF, typename std::enable_if<FVF & 0x02>::type>
     : private scoped_vertex_enable {
    template <typename Vertex>
    explicit scoped_color_enable(const Vertex &vertex)
        : scoped_vertex_enable(vertex) {
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(4,
                     GL_FLOAT,
                     sizeof(vertex.front()),
    		         &vertex_member_at<diffuse_member>(vertex[0]).r_);
    }

    ~scoped_color_enable() {
      glDisableClientState(GL_COLOR_ARRAY);
    }
  };


  template <std::uint32_t FVF, typename T = void>
  struct scoped_texture_1_enable : private scoped_color_enable<FVF> {
    template <typename Vertex>
    explicit scoped_texture_1_enable(const Vertex &vertex)
        : scoped_texture_1_enable::scoped_color_enable(vertex) {}
  };

  template <std::uint32_t FVF>
  struct scoped_texture_1_enable<FVF,
                                 typename std::enable_if<FVF & 0x08>::type>
      : private scoped_color_enable<FVF - 0x08> {
    template <typename Vertex>
    explicit scoped_texture_1_enable(const Vertex &vertex)
        : scoped_texture_1_enable::scoped_color_enable(vertex) {
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      glTexCoordPointer(2,
    		            GL_FLOAT,
    		            sizeof(vertex.front()),
    	  	            &vertex_member_at<texture_member>(
                            vertex[0]).texture_array[0].u);
    }

    ~scoped_texture_1_enable() {
      glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }
  };

  template <std::uint32_t FVF>
  struct scoped_list : private scoped_texture_1_enable<FVF> {
    template <typename Vertex>
    explicit scoped_list(const Vertex &vertex)
        : scoped_list::scoped_texture_1_enable(vertex) {}
  };

  std::unique_ptr<system_impl> graphic_;
};
}}

#endif
