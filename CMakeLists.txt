cmake_minimum_required(VERSION 3.13)
project(pbr)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-Wall -Wno-write-strings -ggdb -pg -O0 -D_GLIBCXX_DEBUG")
message("CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}")

file(GLOB SOURCES "src/*.cpp")
include_directories(include)
add_executable(pbr ${SOURCES})