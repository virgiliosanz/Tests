cmake_minimum_required(VERSION 3.5)
project(my)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp machine.cpp MachineState.cpp)
add_executable(my ${SOURCE_FILES})