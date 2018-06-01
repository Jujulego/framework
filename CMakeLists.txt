cmake_minimum_required(VERSION 3.8)

#
# Options générales
#
project(projet)

set(PROJECT_BINARY_DIR "build")

#
# Options de compilation
#
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g3")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
set(CMAKE_SHARED_LIBRARY_PREFIX "_")
set(CMAKE_SHARED_MODULE_PREFIX "")

#
# Sources
#
include_directories(src)
add_subdirectory(src)
