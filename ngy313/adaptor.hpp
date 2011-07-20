#ifndef NGY313_ADAPTOR_HPP_
#define NGY313_ADAPTOR_HPP_

#include <type_traits>
#include <boost/mpl/insert.hpp>
#include <boost/fusion/include/at_key.hpp>
#include <ngy313/drawable_traits.hpp>

namespace ngy313 {
template <typename Adaptor, typename Drawable>
struct drawable_adaptor {
	typedef typename Drawable::list_type list_type;
	typedef typename Drawable::vertex_type vertex_type;
	typedef typename Drawable::vertex_array_type vertex_array_type;

  explicit drawable_adaptor(const Drawable &drawable)
      : list_(detail::drawable_fusion_initializer::init(drawable)) {}

  vertex_array_type vertex() const {
    auto vertex = boost::fusion::at_key<detail::drawable_key>(list_).vertex();
    static_cast<const Adaptor &>(*this).transform(vertex);
    return vertex;
  }

  const texture &texture1() const {
    return boost::fusion::at_key<detail::texture_data_key>(list_);
  }

 private:
  const typename detail::drawable_fusion<Drawable>::type list_;
};

template <typename Drawable, typename AddData>
struct add_drawable_adaptor {
	typedef typename boost::mpl::insert<typename Drawable::list_type,
		                                  AddData>::type list_type;
	typedef typename Drawable::vertex_type vertex_type;
	typedef typename Drawable::vertex_array_type vertex_array_type;

  explicit add_drawable_adaptor(const Drawable &drawable)
      : list_(detail::drawable_fusion_initializer::init(drawable)) {}

  vertex_array_type vertex() const {
    return boost::fusion::at_key<detail::drawable_key>(list_).vertex();
  }

  const texture &texture1() const {
    return boost::fusion::at_key<detail::texture_data_key>(list_);
  }

 private:
  const typename detail::drawable_fusion<Drawable>::type list_;
};
}

#endif
