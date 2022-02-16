cmake_minimum_required(VERSION 3.17)
project(lab4)

add_subdirectory(projet1)

add_executable(hello-world-4 main.cpp)

target_link_libraries(hello-world-4 PRIVATE lib)
