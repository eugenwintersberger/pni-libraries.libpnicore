cmake_minimum_required(VERSION 2.6)

project(PNIIO)
set(CMAKE_VERBOSE_MAKEFILE ON)

#===========================provide some user options==========================
option(BOOST_PREFIX "installation prefix of the local BOOST installation" "/usr")

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

#need to check for several libraries if they are installed
find_library(BOOST_OPTIONS_SEARCH xboost_program_options PATHS "${BOOST_PREFIX}/lib")
if(NOT BOOST_OPTIONS_SEARCH)
    message(FATAL_ERROR "boost_program_options library not found!")
endif(NOT BOOST_OPTIONS_SEARCH)

find_library(BOOST_SYSTEM_SEARCH boost_system PATHS "${BOOST_PREFIX}/lib")
if(NOT BOOST_SYSTEM_SEARCH)
    message(FATAL_ERROR "boost_system library not found!")
endif(NOT BOOST_SYSTEM_SEARCH)

find_library(BOOST_REGEX_SEARCH boost_regex PATHS "${BOOST_PREFIX}/lib")
if(NOT BOOST_REGEX_SEARCH)
    message(FATAL_ERROR "boost_regex library not found!")
endif(not BOOST_REGEX_SEARCH)

add_subdirectory(src)

