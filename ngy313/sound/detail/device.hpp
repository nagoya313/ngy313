#pragma once
#include <cassert>
#include <cstdint>
#include <stdexcept>
#include <ngy313/sound/detail/fwd.hpp>
#include <ngy313/sound/detail/voice_delete.hpp>
#include <ngy313/sound/format.hpp>
#include <ngy313/utility/com_delete.hpp>

namespace ngy313 { namespace sound { namespace detail {
inline
device_handle create_device() {
#ifdef NDEBUG
  const std::uint32_t flag = 0;
#else
  const std::uint32_t flag = XAUDIO2_DEBUG_ENGINE;
#endif
  IXAudio2 *xaudio;
  if (FAILED(XAudio2Create(&xaudio, flag))) {
    throw std::runtime_error("XAudio2の初期化に失敗しました");
  }
  return device_handle(xaudio);
}

inline
master_voice_handle create_master_voice(const device_handle &xaudio) {
  assert(xaudio);
  IXAudio2MasteringVoice *mastering_voice;
  if (FAILED(xaudio->CreateMasteringVoice(&mastering_voice))) {
    throw std::runtime_error("マスターボイスの作成に失敗しました");
  }
  return master_voice_handle(mastering_voice);
}

inline
submix_voice_handle create_submix_voice(const device_handle &xaudio,
                                        const std::uint32_t channels,
                                        const std::uint32_t sample_rate) {
  assert(xaudio);
  IXAudio2SubmixVoice *submix_voice;
  if (FAILED(xaudio->CreateSubmixVoice(&submix_voice, channels, sample_rate, XAUDIO2_VOICE_USEFILTER))) {
    throw std::runtime_error("サブミックスボイスの作成に失敗しました");
  }
  return submix_voice_handle(submix_voice);
}

inline
WAVEFORMATEX transform_format(const buffer_format &format) {
  const WAVEFORMATEX format_ex = {
    format.type, 
    format.channels,
    format.samples_per_sec,
    format.avg_bytes_per_sec,
    format.block_align,
    format.bits_per_sample,
    0
  };
  return format_ex;
}

inline
source_voice_handle create_source_voice(const device_handle &xaudio, const buffer_format &format) {
  assert(xaudio);
  IXAudio2SourceVoice *voice;
  // ここの冗長性をどうするか
  const WAVEFORMATEX format_ex = transform_format(format);
  if (FAILED(xaudio->CreateSourceVoice(&voice, &format_ex))) {
    throw std::runtime_error("ソースボイスの作成に失敗しました");
  }
  return source_voice_handle(voice);
}

inline
source_voice_handle create_source_voice(const device_handle &xaudio, 
                                        const buffer_format &format,
                                        const streaming_callback callback) {
  assert(xaudio);
  IXAudio2SourceVoice *voice;
  const WAVEFORMATEX format_ex = transform_format(format);
  if (FAILED(xaudio->CreateSourceVoice(&voice, &format_ex, 0, XAUDIO2_DEFAULT_FREQ_RATIO, callback))) {
    throw std::runtime_error("ソースボイスの作成に失敗しました");
  }
  return source_voice_handle(voice);
}

inline
source_voice_handle create_source_voice(const device_handle &xaudio, 
                                        const buffer_format &format,
                                        const submix_voice_handle &submix) {
  assert(xaudio);
  IXAudio2SourceVoice *voice;
  // ここの冗長性をどうするか
  const WAVEFORMATEX format_ex = transform_format(format);
  XAUDIO2_SEND_DESCRIPTOR send = {
    XAUDIO2_SEND_USEFILTER, submix.get()
  };
  const XAUDIO2_VOICE_SENDS list = {
    1, &send
  };
  if (FAILED(xaudio->CreateSourceVoice(&voice, &format_ex, 0, XAUDIO2_DEFAULT_FREQ_RATIO, nullptr, &list))) {
    throw std::runtime_error("ソースボイスの作成に失敗しました");
  }
  return source_voice_handle(voice);
}

inline
source_voice_handle create_source_voice(const device_handle &xaudio, 
                                        const buffer_format &format,
                                        const submix_voice_handle &submix,
                                        const streaming_callback callback) {
  assert(xaudio);
  IXAudio2SourceVoice *voice;
  // ここの冗長性をどうするか
  const WAVEFORMATEX format_ex = transform_format(format);
  XAUDIO2_SEND_DESCRIPTOR send = {
    XAUDIO2_SEND_USEFILTER, submix.get()
  };
  const XAUDIO2_VOICE_SENDS list = {
    1, &send
  };
  if (FAILED(xaudio->CreateSourceVoice(&voice, &format_ex, 0, XAUDIO2_DEFAULT_FREQ_RATIO, callback, &list))) {
    throw std::runtime_error("ソースボイスの作成に失敗しました");
  }
  return source_voice_handle(voice);
}
}}}
