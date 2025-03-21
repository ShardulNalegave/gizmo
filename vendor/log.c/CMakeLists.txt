cmake_minimum_required(VERSION 3.10)
project(log-c)

add_compile_definitions(LOG_USE_COLOR)
add_library(log-c "log.c")
target_include_directories(log-c PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)