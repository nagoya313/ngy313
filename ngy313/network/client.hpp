#ifndef NGY313_NETWORK_CLIENT_HPP_
#define NGY313_NETWORK_CLIENT_HPP_
#include <cstdint>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>

namespace ngy313 { namespace network {
class client : private boost::noncopyable {
 public:
  client(const std::string &ip, const std::uint16_t port) 
      : io_(), socket_(io_), send_buffer_(), receive_buffer_(), message_() {
    socket_.connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(ip), port));
  }

  void update() {
    io_.reset();
    io_.run();
  }

  template <typename T>
  void send(const T &t) {
    std::ostream os(&send_buffer_);
    os << t;
    boost::asio::async_write(socket_, send_buffer_.data(), boost::bind(&client::send_end, this, _1));
  }

  void receive() {
    boost::asio::async_read_until(socket_, receive_buffer_, '\n', boost::bind(&client::receive_end, this, _1));
  }

  void reset() {
    io_.reset();
  }

  void run() {
    io_.run();
  }

 private:
  void send_end(const boost::system::error_code &error) {
    if (error) {
      throw std::runtime_error(error.message());
    } else {  
      send_buffer_.consume(send_buffer_.size());
    }
  }

  void receive_end(const boost::system::error_code &error) {
    if (error) {
      throw std::runtime_error(error.message());
    } else {
      receive_buffer_.consume(receive_buffer_.size());
    }
  }

  boost::asio::io_service io_;
  boost::asio::ip::tcp::socket socket_;
  boost::asio::streambuf send_buffer_;
  boost::asio::streambuf receive_buffer_;
  std::string message_;
};
}}

#endif
