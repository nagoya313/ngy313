#ifndef NGY313_GRAPHIC_ADAPTOR_HPP_
#define NGY313_GRAPHIC_ADAPTOR_HPP_
#include <type_traits>
#include <boost/fusion/include/at_key.hpp>
#include <ngy313/graphic/detail/key.hpp>
#include <ngy313/graphic/drawable.hpp>
#include <ngy313/graphic/drawable_access.hpp>
#include <ngy313/graphic/texture.hpp>

namespace ngy313 { namespace graphic {
class adaptor_access {
 private:
  template <typename Adaptor, typename Vertex>
  static void transform(const Adaptor &adaptor, Vertex &vertex) {
    adaptor.transform(vertex);
  }

  template <typename Adaptor, typename Drawable>
  friend struct drawable_adaptor;
};


template <typename Adaptor, typename Drawable>
struct drawable_adaptor : public copy_drawable<Drawable> {
  explicit drawable_adaptor(const Drawable &drawable) : list_(detail::drawable_fusion_initializer::init(drawable)) {}

 private:
  typename Drawable::vertex_array_type vertex() const {
    auto vertex = drawable_access::copy_vertex(boost::fusion::at_key<detail::drawable_key>(list_));
    adaptor_access::transform(static_cast<const Adaptor &>(*this), vertex);
    return vertex;
  }

  const texture &texture1() const {
    return boost::fusion::at_key<detail::texture_data_key>(list_);
  }

  const typename detail::drawable_fusion<Drawable>::type list_;
  
  friend class drawable_access;
  friend class texture_access;
};

template <typename Drawable, typename AddPair>
struct add_drawable_adaptor : public add_drawable<Drawable, AddPair> {
  explicit add_drawable_adaptor(const Drawable &drawable) : list_(detail::drawable_fusion_initializer::init(drawable)) {}

 private:
  typename Drawable::vertex_array_type vertex() const {
    return drawable_access::copy_vertex(boost::fusion::at_key<detail::drawable_key>(list_));
  }

  const texture &texture1() const {
    return boost::fusion::at_key<detail::texture_data_key>(list_);
  }

  const typename detail::drawable_fusion<Drawable>::type list_;

  friend class drawable_access;
  friend class texture_access;
};
}}

#endif
