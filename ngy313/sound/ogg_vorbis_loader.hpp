#ifndef NGY313_SOUND_OGG_VORBIS_LOADER_HPP_
#define NGY313_SOUND_OGG_VORBIS_LOADER_HPP_
#include <algorithm>
#include <string>
#include <boost/range/algorithm/fill.hpp>
#include <ngy313/sound/detail/ogg_vorbis.hpp>

namespace ngy313 { namespace sound { namespace ogg_vorbis {
class loader {
 public:
  explicit loader(const std::string &file_name) : buffer_(file_name), 
                                                  file_(buffer_.buffer()),
                                                  data_(kSize_),
                                                  offset_(0),
                                                  loop_size_(0),
                                                  loop_(false),
                                                  end_(false),
                                                  read_size_(0) {
    init();
  }

  loader(const std::string &file_name, const std::uint32_t offset, const std::uint32_t loop_size)
      : buffer_(file_name), 
        file_(buffer_.buffer()),
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
    return buffer_.format();
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

  const detail::buffer_type buffer_;
  detail::file file_;
  std::vector<std::uint8_t> data_;
  const std::uint32_t offset_;
  const std::uint32_t loop_size_;
  const bool loop_;
  bool end_;
  std::uint32_t read_size_;
  static const std::size_t kSize_ = 4096;
};
}}}

#endif
