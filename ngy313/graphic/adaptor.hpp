#pragma once
#include <type_traits>
#include <boost/fusion/include/map.hpp>
#include <boost/fusion/include/at_key.hpp>
#include <boost/fusion/include/size.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/same_as.hpp>
#include <boost/mpl/always.hpp>
#include <boost/mpl/switch.hpp>
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

template <typename Drawable>
struct drawable_switch_body {
  typedef boost::mpl::vector<
      boost::mpl::pair<boost::mpl::same_as<boost::mpl::void_>,
                       boost::mpl::always<
                           boost::fusion::map<boost::fusion::pair<detail::drawable_key, const Drawable &>>>>,
      boost::mpl::pair<boost::mpl::same_as<tex_t<1>>,
                       boost::mpl::always<
                           boost::fusion::map<boost::fusion::pair<detail::drawable_key, const Drawable &>,
                                              boost::fusion::pair<detail::texture_data_key, const texture &>>>>> type;
};

template <typename Drawable>
struct drawable_fusion {
  typedef typename boost::mpl::switch_<typename drawable_switch_body<Drawable>::type,
                                       typename drawable_switch_element<Drawable>::type>::type type;
};

template <typename Drawable>
struct drawable_switch {
  typedef boost::fusion::result_of::size<typename drawable_fusion<Drawable>::type> type;
};

template <typename Drawable>
typename drawable_fusion<Drawable>::type 
    drawable_fusion_init(const Drawable &drawable,
                         typename std::enable_if<drawable_switch<Drawable>::type::value == 1>::type * = nullptr) {
  return typename drawable_fusion<Drawable>::type(drawable);
}

template <typename Drawable>
typename drawable_fusion<Drawable>::type 
    drawable_fusion_init(const Drawable &drawable,
                         typename std::enable_if<drawable_switch<Drawable>::type::value == 2>::type * = nullptr) {
  return typename drawable_fusion<Drawable>::type(drawable, texture_access::texture1(drawable));
}

template <typename Adaptor, typename Drawable>
struct drawable_adaptor : public ngy313::graphic::copy_drawable<Drawable> {
  explicit drawable_adaptor(const Drawable &drawable) : list_(drawable_fusion_init(drawable)) {}

 private:
  typename Drawable::vertex_array_type vertex() const {
    auto vertex = drawable_access::copy_vertex(boost::fusion::at_key<detail::drawable_key>(list_));
    adaptor_access::transform(static_cast<const Adaptor &>(*this), vertex);
    return vertex;
  }

  const texture &texture1() const {
    return boost::fusion::at_key<detail::texture_data_key>(list_);
  }

  const typename drawable_fusion<Drawable>::type list_;
  
  friend class drawable_access;
  friend class texture_access;
};

template <typename Drawable, typename AddPair>
struct add_drawable_adaptor : public ngy313::graphic::add_drawable<Drawable, AddPair> {
  explicit add_drawable_adaptor(const Drawable &drawable) : list_(drawable_fusion_init(drawable)) {}

 private:
  typename Drawable::vertex_array_type vertex() const {
    return drawable_access::copy_vertex(boost::fusion::at_key<detail::drawable_key>(list_));
  }

  const texture &texture1() const {
    return boost::fusion::at_key<detail::texture_data_key>(list_);
  }

  const typename drawable_fusion<Drawable>::type list_;

  friend class drawable_access;
  friend class texture_access;
};
}}
