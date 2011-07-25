#ifndef NGY313_OGG_VORBIS_LOADER_HPP_
#define NGY313_OGG_VORBIS_LOADER_HPP_

#include <cassert>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <type_traits>
#include <vector>
#include <boost/config.hpp>
#include <boost/range/algorithm/fill.hpp>
#include <sys/types.h>
#include <sys/stat.h>
#include <vorbis/vorbisfile.h>
#include <ngy313/sound_format.hpp>
#include <ngy313/string_wrap.hpp>

namespace ngy313 {
#if defined(_MSC_VER)
std::FILE *file_open(const string_wrap &file_name, const string_wrap &option) {
  std::FILE *file;
  return fopen_s(&file, file_name.c_str(), option.c_str()) ? file : nullptr;
}
#elif defined(__GNUC__)
std::FILE *file_open(const string_wrap &file_name, const string_wrap &option) {
  return std::fopen(file_name.c_str(), option.c_str());
}
#endif

struct ogg_vorbis_delete {
  void operator ()(OggVorbis_File *ovf) const {
    assert(ovf);
    ov_clear(ovf);
    delete ovf;
  }
};

typedef std::shared_ptr<OggVorbis_File> ogg_vorbis_handle;

class ogg_vorbis_file {
 public:
  explicit ogg_vorbis_file(const buffer_container_type &buffer)
      : buffer_(buffer), pos_(0), ovf_() {
    ovf_ = init_ogg_vorbis();
  }

  OggVorbis_File *get() {
    return ovf_.get();
  }
  
  const buffer_container_type &buffer() const {
    return std::get<0>(data_);
  }

  const buffer_format &format() const {
    return std::get<1>(data_);
  }

 private:
  ogg_vorbis_handle init_ogg_vorbis() {
    std::unique_ptr<OggVorbis_File> ovf(new OggVorbis_File());
    const ov_callbacks callbacks = {&read, &seek, &close, &tell};
	if (ov_open_callbacks(this, ovf.get(), nullptr, 0, callbacks)) {
	  throw std::runtime_error("ogg vorbisを開くのに失敗しました");
	}
	return ogg_vorbis_handle(ovf.release(), ogg_vorbis_delete());
  }
  
  std::size_t read_impl(void *buffer, std::size_t size, std::size_t count) {
  	if (!buffer) {
      return 0;
    }
    std::size_t rcnt = (buffer_.size() - pos_) / size;
    if (rcnt > count) {
      rcnt = count;
    }
    std::memcpy(buffer, buffer_.data() + pos_, size * rcnt);
    pos_ += size * rcnt;
    return rcnt;
  }

  static std::size_t read(void *buffer, std::size_t size, std::size_t count, void *stream) {
    assert(stream);
    return static_cast<ogg_vorbis_file *>(stream)->read_impl(buffer, size, count);
  }

  int seek_impl(ogg_int64_t offset, int origin) {
    switch (origin) {
      case SEEK_CUR:
        pos_ += static_cast<long>(offset);
        break;
      case SEEK_END:
        pos_ = buffer_.size() + static_cast<long>(offset);
        break;
      case SEEK_SET:
        pos_ = static_cast<long>(offset);
        break;
      default:
        return -1;
    }
    if (pos_ > static_cast<long>(buffer_.size())) {
      pos_ = buffer_.size();
      return -1;
    } else if (pos_ < 0) {
      pos_ = 0;
      return -1;
    }
    return 0;
  }

  static int seek(void *stream, ogg_int64_t offset, int origin) {
    assert(stream);
    return static_cast<ogg_vorbis_file *>(stream)->seek_impl(offset, origin);
  }

  static int close(void *stream) {
    return 0;
  }

  long tellimpl() {
    return pos_;
  }

  static long tell(void *stream) {
    assert(stream);
    return static_cast<ogg_vorbis_file *>(stream)->tellimpl();
  }

  sound_tuple data_;
  const buffer_container_type &buffer_;
  long pos_;
  ogg_vorbis_handle ovf_;
};

inline
sound_tuple create_ogg_vorbis_buffer(const string_wrap &file_name) {
  std::FILE * const fp = file_open(file_name, "rb");
  if (!fp) {
    throw std::runtime_error("ファイルを開くのに失敗しました");
  }
  struct stat data;
  stat(file_name.c_str(), &data);
  buffer_container_type buffer(static_cast<std::size_t>(data.st_size));
  if (std::fread(&buffer.front(),
  		            sizeof(buffer.front()),
  		            buffer.size(),
  		            fp));
  std::fseek(fp, 0, SEEK_SET);
  std::unique_ptr<OggVorbis_File> temp(new OggVorbis_File());
  if (ov_open(fp, temp.get(), nullptr, 0)) {
    std::fclose(fp);
    throw std::runtime_error("ogg vorbisを開くのに失敗しました");
  }
  const ogg_vorbis_handle ovf(temp.release(), ogg_vorbis_delete());
  const vorbis_info * const info = ov_info(ovf.get(), -1);
  if (!info) {
    throw std::runtime_error("vorbisフォーマットの取得に失敗しました");
  }
  const buffer_format format = {
    kFormatPCM,
    static_cast<std::uint16_t>(info->channels),
    info->rate,
    info->rate * info->channels * 2,
    static_cast<std::uint16_t>(info->channels * 2),
    16
  };
  return sound_tuple(std::move(buffer), format);
}

class ogg_vorbis_buffer_data {
 public:
  explicit ogg_vorbis_buffer_data(const string_wrap &file_name)
      : data_(create_ogg_vorbis_buffer(file_name)) {}

  const buffer_container_type &buffer() const {
    return std::get<0>(data_);
  }

  const buffer_format &format() const {
    return std::get<1>(data_);
  }

 private:
  sound_tuple data_;
};

class ogg_vorbis_loader {
 public:
  explicit ogg_vorbis_loader(const string_wrap &file_name)
      : buffer_(std::make_shared<ogg_vorbis_buffer_data>(file_name)),
        file_(std::make_shared<ogg_vorbis_file>(buffer_->buffer())),
        data_(kSize_),
        offset_(0),
        loop_size_(0),
        loop_(false),
        end_(false),
        read_size_(0) {}

  explicit ogg_vorbis_loader(const string_wrap &file_name,
                             std::uint32_t offset,
                             std::uint32_t loop_size)
      : buffer_(std::make_shared<ogg_vorbis_buffer_data>(file_name)),
        file_(std::make_shared<ogg_vorbis_file>(buffer_->buffer())),
        data_(kSize_),
        offset_(offset),
        loop_size_(loop_size),
        loop_(true),
        end_(false),
        read_size_(0) {}

  buffer_container_type::const_iterator buffer() const {
    return data_.cbegin();
  }

  std::size_t size() const {
    return kSize_;
  }

  buffer_format format() const {
    return buffer_->format();
  }

  bool loop() const {
    return loop_;
  }

  void start() {
    init();
  }

  void end() {}

  bool ended() const {
    return end_;
  }

  void reset() {
    ov_pcm_seek(file_->get(), 0);
  }

 private:
  void init() {
    boost::fill(data_, 0);
    int request_size = kSize_;
    int bit_stream = 0;
    std::uint32_t com_size = 0;
    while (!end_) {
      const long read_size = ov_read(file_->get(),
                                     reinterpret_cast<char *>(data_.data()) + com_size,
                                     request_size,
                                     0,
                                     2,
                                     1,
                                     &bit_stream);
      if (loop_) {
        if (read_size_ >= offset_ + loop_size_ || !read_size) {
          read_size_ = offset_;
          ov_pcm_seek(file_->get(), offset_);
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
      if (data_.size() - com_size < kSize_) {
        if (loop_) {
         request_size = std::min(data_.size() - com_size,
                                 offset_ + loop_size_ - read_size_);
        } else {
          request_size = data_.size() - com_size;
        }
      }
    }
  }

  std::shared_ptr<ogg_vorbis_buffer_data> buffer_;
  std::shared_ptr<ogg_vorbis_file> file_;
  std::vector<std::uint8_t> data_;
  std::uint32_t offset_;
  std::uint32_t loop_size_;
  bool loop_;
  bool end_;
  std::uint32_t read_size_;
  BOOST_STATIC_CONSTEXPR std::size_t kSize_ = 4096;
};
}

#endif
