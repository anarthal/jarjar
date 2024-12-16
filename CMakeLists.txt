#
# Copyright (c) 2024 Ruben Perez Hidalgo (rubenperez038 at gmail dot com)
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#

cmake_minimum_required(VERSION 3.5..3.20)
project(jarjar LANGUAGES CXX)

find_package(Boost REQUIRED COMPONENTS headers)

add_library(jarjar src/jarjar.cpp)
target_include_directories(jarjar PUBLIC include)
target_link_libraries(jarjar PUBLIC Boost::headers)

add_executable(jarjar_test test/main.cpp)
target_link_libraries(jarjar_test PRIVATE jarjar)