cmake_minimum_required(VERSION 3.10)
project(gizmo)

set(c_srcs
    "src/main.c"
)

add_executable(gizmo ${c_srcs})
target_include_directories(gizmo PRIVATE "src")