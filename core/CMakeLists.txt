# core/memory/CMakeLists.txt
add_library(netseed_memory
    memory.c
)

target_include_directories(netseed_memory
    PUBLIC
        ${CMAKE_SOURCE_DIR}/core/include
)