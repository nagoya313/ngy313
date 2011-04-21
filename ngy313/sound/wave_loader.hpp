#ifndef NGY313_SOUND_WAVE_LOADER_HPP_
#define NGY313_SOUND_WAVE_LOADER_HPP_
#include <boost/noncopyable.hpp>
#include <ngy313/sound/detail/wave.hpp>

namespace ngy313 { namespace sound { namespace wave {
class loader : private boost::noncopyable {
 public:
  explicit loader(const std::string &file_name) : buffer_(file_name) {}

  buffer_container_type::const_iterator buffer() const {
    return buffer_.buffer().cbegin();
  }

  std::size_t size() const {
    return buffer_.buffer().size();
  }

  buffer_format format() const {
    return buffer_.format();
  }

 private:
  const detail::buffer_type buffer_;
};
}}}

#endif
