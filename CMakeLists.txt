cmake_minimum_required(VERSION 3.16)
project(jvm_demo1)

set(CMAKE_CXX_STANDARD 17)

set(SRC_LISTS main.cpp class_file.hpp general_def.hpp class_file_stream.cpp class_file_stream.hpp bytes_x86.hpp)

add_executable(jvm_demo1 ${SRC_LISTS})