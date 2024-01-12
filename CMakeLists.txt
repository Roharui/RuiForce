cmake_minimum_required(VERSION 3.14)

# 프로젝트 이름을 적어주세요
project(World-simulator VERSION 0.1.0)

SET(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

file(GLOB_RECURSE MY_SRCS ${PROJECT_SOURCE_DIR}/src/*.cpp)
set(MY_SRCS ${MY_SRCS} ${PROJECT_SOURCE_DIR}/src/main.cpp)
set(MY_INCLUDES ${PROJECT_SOURCE_DIR}/include)
set(MY_LINKS ${PROJECT_SOURCE_DIR}/lib)

set(MY_LIBS raylib ws2_32 wsock32 rabbitmq)

add_subdirectory(src)
add_subdirectory(tests)