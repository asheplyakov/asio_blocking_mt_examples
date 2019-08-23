#include <cstdlib>
#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include <utility>

using boost::asio::ip::tcp;

const int max_length = 1024;

int main(int argc, char** argv) {
  boost::asio::io_service io_context;
  unsigned short port = 16161;
  tcp::acceptor a(io_context, tcp::endpoint(tcp::v4(), port));
  for (;;) {
    tcp::socket s(io_context);
    a.accept(s);

    std::thread(
        [](tcp::socket sock) {
          try {
            for (;;) {
              char data[max_length];
              boost::system::error_code error;
              size_t length = sock.read_some(boost::asio::buffer(data), error);
              if (error == boost::asio::error::eof) {
                break;  // Connection closed cleanly by peer.
              } else if (error) {
                throw boost::system::system_error(error);  // Some other error.
              }
              boost::asio::write(sock, boost::asio::buffer(data, length));
            }
          } catch (std::exception& e) {
            std::cerr << "Exception in thread: " << e.what() << "\n";
          }
        },
        std::move(s))
        .detach();
  }
  return 0;
}
