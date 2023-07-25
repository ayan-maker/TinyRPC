project(cortest)

cmake_minimum_required(VERSION 3.6)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g")

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_EXE_LINKER_FLAGS  "-lpthread -ldl")

add_subdirectory(LOCK)
add_subdirectory(Log)
add_subdirectory(coroutine)
add_subdirectory(net)
add_subdirectory(hook)
add_subdirectory(config)

add_executable(tcpserver test/test_reactor.cpp)
target_link_libraries(tcpserver config net coroutine Log LOCK)