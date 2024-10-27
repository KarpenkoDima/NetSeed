# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(NetSeed C)

# Опции проекта
option(BUILD_TESTS "Build the tests" ON)

# Компилятор и флаги
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

# Глобальные пути для включаемых файлов
include_directories(${CMAKE_SOURCE_DIR}/core/include)

# Только memory
add_subdirectory(core/memory)

# Тесты
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(sprouts/tests)
endif()