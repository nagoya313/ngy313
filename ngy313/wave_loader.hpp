#ifndef NGY313_WAVE_LOADER_HPP_
#define NGY313_WAVE_LOADER_HPP_

#include <fstream>
#include <memory>
#include <type_traits>
#include <ngy313/sound_format.hpp>
#include <ngy313/string_wrap.hpp>

namespace ngy313 {
template <typename T, typename Stream>
typename std::remove_const<T>::type read(Stream &stream) {
  typename std::remove_const<T>::type t;
  stream.read(reinterpret_cast<char *>(&t), sizeof(t));
  return t;
}

inline
sound_tuple create_buffer(const string_wrap &file_name) {
  std::ifstream fin(file_name.c_str(), std::ios::in | std::ios::binary);
  if (!fin) {
    throw std::runtime_error("ファイルを開くのに失敗しました");
  }
  if (read<std::uint32_t>(fin) != *reinterpret_cast<const std::uint32_t *>("RIFF")) {
    throw std::runtime_error("RIFFチャンクが存在しません");
  }
  fin.ignore(4);
  if (read<std::uint32_t>(fin) != *reinterpret_cast<const std::uint32_t *>("WAVE")) {
	  throw std::runtime_error("WAVEチャンクが存在しません");
  }
  if (read<std::uint32_t>(fin) != *reinterpret_cast<const std::uint32_t *>("fmt ")) {
	  throw std::runtime_error("fmt チャンクが存在しません");
  } 
  const std::uint32_t format_size = read<decltype(format_size)>(fin);
  const buffer_format format = {
    read<decltype(format.type)>(fin),
    read<decltype(format.channels)>(fin),
    read<decltype(format.samples_per_sec)>(fin),
    read<decltype(format.avg_bytes_per_sec)>(fin),
    read<decltype(format.block_align)>(fin),
    read<decltype(format.bits_per_sample)>(fin)
  };
  fin.ignore(format_size - 16);
  if (read<std::uint32_t>(fin) != *reinterpret_cast<const std::uint32_t *>("data")) {
	  throw std::runtime_error("dataチャンクが存在しません");
  }
  buffer_container_type buffer(read<std::uint32_t>(fin));
  fin.read(reinterpret_cast<char *>(buffer.data()), buffer.size());
  return std::tuple<buffer_container_type, buffer_format>(std::move(buffer), format);
}

class wave_buffer_data {
 public:
  explicit wave_buffer_data(const string_wrap &file_name)
      : data_(create_buffer(file_name)) {}

  const buffer_container_type &buffer() const {
    return std::get<0>(data_);
  }

  const buffer_format &format() const {
    return std::get<1>(data_);
  }

 private:
  sound_tuple data_;
};

class wave_loader {
 public:
  explicit wave_loader(const string_wrap &file_name, bool loop)
      : buffer_(std::make_shared<wave_buffer_data>(file_name)), loop_(loop) {}

  buffer_container_type::const_iterator buffer() const {
    return buffer_->buffer().cbegin();
  }

  std::size_t size() const {
    return buffer_->buffer().size();
  }

  buffer_format format() const {
    return buffer_->format();
  }

  bool loop() const {
    return loop_;
  }

 private:
  std::shared_ptr<wave_buffer_data> buffer_;
  bool loop_;
};
}

#endif
