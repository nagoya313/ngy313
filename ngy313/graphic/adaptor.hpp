#pragma once
#include <functional>
#include <type_traits>
#include <boost/mpl/if.hpp>
#include <boost/mpl/inherit.hpp>
#include <boost/type_traits/function_traits.hpp>
#include <ngy313/graphic/drawable.hpp>
#include <ngy313/graphic/drawable_access.hpp>
#include <ngy313/graphic/texture.hpp>

namespace ngy313 { namespace graphic {
template <typename Signature>
struct copy_argument {
  typedef typename std::decay<typename boost::function_traits<Signature>::arg1_type>::type type;
};

class adaptor_access {
 private:
  template <typename Adaptor, typename Vertex>
  static void transform(const Adaptor &adaptor, Vertex &vertex) {
    adaptor.transform(vertex);
  }

  template <typename Adaptor, typename Drawable>
  friend struct drawable_adaptor;
};

struct empty {};

template <typename Adaptor, typename Drawable>
struct drawable_adaptor : public ngy313::graphic::copy_drawable<Drawable>::type,
                          public boost::mpl::if_<std::is_base_of<texture, Drawable>, texture, empty>::type {
  template <typename Draw>
  drawable_adaptor(const Draw &drawable,
                   typename std::enable_if<!std::is_base_of<texture, Draw>::value>::type * = nullptr)
      : drawable_(drawable) {}

  template <typename Draw>
  drawable_adaptor(const Draw &drawable,
                   typename std::enable_if<std::is_base_of<texture, Draw>::value>::type * = nullptr)
      : drawable_(drawable), texture(drawable) {}

 private:
  typename Drawable::vertex_array_type vertex() const {
    auto vertex = drawable_access::copy_vertex(drawable_);
    adaptor_access::transform(static_cast<const Adaptor &>(*this), vertex);
    return vertex;
  }

  const Drawable &drawable_;
  
  friend class drawable_access;
};

template <typename Drawable, typename AddType>
struct add_drawable_adaptor : public AddType::type,
                              public boost::mpl::if_<std::is_base_of<texture, Drawable>, texture, empty>::type {
  template <typename Draw>
  add_drawable_adaptor(const Draw &drawable,
                   typename std::enable_if<!std::is_base_of<texture, Draw>::value>::type * = nullptr)
      : drawable_(drawable) {}

  template <typename Draw>
  add_drawable_adaptor(const Draw &drawable,
                   typename std::enable_if<std::is_base_of<texture, Draw>::value>::type * = nullptr)
      : drawable_(drawable), texture(drawable) {}

 private:
  typename Drawable::vertex_array_type vertex() const {
    return drawable_access::copy_vertex(drawable_);
  }

  const Drawable &drawable_;

  friend class drawable_access;
};
}}
