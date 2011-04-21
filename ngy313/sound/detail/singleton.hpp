#ifndef NGY313_SOUND_DETAIL_SINGLETON_HPP_
#define NGY313_SOUND_DETAIL_SINGLETON_HPP_
#include <boost/noncopyable.hpp>

namespace ngy313 { namespace sound { namespace detail {
template <typename Device>
class singleton : private boost::noncopyable {
 public:
  static const singleton &instance() {
    static const singleton sound;
    return sound;
  }

  const sound_device &device() const {
    return device_;
  }

 private:
  singleton() : device_() {}

  const Device device_;
};
}}}

#endif
