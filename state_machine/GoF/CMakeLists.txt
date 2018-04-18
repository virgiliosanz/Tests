cmake_minimum_required(VERSION 3.5)
project(GoF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(SOURCE_FILES main.cpp machine.cpp)
add_executable(GoF ${SOURCE_FILES})