
add_executable(echoserver echoserver.cpp)
target_link_libraries(echoserver
    PRIVATE Boost::asio Threads::Threads
    $<$<AND:$<PLATFORM_ID:Windows>,$<CXX_COMPILER_ID:GNU>>:MinGW::Threads>
)
set_target_properties(echoserver PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
)
target_link_options(echoserver
    PRIVATE
    $<$<AND:$<PLATFORM_ID:Windows>,$<CXX_COMPILER_ID:GNU>>:-static-libgcc -static-libstdc++>
)


add_executable(daytime daytime.cpp)
target_link_libraries(daytime
    PRIVATE Boost::asio Threads::Threads
    $<$<AND:$<PLATFORM_ID:Windows>,$<CXX_COMPILER_ID:GNU>>:MinGW::Threads>
)
set_target_properties(daytime PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
)
target_link_options(daytime
    PRIVATE
    $<$<AND:$<PLATFORM_ID:Windows>,$<CXX_COMPILER_ID:GNU>>:-static-libgcc -static-libstdc++>
)

add_executable(echoserver_limiting
    echoserver_limiting.cpp
    syncthreadedtcpserver.hpp
)
target_link_libraries(echoserver_limiting
    PRIVATE Boost::asio Threads::Threads
    $<$<AND:$<PLATFORM_ID:Windows>,$<CXX_COMPILER_ID:GNU>>:MinGW::Threads>
)
set_target_properties(echoserver_limiting PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)
target_link_options(echoserver_limiting
    PRIVATE
    $<$<AND:$<PLATFORM_ID:Windows>,$<CXX_COMPILER_ID:GNU>>:-static-libgcc -static-libstdc++>
)
