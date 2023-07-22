aux_source_directory(.  DIR_LIB_SRCS)

add_library(config  ${DIR_LIB_SRCS})

target_link_libraries(config net coroutine)