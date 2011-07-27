#ifndef NGY313_ADAPTOR_HPP_
#define NGY313_ADAPTOR_HPP_

#include <boost/mpl/insert.hpp>

namespace ngy313 {
template <typename Adaptor, typename Drawable>
struct drawable_adaptor {
  typedef typename Drawable::list_type list_type;
  typedef typename Drawable::vertex_type vertex_type;
  typedef typename Drawable::vertex_array_type vertex_array_type;

  explicit drawable_adaptor(const Drawable &drawable)
      : drawable_(drawable) {}

  vertex_array_type vertex() const {
    auto vertex = drawable_.vertex();
    static_cast<const Adaptor &>(*this).transform(vertex);
    return vertex;
  }

  const texture &texture1() const {
    return drawable_.texture1();
  }

 private:
  const Drawable &drawable_;
};

template <typename AddData, typename Drawable>
struct add_drawable_adaptor {
  typedef typename boost::mpl::insert<typename Drawable::list_type,
		                              AddData>::type list_type;
  typedef typename Drawable::vertex_type vertex_type;
  typedef typename Drawable::vertex_array_type vertex_array_type;

  explicit add_drawable_adaptor(const Drawable &drawable)
      : drawable_(drawable) {}

  vertex_array_type vertex() const {
    return drawable_.vertex();
  }

  const texture &texture1() const {
    return drawable_.texture1();
  }

 private:
  const Drawable &drawable_;
};
}

#endif
