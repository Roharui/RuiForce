

add_library(HttpRequest SHARED HttpRequest.cpp)

target_include_directories(HttpRequest PUBLIC ${MY_INCLUDES})
target_link_libraries(HttpRequest ws2_32)
