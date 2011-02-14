#pragma once
#ifndef NDEBUG
#pragma comment(lib, "libogg_static_d.lib")
#pragma comment(lib, "libvorbis_static_d.lib")
#pragma comment(lib, "libvorbisfile_static_d.lib")
#else
#pragma comment(lib, "libogg_static.lib")
#pragma comment(lib, "libvorbis_static.lib")
#pragma comment(lib, "libvorbisfile_static.lib")
#endif
#include <cassert>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>
#include <boost/filesystem.hpp>
#include <boost/range/algorithm/fill.hpp>
#include <vorbis/vorbisfile.h>
#include <XAudio2.h>
#include <ngy313/sound/format.hpp>
#include <ngy313/sound/sound.hpp>

namespace ngy313 { namespace sound {
// OggVorbis_Fileの管理はもう少し審議すべき
struct ogg_vorbis {
  ogg_vorbis() : ovf_() {}

  ~ogg_vorbis() {
    ov_clear(&ovf_);
  }

  OggVorbis_File *addressof() {
    return &ovf_;
  }

 private:
  OggVorbis_File ovf_;
};

class ogg_file {
 public:
  explicit ogg_file(const buffer_container_type::const_iterator front, const std::size_t size)
      : ovf_(), front_(front), pos_(0), size_(size) {
    const ov_callbacks callbacks = {
      &read, &seek, &close, &tell
    };
    if (ov_open_callbacks(this, ovf_.addressof(), nullptr, 0, callbacks)) {
      throw std::runtime_error("ogg vorbisを開くのに失敗しました");
    }
  }

  OggVorbis_File *get() {
    return ovf_.addressof();
  }

 private:
  std::size_t read_impl(void * const buffer, const std::size_t size, const std::size_t count) {
    if (!buffer) {
      return 0;
    }
    std::size_t rcnt = (size_ - pos_) / size;
    if (rcnt > count) {
      rcnt = count;
    }
    std::memcpy(buffer, &(*front_) + pos_, size * rcnt);
    pos_ += size * rcnt;
    return rcnt;
  }

  static std::size_t read(void * const buffer, const std::size_t size, const std::size_t count, void * const stream) {
    assert(stream);
    return static_cast<ogg_file *>(stream)->read_impl(buffer, size, count);
  }

  int seek_impl(const ogg_int64_t offset, const int origin) {
    switch (origin) {
      case SEEK_CUR:
        pos_ += static_cast<long>(offset);
        break;
      case SEEK_END:
        pos_ = size_ + static_cast<long>(offset);
        break;
      case SEEK_SET:
        pos_ = static_cast<long>(offset);
        break;
      default:
        return -1;
    }
    if (pos_ > size_) {
      pos_ = size_;
      return -1;
    } else if (pos_ < 0) {
      pos_ = 0;
      return -1;
    }
    return 0;
  }

  static int seek(void * const stream, const ogg_int64_t offset, const int origin) {
    assert(stream);
    return static_cast<ogg_file *>(stream)->seek_impl(offset, origin);
  }

  static int close(void * const stream) {
    return 0;
  }

  long tellimpl() {
    return pos_;
  }

  static long tell(void * const stream) {
    assert(stream);
    return static_cast<ogg_file *>(stream)->tellimpl();
  }

  ogg_vorbis ovf_;
  buffer_container_type::const_iterator front_;
  long pos_;
  long size_;
};

inline
std::tuple<buffer_container_type, buffer_format> create_ogg_buffer(const std::string &file_name) {
  // ov_clearがファイルハンドルを閉じるのでstd::FILEのスマポ化はできない
  std::FILE *fp = std::fopen(file_name.c_str(), "rb");
  if (!fp) {
    throw std::runtime_error("ファイルを開くのに失敗しました");
  }
  buffer_container_type buffer(static_cast<std::size_t>(boost::filesystem::file_size(file_name)));
  std::fread(&buffer.front(), sizeof(buffer.front()), buffer.size(), fp);
  std::fseek(fp, 0, SEEK_SET);
  ogg_vorbis ovf;
  if (ov_open(fp, ovf.addressof(), nullptr, 0)) {
    std::fclose(fp);
    throw std::runtime_error("ogg vorbisを開くのに失敗しました");
  }
  const vorbis_info * const info = ov_info(ovf.addressof(), -1);
  if (!info) {
    throw std::runtime_error("vorbisフォーマットの取得に失敗しました");
  }
  const buffer_format format = {
    WAVE_FORMAT_PCM,
    static_cast<std::uint16_t>(info->channels),
    info->rate,
    info->rate * info->channels * 2,
    static_cast<std::uint16_t>(info->channels * 2),
    16
  };
  return std::tuple<buffer_container_type, buffer_format>(std::move(buffer), format);
}

class ogg_buffer_data {
 public:
  explicit ogg_buffer_data(const std::string &file_name) : data_(create_ogg_buffer(file_name)) {}

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

typedef boost::flyweights::flyweight<boost::flyweights::key_value<std::string, ogg_buffer_data>> ogg_buffer_type;

class ogg_loader {
 public:
  explicit ogg_loader(const std::string &file_name) : buffer_(file_name), 
                                                      file_(buffer_.get().buffer(), buffer_.get().size()),
                                                      data_(kSize_),
                                                      offset_(0),
                                                      loop_size_(0),
                                                      loop_(false),
                                                      end_(false),
                                                      read_size_(0) {
    init();
  }

  ogg_loader(const std::string &file_name, const std::uint32_t offset, const std::uint32_t loop_size)
      : buffer_(file_name), 
        file_(buffer_.get().buffer(), buffer_.get().size()),
        data_(kSize_),
        offset_(offset),
        loop_size_(loop_size),
        loop_(true),
        end_(false),
        read_size_(0) {
    init();
  }

  buffer_container_type::const_iterator buffer() const {
    return data_.cbegin();
  }

  std::size_t size() const {
    return kSize_;
  }

  buffer_format format() const {
    return buffer_.get().format();
  }

  void start() {
    init();
  }

  void end() {
  }

  bool ended() const {
    return end_;
  }

  void reset() {
    ov_pcm_seek(file_.get(), 0);
  }

 private:
  void init() {
    boost::fill(data_, 0);
    int request_size = size();
    int bit_stream = 0;
    std::uint32_t com_size = 0;
    while (!end_) {
      const long read_size = ov_read(file_.get(), 
                                     reinterpret_cast<char *>(data_.data()) + com_size,
                                     request_size, 
                                     0,
                                     2,
                                     1,
                                     &bit_stream);
      if (loop_) {
        if (read_size_ >= offset_ + loop_size_ || !read_size) {
          read_size_ = offset_;
          ov_pcm_seek(file_.get(), offset_);
        }
      } else {
        if (!read_size) {
          end_ = true;
          break;
        }
      }
      com_size += read_size;
      read_size_ += read_size;
      if (com_size >= kSize_) {
        break;
      }
      if (data_.size() - com_size < size()) {
        if (loop_) {
          request_size = (std::min)(data_.size() - com_size, offset_ + loop_size_ - read_size_);
        } else {
          request_size = data_.size() - com_size;
        }
      }
    }
    
  }

  const ogg_buffer_type buffer_;
  ogg_file file_;
  std::vector<std::uint8_t> data_;
  const std::uint32_t offset_;
  const std::uint32_t loop_size_;
  const bool loop_;
  bool end_;
  std::uint32_t read_size_;
  static const std::size_t kSize_ = 4096;
};
}}
