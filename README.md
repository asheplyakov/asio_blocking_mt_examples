# Multithreaded blocking network servers with [Asio](https://think-async.com/Asio)

Some of [asio examples](http://think-async.com/Asio/boost_asio_1_12_2/doc/html/boost_asio/examples/cpp11_examples.html)
rewritten using "thread per a client" approach.

### Why?

Often the "thread per a client" model is good enough, i.e.

- When the workload is CPU bound
- When interfacing with 3rd party code doing blocking calls


### Prerequisites

* C++ compiler supporting C++14
* CMake 3.12 or newer


### Building

#### Linux

```bash
git clone --recursive git://github.com/asheplyakov/asio_blocking_mt_examples.git
cd asio_blocking_mt_examples
mkdir -p build
cd build
cmake ..
make -j
```

#### Cross-compilation for Windows

Use the supplied toolchain file (cmake/Toolchain-mingw.cmake):

```bash
git clone --recursive git://github.com/asheplyakov/asio_blocking_mt_examples.git
cd asio_blocking_mt_examples
mkdir -p build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/Toolchain-mingw.cmake ..
make -j
```
