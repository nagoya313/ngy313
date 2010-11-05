#pragma once
#include <cstdint>
#include <boost/noncopyable.hpp>
#include "detail/window_singleton.hpp"

namespace ngy313 {
class scoped_render : private boost::noncopyable {
 public:
  scoped_render() : succeeded_(detail::begin_scene(detail::graphic_device())) {}
  
  ~scoped_render() {
    detail::end_scene(detail::graphic_device());
  }

  bool succeeded() const {
    return succeeded_;
  }

 private:
  const bool succeeded_;
};

inline
void clear(const std::uint32_t &col) {
  detail::clear(detail::graphic_device(), col);
}

inline
void present() {
  detail::present(detail::window(), detail::graphic_device(), true);
}

template <typename Drawable>
void draw(const Drawable &drawable) {
  detail::draw(detail::graphic_device(), drawable);
}
}