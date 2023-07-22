# aux_source_directory(.  DIR_LIB_SRCS)
set(SOURCES
    coroutine_hook.cpp
    coroutine_pool.cpp
    coroutine.cpp
    memory.cpp
    coctx_swap.S
)
ENABLE_LANGUAGE(ASM)

# set(ASM_OBJECTS "")
# foreach(SOURCE ${SOURCES})
#     if(${SOURCE} MATCHES ".*.S")
#         get_filename_component(OBJ ${SOURCE} NAME_WE)
#         add_custom_command(OUTPUT ${OBJ}.o
#             COMMAND ${CMAKE_ASM_COMPILER} ${CMAKE_ASM_FLAGS} -o ${OBJ}.o ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE}
#             DEPENDS ${SOURCE}
#             WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#         )
#         list(APPEND ASM_OBJECTS ${CMAKE_CURRENT_BINARY_DIR}/${OBJ}.o)
#     else()
#         list(APPEND ASM_OBJECTS ${SOURCE})
#     endif()
# endforeach()


add_library(coroutine ${SOURCES})

target_link_libraries(coroutine Log LOCK)