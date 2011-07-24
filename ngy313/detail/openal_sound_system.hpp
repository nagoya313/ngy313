#ifndef NGY313_DETAIL_OPENAL_SOUND_SYSTEM_HPP_
#define NGY313_DETAIL_OPENAL_SOUND_SYSTEM_HPP_

#include <cassert>
#include <memory>
#include <stdexcept>
#include <boost/noncopyable.hpp>
#include <AL/al.h>
#include <AL/alc.h>

namespace ngy313 { namespace detail {
class openal_sound_system : boost::noncopyable {
  struct device_delete {
    void operator ()(ALCdevice *device) const {
      assert(device);
      alcCloseDevice(device);
    }
  };

  typedef std::unique_ptr<ALCdevice, device_delete> device_handle;

  struct context_delete {
    void operator ()(ALCcontext *context) const {
      assert(context);
      alcMakeContextCurrent(nullptr);
      alcDestroyContext(context);
    }
  };

  typedef std::unique_ptr<ALCcontext, context_delete> context_handle;

 public:
  openal_sound_system() : device_(create_device()),
                          context_(create_context(device_)) {
    alcMakeContextCurrent(context_.get());
  }

 private:
  static device_handle create_device() {
    ALCdevice * const device = alcOpenDevice(nullptr);
    if (!device) {
      throw std::runtime_error("サウンドデバイスの初期化に失敗しました");
    }
    return device_handle(device);
  }

  static context_handle create_context(const device_handle &device) {
    ALCcontext * const context = alcCreateContext(device.get(),
                                                        nullptr);
    if (!context) {
      throw std::runtime_error("コンテクストの生成に失敗しました");
    }
    return context_handle(context);
  }

  const device_handle device_;
  const context_handle context_;
};
}}

#endif
