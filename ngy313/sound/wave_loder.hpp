#pragma once
#include <ngy313/sound/detail/wave.hpp>

namespace ngy313 { namespace sound { namespace wave {
class loader {
 public:
  explicit loader(const std::string &file_name) : buffer_(file_name) {}

  buffer_container_type::const_iterator buffer() const {
    return buffer_.get().buffer().cbegin();
  }

  std::size_t size() const {
    return buffer_.get().buffer().size();
  }

  buffer_format format() const {
    return buffer_.get().format();
  }

 private:
  loader &operator =(const loader &);
  const detail::buffer_type buffer_;
};
}}}
