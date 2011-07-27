#ifndef NGY313_WAVE_LOADER_HPP_
#define NGY313_WAVE_LOADER_HPP_

#include <fstream>
#include <memory>
#include <tuple>
#include <type_traits>
#include <ngy313/sound_format.hpp>
#include <ngy313/string_wrap.hpp>

namespace ngy313 {
class wave_loader : public sound_loader_facade<normal_play_only_tag> {
 public:
  explicit wave_loader(const string_wrap &file_name)
      : data_(create_wave_buffer(file_name)) {}

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
  typedef std::tuple<buffer_container_type, buffer_format> sound_tuple;
  
  template <typename T, typename Stream>
  typename std::decay<T>::type read(Stream &stream) {
    typename std::decay<T>::type t;
    stream.read(reinterpret_cast<char *>(&t), sizeof(t));
    return t;
  }
  
  sound_tuple create_wave_buffer(const string_wrap &file_name) {
    std::ifstream fin(file_name.c_str(), std::ios::in | std::ios::binary);
    if (!fin) {
      throw std::runtime_error("�t�@�C�����J���̂Ɏ��s���܂���");
    }
    if (read<std::uint32_t>(fin) != 
        *reinterpret_cast<const std::uint32_t *>("RIFF")) {
      throw std::runtime_error("RIFF�`�����N�����݂��܂���");
    }
    fin.ignore(4);
    if (read<std::uint32_t>(fin) !=
        *reinterpret_cast<const std::uint32_t *>("WAVE")) {
	  throw std::runtime_error("WAVE�`�����N�����݂��܂���");
    }
    if (read<std::uint32_t>(fin) !=
        *reinterpret_cast<const std::uint32_t *>("fmt ")) {
	  throw std::runtime_error("fmt �`�����N�����݂��܂���");
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
    if (read<std::uint32_t>(fin) !=
        *reinterpret_cast<const std::uint32_t *>("data")) {
	    throw std::runtime_error("data�`�����N�����݂��܂���");
    }
    buffer_container_type buffer(read<std::uint32_t>(fin));
    fin.read(reinterpret_cast<char *>(buffer.data()), buffer.size());
    return sound_tuple(std::move(buffer), format);
  }

  sound_tuple data_;
};
}

#endif
