cmake_minimum_required(VERSION 3.8)

#
# Options générales
#
project(projet)

set(PROJECT_SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set(PROJECT_BINARY_DIR "build")

#
# Options de compilation
#
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g3")

#
# Sources
#
include_directories(src)
add_subdirectory(src)
