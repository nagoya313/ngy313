#ifndef NGY313_GRAPHIC_SHAPE_POSITION_HPP_
#define NGY313_GRAPHIC_SHAPE_POSITION_HPP_
#include <boost/mpl/at.hpp>
#include <boost/range/numeric.hpp>
#include <ngy313/graphic/detail/key.hpp>
#include <ngy313/graphic/detail/add_position.hpp>
#include <ngy313/graphic/drawable_access.hpp>
#include <ngy313/graphic/fvf_traits.hpp>
#include <ngy313/graphic/vertex_member.hpp>

namespace ngy313 { namespace graphic {
struct shape_position {
  template <typename Drawable>
  static float x(const Drawable &drawable, const std::size_t at) {
    return vertex_member_at<position>(drawable_access::copy_vertex(drawable)[at]).x;
  }

  template <typename Drawable>
  static float y(const Drawable &drawable, const std::size_t at) {
    return vertex_member_at<position>(drawable_access::copy_vertex(drawable)[at]).y;
  }

  template <typename Drawable, std::size_t Index>
  static float u(const Drawable &drawable, const std::size_t at) {
    return vertex_member_at<tex>(drawable_access::copy_vertex(drawable)[at]).tex_array[Index].u;
  }

  template <typename Drawable, std::size_t Index>
  static float v(const Drawable &drawable, const std::size_t at) {
    return vertex_member_at<tex>(drawable_access::copy_vertex(drawable)[at]).tex_array[Index].v;
  }
};

struct shape_center {
  template <typename Drawable>
  static float x(const Drawable &drawable) {
    return boost::accumulate(drawable_access::copy_vertex(drawable), 0.f, detail::add_position_x) / 
         static_cast<float>(boost::mpl::at<typename Drawable::list_type, detail::size_key>::type::type::value);
  }

  template <typename Drawable>
  static float y(const Drawable &drawable) {
    return boost::accumulate(drawable_access::copy_vertex(drawable), 0.f, detail::add_position_y) / 
         static_cast<float>(boost::mpl::at<typename Drawable::list_type, detail::size_key>::type::type::value);
  }

  template <typename Drawable, std::size_t Index>
  static float u(const Drawable &drawable) {
    return boost::accumulate(drawable_access::copy_vertex(drawable), 0.f, detail::add_position_u_t<Index>()) / 
         static_cast<float>(boost::mpl::at<typename Drawable::list_type, detail::size_key>::type::type::value);
  }

  template <typename Drawable, std::size_t Index>
  static float v(const Drawable &drawable) {
    return boost::accumulate(drawable_access::copy_vertex(drawable), 0.f, detail::add_position_v_t<Index>()) / 
         static_cast<float>(boost::mpl::at<typename Drawable::list_type, detail::size_key>::type::type::value);
  }
};
}}

#endif
