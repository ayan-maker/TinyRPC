set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

aux_source_directory(.  DIR_LIB_SRCS)

add_library(Log  ${DIR_LIB_SRCS})

target_link_libraries(Log PUBLIC Threads::Threads)