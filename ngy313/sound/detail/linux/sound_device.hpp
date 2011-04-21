#ifndef NGY313_SOUND_DETAIL_LINUX_SOUND_DEVICE_HPP_
#define NGY313_SOUND_DETAIL_LINUX_SOUND_DEVICE_HPP_
#include <cassert>
#include <memory>
#include <stdexcept>
#include <boost/noncopyable.hpp>
#include <AL/al.h>
#include <AL/alc.h>

namespace ngy313 { namespace sound { namespace detail {
struct device_delete {
  void operator ()(ALCdevice * const device) const {
    assert(device);
    alcCloseDevice(device);
  }
};

struct context_delete {
  void operator ()(ALCcontext * const context) const {
    assert(context);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(context);
  }
};

class sound_device : private boost::noncopyable {
 public:
  sound_device() : device_(alcOpenDevice(NULL)), context_(alcCreateContext(device_.get(), NULL)) {
    if (!device_) {
      throw std::runtime_error("サウンドデバイスの初期化に失敗しました");
    }
    if (!context_) {
      throw std::runtime_error("コンテクストの生成に失敗しました");
    }
    alcMakeContextCurrent(context_.get());
  }
  
  int device() const {
    return 0;
  }
  
 private:
  std::unique_ptr<ALCdevice, device_delete> device_;
  std::unique_ptr<ALCcontext, context_delete> context_;
};
}}}

#endif
