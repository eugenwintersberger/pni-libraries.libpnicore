include(CheckTypeSize)
include(CheckCXXSourceCompiles)
include(CheckCXXCompilerFlag)
include(FindBoost)

if(CMAKE_HOST_UNIX)
    include(FindPkgConfig)
    include(GNUInstallDirs)

    if(NOT PKG_CONFIG_FOUND)
        message("Could not find pkg-config ... try without it!")
    endif()
else()
    set(CMAKE_INSTALL_FULL_LIBDIR ${CMAKE_INSTALL_PREFIX}/lib)
    message("Installation path for Windows: ${CMAKE_INSTALL_FULL_LIBDIR}")
endif()

#==========need to check for several libraries if they are installed===========

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)
find_package(Boost 1.41 REQUIRED 
             COMPONENTS program_options 
                        system 
                        regex 
                        unit_test_framework)

message(STATUS "${Boost_LIBRARY_DIRS}")
link_directories(${Boost_LIBRARY_DIRS})
add_definitions(${Boost_LIB_DIAGNOSTIC_DEFINITIONS})

#======================compiler specific configuration========================   
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    #=========================================================================
    #setup for GNU CXX compiler
    #=========================================================================
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
    add_definitions(-DGCC)

elseif(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    #=========================================================================
    #setup for the Microsoft C++ compiler 
    #=========================================================================
    message(STATUS "found Microsoft C++ compiler ...") 
    add_definitions(-DMSVC)
    add_definitions(-DBOOST_ALL_DYN_LINK)
    
elseif(CMAKE_CXX_COMPILER_ID MATCHES Clang)
    #=========================================================================
    #setup for Clang
    #=========================================================================

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
    add_definitions(-DCLANG)
endif()


if()
endif()

#===================================check the size of data types===============
include(configure/CheckTypeSizes.txt)

