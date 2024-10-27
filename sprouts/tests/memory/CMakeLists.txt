# sprouts/tests/memory/CMakeLists.txt
add_executable(test_mbuf
    test_mbuf.c
)

target_include_directories(test_mbuf
    PRIVATE
        ${CMAKE_SOURCE_DIR}/core/include
)

target_link_libraries(test_mbuf
    PRIVATE
        unity
        netseed_memory      # Убрали netseed_log
        pthread
)

add_test(NAME test_mbuf COMMAND test_mbuf)