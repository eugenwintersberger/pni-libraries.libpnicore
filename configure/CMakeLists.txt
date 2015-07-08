include(GNUInstallDirs)
include(CheckTypeSize)
include(CheckCXXSourceCompiles)
include(CheckCXXCompilerFlag)
include(FindBoost)
include(FindPkgConfig)

message("Installation path: ${CMAKE_INSTALL_LIBDIR}")
message("Architecture: ${CMAKE_LIBRARY_ARCHITECTURE}")

if(NOT PKG_CONFIG_FOUND)
    message("Could not find pkg-config ... try without it!")
endif()
   
#setup for GNU CXX compiler
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message("found GNU compiler ...")
    #setup some default compiler flags
    add_definitions(-Wextra -pedantic -Wall -Wno-psabi)
    if(CMAKE_BUILD_TYPE MATCHES RELEASE)
        message("setup for release build ...")
        add_definitions(-O3 -g)
    elseif(CMAKE_BUILD_TYPE MATCHES DEBUG)
        message("setup for debug build ...")
        add_definitions(-O0 -g -fno-inline -DDEBUG)
    endif()

    #for this version the compiler has to support c++11 flag
    add_definitions(-std=c++11)
    add_definitions(-DCOMPILER=GCC)
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message("found clang compliler...")

    add_definitions(-Wextra -pedantic -Wall)
    if(CMAKE_BUILD_TYPE MATCHES RELEASE)
        message("setup for release build ...")
        add_definitions(-O3 -g)
    elseif(CMAKE_BUILD_TYPE MATCHES DEBUG)
        message("setup for debug build ...")
        add_definitions(-O0 -g -fno-inline -DDEBUG)
    endif()

    #for this version the compiler has to support c++11 flag
    add_definitions(-std=c++11)
    add_definitions(-DCOMPILER=CLANG)
endif()

#===================================check the size of data types===============
include(configure/CheckTypeSizes.txt)

#==========need to check for several libraries if they are installed=============

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED OFF)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.41 COMPONENTS program_options system regex)

if(PKG_CONFIG_FOUND)
    pkg_search_module(CPPUNIT REQUIRED cppunit)
endif()

