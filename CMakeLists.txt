cmake_minimum_required(VERSION 3.10)
project(asio_synch_multithreaded_servers)

find_package(Threads REQUIRED)
add_subdirectory(3rdparty/boost-cmake)
add_subdirectory(src)

