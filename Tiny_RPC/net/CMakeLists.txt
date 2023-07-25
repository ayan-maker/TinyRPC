set(CMAKE_CXX_STANDARD 11)

set( DIR_LIB_SRCS
    Accept.cpp
    Reactor.cpp
    FdEvent.cpp
)

add_library(net ${DIR_LIB_SRCS})

target_link_libraries(net coroutine)