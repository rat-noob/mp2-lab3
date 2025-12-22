cmake_minimum_required(VERSION 3.10)

set(Project_name Arth)
project(${Project_name})



set(MP3_LIBRARY "${Project_name}")
set(MP3_TESTS   "test_${Project_name}")
set(MP3_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")

#include_directories("${MP3_INCLUDE}")
include_directories("${MP3_INCLUDE}" gtest)


add_subdirectory(src)
#add_subdirectory(include)
add_subdirectory(test)
add_subdirectory(samples)
add_subdirectory(gtest)
