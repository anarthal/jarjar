cmake_minimum_required(VERSION 3.15.0)
project(jarjar)

add_library(jarjar src/jarjar.cpp)
target_include_directories(jarjar PUBLIC include)

add_executable(jarjar_test test/main.cpp)
target_link_libraries(jarjar_test PRIVATE jarjar)