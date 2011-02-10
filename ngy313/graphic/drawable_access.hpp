#pragma once

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

  template <typename Positon>
  friend struct shape_position ;

  template <typename Drawable>
  friend float shape_position_at_x(const Drawable &drawable, const std::size_t at);

  template <typename Drawable>
  friend float shape_position_at_y(const Drawable &drawable, const std::size_t at);

  template <typename Drawable>
  friend float shape_center_x(const Drawable &drawable);

  template <typename Drawable>
  friend float shape_center_y(const Drawable &drawable);
};
}}