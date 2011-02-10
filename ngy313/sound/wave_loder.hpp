#pragma once
#include <cassert>
#include <cstdint>
#include <fstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>
#include <ngy313/sound/format.hpp>
#include <ngy313/utility/read.hpp>

namespace ngy313 { namespace sound {
inline
std::tuple<buffer_container_type, buffer_format> create_wave_buffer(const std::string &file_name) {
  std::ifstream fin(file_name, std::ios::in | std::ios::binary);
  if (!fin) {
    throw std::runtime_error("ファイルを開くのに失敗しました");
  }
  if (utility::read<std::uint32_t>(fin) != *reinterpret_cast<std::uint32_t *>("RIFF")) {
    throw std::runtime_error("RIFFチャンクが存在しません");
  }
  fin.ignore(4);
  if (utility::read<std::uint32_t>(fin) != *reinterpret_cast<std::uint32_t *>("WAVE")) {
	  throw std::runtime_error("WAVEチャンクが存在しません");
  }
  if (utility::read<std::uint32_t>(fin) != *reinterpret_cast<std::uint32_t *>("fmt ")) {
	  throw std::runtime_error("fmt チャンクが存在しません");
  } 
  const std::uint32_t format_size = utility::read<decltype(format_size)>(fin);
  const buffer_format format = {
    utility::read<decltype(format.type)>(fin),
    utility::read<decltype(format.channels)>(fin),
    utility::read<decltype(format.samples_per_sec)>(fin),
    utility::read<decltype(format.avg_bytes_per_sec)>(fin),
    utility::read<decltype(format.block_align)>(fin),
    utility::read<decltype(format.bits_per_sample)>(fin)
  };
  fin.ignore(format_size - 16);
  if (utility::read<std::uint32_t>(fin) != *reinterpret_cast<std::uint32_t *>("data")) {
	  throw std::runtime_error("dataチャンクが存在しません");
  }
  buffer_container_type buffer(utility::read<std::uint32_t>(fin));
  fin.read(reinterpret_cast<char *>(&buffer.front()), buffer.size());
  return std::tuple<buffer_container_type, buffer_format>(std::move(buffer), format);
}

class wave_buffer_data {
 public:
  explicit wave_buffer_data(const std::string &file_name) : data_(create_wave_buffer(file_name)) {}

  buffer_container_type::const_iterator buffer() const {
    return std::get<0>(data_).cbegin();
  }

  std::size_t size() const {
    return std::get<0>(data_).size();
  }

  buffer_format format() const {
    return std::get<1>(data_);
  }

 private:
  const std::tuple<buffer_container_type, buffer_format> data_;
};

typedef boost::flyweights::flyweight<boost::flyweights::key_value<std::string, wave_buffer_data>> wave_buffer_type;

class wave_loader {
 public:
  explicit wave_loader(const std::string &file_name) : buffer_(file_name) {}

  buffer_container_type::const_iterator buffer() const {
    return buffer_.get().buffer();
  }

  std::size_t size() const {
    return buffer_.get().size();
  }

  buffer_format format() const {
    return buffer_.get().format();
  }

 private:
  const wave_buffer_type buffer_;
};
}}
