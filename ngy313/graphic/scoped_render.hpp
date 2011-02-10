#pragma once
#include <boost/noncopyable.hpp>
#include <ngy313/graphic/detail/singleton.hpp>

namespace ngy313 { namespace graphic {
class scoped_render : private boost::noncopyable {
 public:
  scoped_render() : succeeded_(detail::begin_scene(detail::device())) {}
  
  ~scoped_render() {
    detail::end_scene(detail::device());
  }

  bool succeeded() const {
    return succeeded_;
  }

 private:
  const bool succeeded_;
};
}}
