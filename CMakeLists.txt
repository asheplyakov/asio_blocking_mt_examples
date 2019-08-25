cmake_minimum_required(VERSION 3.10)
project(asio_synch_multithreaded_servers)

find_package(Threads REQUIRED)
add_subdirectory(3rdparty/mingw-std-threads)

add_subdirectory(3rdparty/boost-cmake)
add_library(Boost_asio INTERFACE)
add_library(Boost::asio ALIAS Boost_asio)
if (WIN32)
   set(_asio_platform_libs ws2_32)
endif()
target_link_libraries(Boost_asio
    INTERFACE Boost::boost Boost::system ${_asio_platform_libs}
)

add_subdirectory(src)

