#ifndef NGY313_DETAIL_GRAPHIC_HPP_
#define NGY313_DETAIL_GRAPHIC_HPP_

#include <cassert>
#include <cstdint>
#include <boost/noncopyable.hpp>
#include <boost/signals2.hpp>
#include <ngy313/fwd.hpp>
#include <ngy313/detail/drawable_traits_key.hpp>

#if defined(_WIN32)
#include <ngy313/detail/direct3d9_graphic_system.hpp>
#elif defined(__linux__)
#include <ngy313/detail/gtkglextmm_graphic_system.hpp>
#endif

namespace ngy313 { namespace detail {
template <typename Graphic>
class scoped_render : boost::noncopyable {
 public:
  explicit scoped_render(Graphic &graphic) : render_(graphic) {}

  bool succeeded() const {
    return render_.succeeded();
  }

 private:
  const typename Graphic::scoped_render render_;
};

template <typename Device, typename Drawable, typename T = void>
class enable_texture {
 public:
  explicit enable_texture(const Device &, const Drawable &) {}
};

template <typename Device, typename Drawable>
class enable_texture<
          Device,
          Drawable,
          typename std::enable_if<
              std::is_same<texture_t<1>,
              typename drawable_switch_element<Drawable>::type>::value>::type>
    : boost::noncopyable {
 public:
  explicit enable_texture(Device &device, const Drawable &drawable)
      :device_(device) {
    device_.set_texture(drawable);
  }

  ~enable_texture() {
    device_.unset_texture();
  }

 private:
  Device &device_;
};

template <typename Graphic>
class basic_graphic_system : boost::noncopyable {
 public:
	typedef typename Graphic::scoped_render scoped_render;

  template <typename Window>
  explicit basic_graphic_system(const Window &window)
      : graphic_(window) {}

  void resize(int width_size, int height_size) {
    graphic_.resize(width_size, height_size);
    assert(width_size == width() && height_size == height());
  }

  int width() const {
    return graphic_.width();
  }

  int height() const {
    return graphic_.height();
  }

  void present() {
    graphic_.present();
  }

  bool begin_scene() {
    return graphic_.begin_scene();
  }

  void end_scene() {
    graphic_.end_scene();
  }

  template <typename Wrap>
  void clear_screen(const basic_color_wrap<Wrap> &color) {
    graphic_.clear_screen(color);
  }

  std::uint32_t pixel_color(int x, int y) const {
    return graphic_.pixel_color(x, y);
  }

  template <typename Drawable>
  void draw(Drawable &&drawable) {
  	const detail::enable_texture<Graphic,
  	                             Drawable> tex(graphic_, drawable);
    graphic_.draw_primitive(std::forward<Drawable>(drawable));
  }

  template <typename Drawable>
  void set_texture(const Drawable &drawable) {
  	graphic_.set_texture(drawable);
  }

  void unset_texture() {
    graphic_.unset_texture();
  }

  typename Graphic::handle_type handle() const {
    return graphic_.handle();
  }

  boost::signals2::signal<void ()> &before_reset() {
  	return graphic_.before_reset();
  }

  boost::signals2::signal<void ()> &after_reset() {
    return graphic_.after_reset();
  }

 private:
  Graphic graphic_;
};

#if defined(_WIN32)
typedef basic_graphic_system<direct3d9_graphic_system> graphic_system; 
#elif defined(__linux__)
typedef basic_graphic_system<gtkglextmm_graphic_system> graphic_system;
#endif
}}

#endif
