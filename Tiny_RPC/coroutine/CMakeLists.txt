# aux_source_directory(.  DIR_LIB_SRCS)
set(SOURCES
    coroutine_pool.cpp
    coroutine.cpp
    memory.cpp
    coctx_swap.S
)
ENABLE_LANGUAGE(ASM)


add_library(coroutine ${SOURCES})

target_link_libraries(coroutine  Log LOCK dl)