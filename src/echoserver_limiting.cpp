#include <cstdint>
#include <cstring>
#include <ctime>
#include <boost/asio.hpp>
#include <iostream>
#include <string>

#include "syncthreadedtcpserver.hpp"

struct EchoHandler {
  static constexpr unsigned buflen = 4096;
  void operator()(tcp::socket& sock) {
    char data[buflen];
    boost::system::error_code error;
    std::size_t len;
    for (;;) {
      len = sock.read_some(boost::asio::buffer(data), error);
      if (error == boost::asio::error::eof) {
        break;  // connection closed cleanly by peer
      } else if (error) {
        throw boost::system::system_error(error);
      }
      boost::asio::write(sock, boost::asio::buffer(data, len));
    }
  }
};

int main(int argc, char** argv) {
  boost::asio::io_service io_context;
  unsigned short port = 16161;
  uint32_t max_clients = 2;
  auto server = SyncThreadedTcpServer<EchoHandler>::create(io_context, port, max_clients);
  server->serve_forever();
}
