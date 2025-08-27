cmake_minimum_required(VERSION 3.15)

project(project_gitxplorer
        VERSION 0.1.0
        LANGUAGES CXX)

find_package(spdlog REQUIRED CONFIG)
find_package(glfw3 REQUIRED CONFIG)
find_package(skia REQUIRED CONFIG)

add_library(sourcelib STATIC
    src/window.cpp
    src/sk.cpp
    src/font.cpp
)
target_include_directories(sourcelib PUBLIC include)
target_link_libraries(sourcelib spdlog::spdlog glfw skia::skia)

add_executable(gitxplorer src/main.cpp)
target_link_libraries(gitxplorer sourcelib)

if(BUILD_TEST_EXE STREQUAL "ON")
    add_executable(test test/test.cpp)
    target_link_libraries(test sourcelib)
endif()