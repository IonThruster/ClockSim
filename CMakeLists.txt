cmake_minimum_required(VERSION 3.10.0)
project(ClockSim VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(include)
add_subdirectory(catch)
add_subdirectory(tests)
