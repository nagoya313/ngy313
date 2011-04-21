#ifndef NGY313_NETWORK_SERVER_HPP_
#define NGY313_NETWORK_SERVER_HPP_
#include <cstdint>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>

namespace ngy313 { namespace network {
class server : private boost::noncopyable {
 public:
  explicit server(const std::uint16_t port) : io_(),
                                              socket_(io_),
                                              request_buffer_(),
                                              response_buffer_(), 
                                              acceptor_(io_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
                                              connected_(false) {
    acceptor_.async_accept(socket_, boost::bind(&server::acceptor_end, this, _1));
  }

  bool connected() const {
    return connected_;
  }

  bool closed() const {
  }

  void update() {
    io_.reset();
    io_.run();
  }

  void receive_start() {
    boost::asio::async_read_until(socket_, request_buffer_, '\n', boost::bind(&server::receive_end, this, _1));
  }

  template <typename T>
  void send(const T &t) {
    std::ostream os(&response_buffer_);
    os << t;
    boost::asio::async_write(socket_, response_buffer_.data(), boost::bind(&server::send_end, this, _1));
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
      request_buffer_.consume(request_buffer_.size());
    }
  }

  void acceptor_end(const boost::system::error_code &error) {
    if (error) {
      throw std::runtime_error(error.message());
    } else {
      connected_ = true;
    }
  }

  void receive_end(const boost::system::error_code &error) {
    if (error) {
      throw std::runtime_error(error.message());
    } else {
      request_buffer_.consume(request_buffer_.size());
    }
  }

  boost::asio::io_service io_;
  boost::asio::ip::tcp::socket socket_;
  boost::asio::streambuf request_buffer_;
  boost::asio::streambuf response_buffer_;
  boost::asio::ip::tcp::acceptor acceptor_;
  bool connected_;
};
}}

#endif
