#ifndef NGY313_OGG_VORBIS_LOADER_HPP_
#define NGY313_OGG_VORBIS_LOADER_HPP_

#include <cassert>
#include <cstddef>
#include <algorithm>
#include <fstream>
#include <memory>
#include <tuple>
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
class ogg_vorbis_loader : public sound_loader_facade<streaming_play_only_tag> {
 public:
  explicit ogg_vorbis_loader(const string_wrap &file_name)
      : file_(file_name),
        ovf_(init_ogg_vorbis(file_)),
        format_(create_ogg_vorbis_buffer_format(ovf_)),
        data_(4096),
        offset_(0),
        loop_size_(-1),
        loop_(false),
        end_(false),
        read_size_(0) {}

  buffer_container_type::const_iterator streaming_buffer() {
	init();
    return data_.cbegin();
  }
  
  void set_streaming_size(std::size_t size) {
    data_.resize(size);
  }

  buffer_format format() const {
    return format_;
  }

  bool end() const {
    return end_;
  }

  void reset() {
    ov_pcm_seek(ovf_.get(), 0);
  }

 private:
  struct ogg_vorbis_delete {
    void operator ()(OggVorbis_File *ovf) const {
      assert(ovf);
      ov_clear(ovf);
      delete ovf;
    }
  };
  
  typedef std::shared_ptr<OggVorbis_File> ogg_vorbis_handle;
  
  static buffer_format 
      create_ogg_vorbis_buffer_format(const ogg_vorbis_handle &ovf) {
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
    return format;
  }
  
  class ogg_vorbis_file {
   public:
    explicit ogg_vorbis_file(const string_wrap &file_name)
      : data_(create_ogg_vorbis_buffer(file_name)), pos_(0) {}
  
    const buffer_container_type &buffer() const {
      return data_;
    }
    
    static std::size_t read(void *buffer, 
                            std::size_t size,
                            std::size_t count,
                            void *stream) {
      assert(stream);
      return static_cast<ogg_vorbis_file *>(stream)->read_impl(
                 buffer,
                 size,
                 count);
    }
    
    static int seek(void *stream, ogg_int64_t offset, int origin) {
      assert(stream);
      return static_cast<ogg_vorbis_file *>(stream)->seek_impl(offset, origin);
    }
    
    static int close(void *stream) {
      return 0;
    }
    
    static long tell(void *stream) {
      assert(stream);
      return static_cast<ogg_vorbis_file *>(stream)->tellimpl();
    }

   private:
    buffer_container_type create_ogg_vorbis_buffer(const string_wrap &file_name) {
      struct stat data;
      stat(file_name.c_str(), &data);
      buffer_container_type buffer(static_cast<std::size_t>(data.st_size));
      std::ifstream fin(file_name.c_str(), std::ios::in | std::ios::binary);
      if (!fin) {
        throw std::runtime_error("ファイルを開くのに失敗しました");
      }
      fin.read(reinterpret_cast<char *>(buffer.data()), buffer.size());
      return buffer;
    }
    
    std::size_t read_impl(void *buffer, std::size_t size, std::size_t count) {
  	  if (!buffer) {
        return 0;
      }
      const std::size_t rcnt = std::min(
                                   static_cast<std::size_t>((data_.size() - pos_) / size),
                                   count);
      std::memcpy(buffer, data_.data() + pos_, size * rcnt);
      pos_ += size * rcnt;
      return rcnt;
    }

    int seek_impl(ogg_int64_t offset, int origin) {
      switch (origin) {
        case SEEK_CUR:
          pos_ += static_cast<long>(offset);
          break;
        case SEEK_END:
          pos_ = data_.size() + static_cast<long>(offset);
          break;
        case SEEK_SET:
          pos_ = static_cast<long>(offset);
          break;
        default:
          return -1;
      }
      if (pos_ > static_cast<long>(data_.size())) {
        pos_ = data_.size();
        return -1;
      } else if (pos_ < 0) {
        pos_ = 0;
        return -1;
      }
      return 0;
    }

    long tellimpl() {
      return pos_;
    }
  
    buffer_container_type data_;
    long pos_;
  };

  static ogg_vorbis_handle init_ogg_vorbis(ogg_vorbis_file &file) {
    std::unique_ptr<OggVorbis_File> ovf(new OggVorbis_File());
    const ov_callbacks callbacks = {&ogg_vorbis_file::read,
                                    &ogg_vorbis_file::seek,
                                    &ogg_vorbis_file::close,
                                    &ogg_vorbis_file::tell};
	if (ov_open_callbacks(&file, ovf.get(), nullptr, 0, callbacks)) {
	  throw std::runtime_error("ogg vorbisを開くのに失敗しました");
	}
	return ogg_vorbis_handle(ovf.release(), ogg_vorbis_delete());
  }
  
  bool check_end(long read_size) const {
    return !read_size || (loop_size_ >= 0 && 
                          read_size_ >= offset_ + loop_size_);
  }
  
  void set_loop_start() {
    read_size_ = offset_;
    ov_pcm_seek(ovf_.get(), offset_);
  }
  
  bool loop_check(long read_size) {
    if (loop_) {
      if (check_end(read_size)) {
        set_loop_start();
      }
    } else {
      if (check_end(read_size)) {
        end_ = true;
        return true;
      }
    }
    return false;
  }
  
  bool check_read_end(std::uint32_t com_size) const {
    return com_size >= kSize_;
  }
  
  int request(std::uint32_t com_size) const {
	return loop_ ? 
	       std::min<int>(data_.size() - com_size,
                         offset_ + loop_size_ - read_size_) :
           data_.size() - com_size;
  }
  
  void init() {
    boost::fill(data_, 0);
    int request_size = kSize_;
    int bit_stream = 0;
    std::uint32_t com_size = 0;
    while (!end_) {
      const long read_size = ov_read(ovf_.get(),
                                     reinterpret_cast<char *>(data_.data()) +
                                     com_size,
                                     request_size,
                                     0,
                                     2,
                                     1,
                                     &bit_stream);
      if (loop_check(read_size)) {
        break;
      }
      com_size += read_size;
      read_size_ += read_size;
      if (check_read_end(com_size)) {
        break;
      } else {
        request_size = request(com_size);
      }
    }
  }
  
  ogg_vorbis_file file_;
  ogg_vorbis_handle ovf_;
  buffer_format format_;
  buffer_container_type data_;
  std::int64_t offset_;
  std::int64_t loop_size_;
  bool loop_;
  bool end_;
  std::int64_t read_size_;
  static const std::size_t kSize_ = 4096;
};

/*
class ogg_vorbis_loader : public sound_loader_facade<streaming_play_only_tag> {
 public:
  explicit ogg_vorbis_loader(const string_wrap &file_name)
      : buffer_(std::make_shared<ogg_vorbis_buffer_data>(file_name)),
        file_(std::make_shared<ogg_vorbis_file>(buffer_->buffer())),
        data_(kSize_),
        offset_(-1),
        loop_size_(-1),
        loop_(false),
        end_(false),
        read_size_(0) {}

  explicit ogg_vorbis_loader(const string_wrap &file_name,
                             std::int64_t offset,
                             std::int64_t loop_size)
      : buffer_(std::make_shared<ogg_vorbis_buffer_data>(file_name)),
        file_(std::make_shared<ogg_vorbis_file>(buffer_->buffer())),
        data_(kSize_),
        offset_(offset),
        loop_size_(loop_size),
        loop_(true),
        end_(false),
        read_size_(0) {}

  buffer_container_type::const_iterator buffer() const {
    return data_->cbegin();
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
  bool check_end(long read_size) const {
    return !read_size || (offset_ >= 0 && 
                          loop_size_ >= 0 && 
                          read_size_ >= offset_ + loop_size_);
  }
  
  void set_loop_start() {
    read_size_ = offset_;
    ov_pcm_seek(file_->get(), offset_);
  }
  
  bool loop_check(long read_size) {
    if (loop_) {
      if (check_end(read_size)) {
        set_loop_start();
      }
    } else {
      if (check_end(read_size)) {
        end_ = true;
        return true;
      }
    }
    return false;
  }
  
  bool check_read_end(std::uint32_t com_size) const {
    return com_size >= kSize_;
  }
  
  int request(std::uint32_t com_size) const {
	return loop_ ? 
	       std::min<int>(data_.size() - com_size,
                         offset_ + loop_size_ - read_size_) :
           data_.size() - com_size;
  }
  
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
      if (loop_check(read_size)) {
        break;
      }
      com_size += read_size;
      read_size_ += read_size;
      if (check_read_end(com_size)) {
        break;
      } else {
        request_size = request(com_size);
      }
    }
  }

  std::shared_ptr<ogg_vorbis_buffer_data> buffer_;
  std::shared_ptr<ogg_vorbis_file> file_;
  std::vector<std::uint8_t> data_;
  std::int64_t offset_;
  std::int64_t loop_size_;
  bool loop_;
  bool end_;
  std::uint32_t read_size_;
  BOOST_STATIC_CONSTEXPR std::size_t kSize_ = 4096;
};
*/
}

#endif
