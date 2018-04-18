cmake_minimum_required(VERSION 3.5)
project(Actuators)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Relay.cpp)
add_executable(Actuators ${SOURCE_FILES})