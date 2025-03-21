cmake_minimum_required(VERSION 3.10)
project(gizmo)

set(gizmo_srcs "src/cpu.c")
add_library(gizmo ${gizmo_srcs})
target_include_directories(gizmo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(gizmo-exe "src/main.c")
target_link_libraries(gizmo-exe PRIVATE gizmo)

# =========================================================================

enable_testing()
find_package(GTest REQUIRED)

add_executable(gizmo-test
    "tests/hello_world.cpp")

target_link_libraries(gizmo-test PRIVATE
    gizmo
    GTest::GTest
    GTest::Main
    pthread)

add_test(NAME GIZMO_TESTS COMMAND gizmo-test)