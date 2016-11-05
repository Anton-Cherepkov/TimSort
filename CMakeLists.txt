cmake_minimum_required(VERSION 3.6)
project(TimSort)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp include/run.h include/inplace_merge.h include/timsort.h include/test.h include/timsort_params.h include/utils.h)
add_executable(TimSort ${SOURCE_FILES})