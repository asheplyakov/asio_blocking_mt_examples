#ifndef ASIO_SAMPLES_SYNC_THREADED_TCP_SERVER_HPP
#define ASIO_SAMPLES_SYNC_THREADED_TCP_SERVER_HPP
#include <cstdlib>
#include <atomic>
#include <boost/asio.hpp>
#if defined(_WIN32) && defined(__GNUC__)
#include <mingw.condition_variable.h>
#include <mingw.mutex.h>
#include <mingw.thread.h>
#else
#include <condition_variable>
#include <mutex>
#include <thread>
#endif
#include <utility>

using tcp = boost::asio::ip::tcp;

template <typename T>
class PickSlot {
  std::atomic<T>& counter_;
  std::condition_variable& cond_;

public:
  PickSlot(std::atomic<T>& counter, std::condition_variable& cond)
      : counter_(counter), cond_(cond) {
    counter_.fetch_add(1);
  }

  ~PickSlot() {
    counter_.fetch_sub(1);
    cond_.notify_one();
  }
};

/**
 * @brief Old school thread per client TCP server
 */
template <typename T>
class SyncThreadedTcpServer : public std::enable_shared_from_this<SyncThreadedTcpServer<T>> {
  boost::asio::io_service& io_context_;
  uint16_t port_;
  uint32_t client_limit_{0};
  std::atomic<uint32_t> client_count_{0};
  std::mutex mutex_;
  std::condition_variable slots_availabe_cond_;
  struct Key {
    explicit Key(int) {
    }
  };

public:
  static std::shared_ptr<SyncThreadedTcpServer<T>> create(boost::asio::io_service& io_context,
                                                          uint16_t port) {
    return std::make_shared<SyncThreadedTcpServer<T>>(
        SyncThreadedTcpServer<T>::Key{0}, io_context, port);
  }
  static std::shared_ptr<SyncThreadedTcpServer<T>> create(boost::asio::io_service& io_context,
                                                          uint16_t port,
                                                          uint32_t client_limit) {
    return std::make_shared<SyncThreadedTcpServer<T>>(
        SyncThreadedTcpServer<T>::Key{0}, io_context, port, client_limit);
  }

  void serve_forever() {
    tcp::endpoint endpoint{tcp::v4(), port_};
    tcp::acceptor acceptor{io_context_, endpoint.protocol()};
    acceptor.set_option(tcp::acceptor::reuse_address{true});
    acceptor.bind(endpoint);
    if (client_limit_ > 0) {
      acceptor.listen(client_limit_);
    } else {
      acceptor.listen();
    }
    for (;;) {
      {
        std::unique_lock<decltype(mutex_)> lock{mutex_};
        while (client_limit_ > 0 && client_count_.load() >= client_limit_) {
          slots_availabe_cond_.wait(lock);
        }
      }
      tcp::socket sock(io_context_);
      try {
        acceptor.accept(sock);
      } catch (std::exception& e) {
        std::cerr << "failed to accept: " << e.what() << std::endl;
        continue;
      }
      std::thread(
          [server = this->shared_from_this()](tcp::socket sock) {
            PickSlot<uint32_t> throttler(server->client_count_, server->slots_availabe_cond_);
            try {
              T handler;
              handler(sock);
            } catch (std::exception& e) {
              std::cerr << "failed to handle: " << e.what() << std::endl;
            }
          },
          std::move(sock))
          .detach();
    }
  }

  SyncThreadedTcpServer(Key const&, boost::asio::io_service& io_context, uint16_t port)
      : io_context_(io_context), port_{port} {
  }
  SyncThreadedTcpServer(Key const&,
                        boost::asio::io_service& io_context,
                        uint16_t port,
                        uint32_t client_limit)
      : io_context_(io_context), port_{port}, client_limit_{client_limit} {
  }
};

#endif /* ASIO_SAMPLES_SYNC_THREADED_TCP_SERVER_HPP */
