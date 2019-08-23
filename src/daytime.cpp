#include <cstring>
#include <ctime>
#include <boost/asio.hpp>
#include <boost/format.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

using boost::asio::ip::tcp;

static void log(std::string const& message, tcp::socket const& client) {
  std::clog << boost::format("%|-25| [client address: %|15|]\n") % message %
                   client.remote_endpoint().address().to_string();
}

int main(int argc, char** argv) {
  boost::asio::io_service io_ctx;
  tcp::acceptor acceptor(io_ctx, tcp::endpoint(tcp::v4(), 13131));
  for (;;) {
    tcp::socket sock(io_ctx);
    acceptor.accept(sock);
    std::thread(
        [](tcp::socket sock) {
          char buf[32];
          time_t now = time(0);
          ctime_r(&now, buf);
          boost::asio::write(sock, boost::asio::buffer(buf, strlen(buf) + 1));
          log("connection from", sock);
        },
        std::move(sock))
        .detach();
  }
}
