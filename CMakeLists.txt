cmake_minimum_required(VERSION 2.6)

project(PNIIO)

#======================do here some setup work=================================
#setting the compiler flags
set(GCC_COMPILER_RELEASE_FLAGS "-std=c++11 -O3")
set(GCC_COMPILER_DEBUG_FLAGS "-std=c++11 -O0 -g")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILER_RELEASE_FLAGS}")

#need to define the version of the library
set(MAJOR_VERSION "0")
set(MINOR_VERSION "9")
set(PATCH_VERSION "4")
set(LIBRARY_VERSION "${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION}")
set(SO_VERSION "1")

add_subdirectory(src)

