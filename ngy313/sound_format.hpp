#ifndef NGY313_SOUND_FORMAT_HPP_
#define NGY313_SOUND_FORMAT_HPP_

#include <cstdint>
#include <tuple>
#include <vector>
#include <boost/config.hpp>
#include <boost/mpl/vector.hpp>

#if defined(_WIN32)
#include <Xaudio2.h>
#elif defined(__linux__)
#define WAVE_FORMAT_PCM  0
#endif

namespace ngy313 {
BOOST_CONSTEXPR_OR_CONST std::uint16_t kFormatPCM = WAVE_FORMAT_PCM;

struct buffer_format {
  std::uint16_t type;
  std::uint16_t channels;
  std::uint32_t samples_per_sec;
  std::uint32_t avg_bytes_per_sec;
  std::uint16_t block_align;
  std::uint16_t bits_per_sample;
};

typedef std::vector<std::uint8_t> buffer_container_type;

struct normal_play_tag;
struct streaming_play_tag;

template <typename PlayTag>
struct sound_loader_facade {
  typedef PlayTag play_type;
};

typedef boost::mpl::vector<normal_play_tag> normal_play_only_tag;
typedef boost::mpl::vector<streaming_play_tag> streaming_play_only_tag;
typedef boost::mpl::vector<normal_play_tag,
                           streaming_play_tag> normal_and_streaming_play_tag;

struct sound_buffer_base {
  virtual ~sound_buffer_base() {}
  virtual const buffer_container_type &buffer() const = 0;
  virtual const buffer_format &format() const = 0;
};
}

#endif
