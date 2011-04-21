#ifndef NGY313_GRAPHIC_DETAIL_TEXTURE_HPP_
#define NGY313_GRAPHIC_DETAIL_TEXTURE_HPP_
#include <boost/noncopyable.hpp>

namespace ngy313 { namespace graphic { namespace detail {
class texture_data : private boost::noncopyable {
 public:
  template <typename Loader>
  texture_data(const utility::string_piece &file_name, const Loader &loader) : data_(loader(file_name)) {}

  const texture_handle &texture() const {
    return std::get<0>(data_);
  }

  int width() const {
    return std::get<1>(data_);
  }

  int height() const {
    return std::get<2>(data_);
  }

 private:
  const std::tuple<texture_handle, int, int> data_;
};

typedef texture_data texture_type;
}}}

#endif
