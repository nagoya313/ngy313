#ifndef NGY313_GRAPHIC_DETAIL_LINUX_SCOPED_ENABLE_HPP_
#define NGY313_GRAPHIC_DETAIL_LINUX_SCOPED_ENABLE_HPP_
#include <cstdint>
#include <type_traits>
#include <GL/gl.h>
#include <ngy313/graphic/detail/key.hpp>
#include <ngy313/graphic/detail/linux/texture.hpp>
#include <ngy313/graphic/detail/linux/scoped_enable.hpp>
#include <ngy313/graphic/drawable_access.hpp>
#include <ngy313/graphic/fvf_traits.hpp>

namespace ngy313 { namespace graphic { namespace detail {
struct scoped_vertex_enable {
  template <typename Vertex>
  explicit scoped_vertex_enable(const Vertex &vertex) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, sizeof(vertex.front()), &vertex_member_at<position>(vertex[0]).x);
  }
  
  ~scoped_vertex_enable() {
    glDisableClientState(GL_VERTEX_ARRAY);
  }
};

template <std::uint32_t FVF, typename T = void>
struct scoped_color_enable : public scoped_vertex_enable {
  template <typename Vertex>
  explicit scoped_color_enable(const Vertex &vertex) : scoped_color_enable::scoped_vertex_enable(vertex) {}
};

template <std::uint32_t FVF>
struct scoped_color_enable<FVF, typename std::enable_if<FVF & 0x02>::type>
     : public scoped_vertex_enable {
  template <typename Vertex>
  explicit scoped_color_enable(const Vertex &vertex) : scoped_color_enable::scoped_vertex_enable(vertex) {
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(4, GL_FLOAT, sizeof(vertex.front()), &vertex_member_at<diffuse>(vertex[0]).r);
  }
  
  ~scoped_color_enable() {
    glDisableClientState(GL_COLOR_ARRAY);
  }
};

template <std::uint32_t FVF, typename T = void>
struct scoped_texture_1_enable : public scoped_color_enable<FVF> {
  template <typename Vertex>
  explicit scoped_texture_1_enable(const Vertex &vertex) : scoped_texture_1_enable::scoped_color_enable(vertex) {}
};

template <std::uint32_t FVF>
struct scoped_texture_1_enable<FVF, typename std::enable_if<FVF & 0x08>::type>
    : public scoped_color_enable<FVF - 0x08> {
  template <typename Vertex>
  explicit scoped_texture_1_enable(const Vertex &vertex) : scoped_texture_1_enable::scoped_color_enable(vertex) {
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, sizeof(vertex.front()), &vertex_member_at<tex>(vertex[0]).tex_array[0].u);
  }
  
  ~scoped_texture_1_enable() {
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  }
};

template <std::uint32_t FVF>
struct scoped_list : public scoped_texture_1_enable<FVF> {
  template <typename Vertex>
  explicit scoped_list(const Vertex &vertex) : scoped_list::scoped_texture_1_enable(vertex) {}
  
};
}}}

#endif

