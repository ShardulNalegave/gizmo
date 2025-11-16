cmake_minimum_required(VERSION 3.15)
project(gizmo VERSION 0.1.0 LANGUAGES C CXX)

find_package(OpenGL REQUIRED)

add_subdirectory(vendor/SDL EXCLUDE_FROM_ALL)
add_subdirectory(vendor/imgui EXCLUDE_FROM_ALL)
add_subdirectory(vendor/spdlog EXCLUDE_FROM_ALL)

set(LIB_SRCS
    src/registers.c)

add_library(gizmo STATIC ${LIB_SRCS})
target_include_directories(gizmo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/include)

set(APP_SRCS
    app/main.cc
    app/app.cc)

add_executable(gizmo-app ${APP_SRCS})
target_include_directories(gizmo-app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/app)
target_link_libraries(gizmo-app PRIVATE SDL3::SDL3 OpenGL::GL ImGUI spdlog::spdlog gizmo)
