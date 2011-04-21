#ifndef NGY313_GRAPHIC_DRAWABLE_ACCESS_HPP_
#define NGY313_GRAPHIC_DRAWABLE_ACCESS_HPP_

// これが必要な意味がよく分からないが名前空間があると必要？
namespace ngy313 { namespace graphic { namespace detail {
template <typename Drawable>
class draw; 
}}}

namespace ngy313 { namespace graphic {
class drawable_access {
 private:
  template <typename Drawable>
  static typename Drawable::vertex_array_type copy_vertex(const Drawable &drawable) {
    return drawable.vertex();
  }

  template <typename Drawable>
  friend class detail::draw;

  template <typename Adaptor, typename Drawable>
  friend struct drawable_adaptor;

  template <typename Drawable, typename AddType>
  friend struct add_drawable_adaptor;

  friend struct shape_position ;
  friend struct shape_center;
};
}}

#endif
