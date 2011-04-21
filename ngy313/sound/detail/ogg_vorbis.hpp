#ifndef NGY313_SOUND_DETAIL_OGG_VORBIS_HPP_
#define NGY313_SOUND_DETAIL_OGG_VORBIS_HPP_
#include <cassert>
#include <cstdlib>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
#include <boost/filesystem.hpp>
#include <boost/noncopyable.hpp>
#include <vorbis/vorbisfile.h>
#include <ngy313/sound/format.hpp>
#include <ngy313/sound/sound.hpp>

namespace ngy313 { namespace sound { namespace ogg_vorbis { namespace detail {
// OggVorbis_File�̊Ǘ��͂��������R�c���ׂ�
class ogg_vorbis {
 public:
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

class file {
 public:
  explicit file(const buffer_container_type &buffer) : ovf_(), buffer_(buffer), pos_(0) {
    const ov_callbacks callbacks = {
      &read, &seek, &close, &tell
    };
    if (ov_open_callbacks(this, ovf_.addressof(), NULL, 0, callbacks)) {
      throw std::runtime_error("ogg vorbis���J���̂Ɏ��s���܂���");
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
    std::size_t rcnt = (buffer_.size() - pos_) / size;
    if (rcnt > count) {
      rcnt = count;
    }
    std::memcpy(buffer, buffer_.data() + pos_, size * rcnt);
    pos_ += size * rcnt;
    return rcnt;
  }

  static std::size_t read(void * const buffer, const std::size_t size, const std::size_t count, void * const stream) {
    assert(stream);
    return static_cast<file *>(stream)->read_impl(buffer, size, count);
  }

  int seek_impl(const ogg_int64_t offset, const int origin) {
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

  static int seek(void * const stream, const ogg_int64_t offset, const int origin) {
    assert(stream);
    return static_cast<file *>(stream)->seek_impl(offset, origin);
  }

  static int close(void * const stream) {
    return 0;
  }

  long tellimpl() {
    return pos_;
  }

  static long tell(void * const stream) {
    assert(stream);
    return static_cast<file *>(stream)->tellimpl();
  }

  ogg_vorbis ovf_;
  const buffer_container_type &buffer_;
  long pos_;
};

inline
std::tuple<buffer_container_type, buffer_format> create_buffer(const std::string &file_name) {
  // ov_clear���t�@�C���n���h�������̂�std::FILE�̃X�}�|���͂ł��Ȃ�
  std::FILE * const fp = fopen(file_name.c_str(), "rb");
  if (!fp) {
    throw std::runtime_error("�t�@�C�����J���̂Ɏ��s���܂���");
  }
  buffer_container_type buffer(static_cast<std::size_t>(boost::filesystem::file_size(file_name)));
  if (std::fread(&buffer.front(), sizeof(buffer.front()), buffer.size(), fp));
  std::fseek(fp, 0, SEEK_SET);
  ogg_vorbis ovf;
  if (ov_open(fp, ovf.addressof(), NULL, 0)) {
    std::fclose(fp);
    throw std::runtime_error("ogg vorbis���J���̂Ɏ��s���܂���");
  }
  const vorbis_info * const info = ov_info(ovf.addressof(), -1);
  if (!info) {
    throw std::runtime_error("vorbis�t�H�[�}�b�g�̎擾�Ɏ��s���܂���");
  }
  const buffer_format format = {
    kFormatPCM,
    static_cast<std::uint16_t>(info->channels),
    info->rate,
    info->rate * info->channels * 2,
    static_cast<std::uint16_t>(info->channels * 2),
    16
  };
  return std::tuple<buffer_container_type, buffer_format>(std::move(buffer), format);
}

class buffer_data : private boost::noncopyable {
 public:
  explicit buffer_data(const std::string &file_name) : data_(create_buffer(file_name)) {}

  const buffer_container_type &buffer() const {
    return std::get<0>(data_);
  }

  const buffer_format &format() const {
    return std::get<1>(data_);
  }

 private:
  const std::tuple<buffer_container_type, buffer_format> data_;
};

typedef buffer_data buffer_type;
}}}}

#endif

