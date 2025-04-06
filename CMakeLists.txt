cmake_minimum_required(VERSION 3.10)
project(gizmo)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_subdirectory(vendor/log.c EXCLUDE_FROM_ALL)
add_subdirectory(vendor/SDL EXCLUDE_FROM_ALL)
add_subdirectory(vendor/imgui EXCLUDE_FROM_ALL)

# =========================================================================

set(gizmo_srcs "src/cpu.c" "src/memory.c" "src/cartridge.c" "src/cartridge/rom_only.c")
add_library(gizmo ${gizmo_srcs})
target_include_directories(gizmo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(gizmo log-c)

# =========================================================================

add_executable(gizmo-app
    "src-app/main.cc"
    "src-app/state.cc")
target_link_libraries(gizmo-app PRIVATE gizmo SDL3::SDL3 log-c imgui)
target_include_directories(gizmo-app PRIVATE "src-app")

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