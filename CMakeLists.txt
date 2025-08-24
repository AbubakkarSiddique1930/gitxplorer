cmake_minimum_required(VERSION 3.15)

project(project_gitxplorer
        VERSION 0.1.0
        LANGUAGES CXX)

find_package(spdlog REQUIRED)

add_executable(gitxplorer
    src/main.cpp
)
target_link_libraries(gitxplorer spdlog::spdlog)