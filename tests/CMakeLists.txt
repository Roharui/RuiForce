
set(MY_SRCS_MINUS_MAIN ${MY_SRCS})
list(REMOVE_ITEM MY_SRCS_MINUS_MAIN ${PROJECT_SOURCE_DIR}/src/main.cpp)

file(GLOB MY_TEST_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB MY_TEST_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
set(MY_TEST_NAME ${PROJECT_NAME}-test)

enable_testing()

add_executable(
  ${MY_TEST_NAME}
  ${MY_TEST_SRCS} 
  ${MY_SRCS_MINUS_MAIN}
)

target_include_directories(
  ${MY_TEST_NAME} 
  PUBLIC
  ${MY_INCLUDES}
  ${MY_TEST_INCLUDES}
  ${MY_MSYS2_INCLUDES}
  )

target_link_libraries(
  ${MY_TEST_NAME}
  GTest::gtest_main
  ${MY_LIBS}
)