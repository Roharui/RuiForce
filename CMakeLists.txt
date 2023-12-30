cmake_minimum_required(VERSION 3.14)

# 프로젝트 이름을 적어주세요
project(World-simulator VERSION 0.1.0)

SET(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  DOWNLOAD_DIR ${CMAKE_CURRENT_BINARY_DIR}/dependencies
  DOWNLOAD_NO_EXTRACT TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB MY_SRCS ${PROJECT_SOURCE_DIR}/src/**/*.cpp)
set(MY_SRCS ${MY_SRCS} ${PROJECT_SOURCE_DIR}/src/main.cpp)
set(MY_INCLUDES ${PROJECT_SOURCE_DIR}/include)
set(MY_LIBS raylib) # 해당 변수에 필요한 라이브러리를 적어주세요

add_subdirectory(src)
add_subdirectory(tests)