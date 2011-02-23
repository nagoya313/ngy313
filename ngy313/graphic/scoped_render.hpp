#pragma once
#include <boost/noncopyable.hpp>
#include <ngy313/graphic/detail/singleton.hpp>

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
