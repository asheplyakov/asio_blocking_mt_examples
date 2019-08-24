
add_executable(echoserver echoserver.cpp)
target_link_libraries(echoserver
    PRIVATE Boost::boost Boost::system Threads::Threads
)
set_target_properties(echoserver PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
)

add_executable(daytime daytime.cpp)
target_link_libraries(daytime
    PRIVATE Boost::boost Boost::system Threads::Threads
)
set_target_properties(daytime PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
)

