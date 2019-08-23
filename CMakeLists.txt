cmake_minimum_required(VERSION 3.10)
project(asio_synch_multithreaded_servers)

find_package(Boost REQUIRED COMPONENTS system)
find_package(Threads REQUIRED)

add_executable(echoserver src/echoserver.cpp)
target_link_libraries(echoserver
	PRIVATE Boost::boost Boost::system Threads::Threads
)
set_target_properties(echoserver PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
)

add_executable(daytime src/daytime.cpp)
target_link_libraries(daytime
    PRIVATE Boost::boost Boost::system Threads::Threads
)
set_target_properties(daytime PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
)

