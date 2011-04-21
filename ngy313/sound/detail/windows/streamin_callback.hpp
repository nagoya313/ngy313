#ifndef NGY313_SOUND_DETAIL_WINDOWS_STREAMING_CALLBACK_HPP_
#define NGY313_SOUND_DETAIL_WINDOWS_STREAMING_CALLBACK_HPP_
#include <stdexcept>
#include <boost/noncopyable.hpp>
#include <XAudio2.h>

namespace ngy313 { namespace sound { namespace detail {
template <typename StreamingSound>
class streaming_callback : private IXAudio2VoiceCallback, private boost::noncopyable {
 public:
  explicit streaming_callback(StreamingSound &sound) : sound_(sound) {}

 private:
  void WINAPI OnStreamEnd() {}

  void WINAPI OnVoiceProcessingPassEnd() {}

  void WINAPI OnVoiceProcessingPassStart(UINT32) {}

  void WINAPI OnBufferEnd(void *) {
    sound_.buffer_end();
  }

  void WINAPI OnBufferStart(void *) {
    sound_.buffer_start();
  }

  void WINAPI OnLoopEnd(void *) {}

  void WINAPI OnVoiceError(void *, HRESULT) {
    throw std::runtime_error("ストリーミング再生中にエラーが発生しました");
  }

  StreamingSound &sound_;

  friend StreamingSound;
};
}}}

#endif
