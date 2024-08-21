cmake_minimum_required(VERSION 3.29)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

project(tui)

add_subdirectory(./src)
add_subdirectory(./test)