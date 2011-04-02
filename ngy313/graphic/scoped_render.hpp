#ifndef NGY313_GRAPHIC_SCOPED_RENDER_HPP_
#define NGY313_GRAPHIC_SCOPED_RENDER_HPP_
#include <boost/noncopyable.hpp>
#include <ngy313/graphic/detail/graphic.hpp>

namespace ngy313 { namespace graphic {
class scoped_render : private boost::noncopyable {
 public:
  scoped_render() : succeeded_(detail::device().begin_scene()) {}
  
  ~scoped_render() {
    detail::device().end_scene();
  }

  bool succeeded() const {
    return succeeded_;
  }

 private:
  const bool succeeded_;
};
}}

#endif

