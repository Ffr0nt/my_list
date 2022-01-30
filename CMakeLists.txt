cmake_minimum_required(VERSION 3.20)
project(my_list)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(my_list
        main.cpp
        My_list.cpp
        My_list.hpp)
