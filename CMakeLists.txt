cmake_minimum_required(VERSION 3.15)

project(project_gitxplorer
        VERSION 0.1.0
        LANGUAGES CXX)

find_package(spdlog REQUIRED CONFIG)
find_package(glfw3 REQUIRED CONFIG)

add_executable(gitxplorer
    src/main.cpp
    src/window.cpp
)
target_include_directories(gitxplorer PRIVATE include)
target_link_libraries(gitxplorer spdlog::spdlog glfw)