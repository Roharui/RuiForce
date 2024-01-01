cmake_minimum_required(VERSION 3.14)

# 프로젝트 이름을 적어주세요
project(World-simulator VERSION 0.1.0)

SET(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE MY_SRCS ${PROJECT_SOURCE_DIR}/src/*.cpp)
set(MY_SRCS ${MY_SRCS} ${PROJECT_SOURCE_DIR}/src/main.cpp)
set(MY_INCLUDES ${PROJECT_SOURCE_DIR}/include)
set(MY_LIBS raylib) # 해당 변수에 필요한 라이브러리를 적어주세요

add_subdirectory(src)
add_subdirectory(tests)