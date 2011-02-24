#pragma once
#include <string>
#include <boost/filesystem/path.hpp>

namespace ngy313 { namespace utility {
// �����œn�����x�̗p�r�����l���Ă��Ȃ�
// Google�Ƃ��ɂ���悤�Ȕėp�����������邩�͖���
#pragma warning(disable: 4512)

class string_piece {
 public:
  string_piece(const char * const str) : str_(str) {}

  string_piece(const std::string &str) : str_(str.c_str()) {}

  string_piece(const boost::filesystem::path &str) : str_(str.string().c_str()) {}

  const char *c_str() const {
    return str_;
  }

  std::string string() const {
    return std::string(c_str());
  }

 private:
  const char * const str_;
};

#pragma warning(default: 4512)
}}
