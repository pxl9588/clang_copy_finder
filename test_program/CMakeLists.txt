cmake_minimum_required(VERSION 3.22)

project(test-program LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_executable(test-program main.cpp)
install(
    TARGETS test-program
    DESTINATION bin)