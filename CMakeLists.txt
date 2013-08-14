cmake_minimum_required(VERSION 2.6)

project(PNIIO)

#do here some setup work
set(GCC_COMPILER_RELEASE_FLAGS "-std=c++11 -O3")
set(GCC_COMPILER_DEBUG_FLAGS "-std=c++11 -O0 -g")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILER_RELEASE_FLAGS}")

add_subdirectory(src)

