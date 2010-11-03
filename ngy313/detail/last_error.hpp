#pragma 
#include <cstdint>
#include <cstring>
#include <string>
#include <stdexcept>
#include <Windows.h>

namespace ngy313 { namespace detail {
std::string format_error_message() {
  void *message_buffer = nullptr;
  FormatMessage(
      FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
      nullptr,
      GetLastError(),
      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
      reinterpret_cast<char *>(message_buffer),
      0,
      nullptr);
  LocalFree(message_buffer);
  return std::string(
             static_cast<const char *>(message_buffer),
             static_cast<const char *>(message_buffer) + 
             std::strlen(static_cast<const char *>(message_buffer)));
}

class last_error : public std::runtime_error {
 public:
  explicit last_error(const std::string &message)
      : std::runtime_error(message + format_error_message()) {}
};
}}