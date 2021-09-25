cmake_minimum_required(VERSION 3.13)
project(fotile_tree)

set(CMAKE_CXX_STANDARD 14)

add_executable(main src/main.cpp src/fotile_tree.tpp src/fotile_tree.h)
add_executable(test src/test.cpp src/fotile_tree.tpp src/fotile_tree.h)