
add_executable(${PROJECT_NAME} ${MY_SRCS})

target_include_directories(${PROJECT_NAME} PUBLIC ${MY_INCLUDES} ${MY_MSYS2_INCLUDES})

target_link_libraries(${PROJECT_NAME} ${MY_LIBS})