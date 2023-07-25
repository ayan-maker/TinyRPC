aux_source_directory(.  DIR_LIB_SRCS)

add_library(hook  ${DIR_LIB_SRCS})

target_link_libraries(hook net)