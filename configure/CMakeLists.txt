include(CheckTypeSize)
include(CheckCXXSourceCompiles)
include(CheckCXXCompilerFlag)

#==========need to check for several libraries if they are installed===========

# boost parameters common to all platforms
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

set(Boost_USE_STATIC_LIBS OFF)
find_package(Boost 1.41 REQUIRED COMPONENTS program_options
                                            system
                                            unit_test_framework)

message(STATUS "Found shared libraries for Boost")
message(STATUS "Unit test framework: ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}")
message(STATUS "System: ${Boost_SYSTEM_LIBRARY}")
message(STATUS "Program Options: ${Boost_PROGRAM_OPTIONS_LIBRARY}")

link_directories(${Boost_LIBRARY_DIRS})
add_definitions(${Boost_LIB_DIAGNOSTIC_DEFINITIONS})

#======================compiler specific configuration========================
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    #=========================================================================
    #setup for GNU CXX compiler
    #=========================================================================
    message("found GNU compiler ...")
    #setup some default compiler flags
    add_compile_options(-Wextra -pedantic -Wall -Wno-psabi)
    if(CMAKE_BUILD_TYPE MATCHES RELEASE)
        message("setup for release build ...")
        add_compile_options(-O3 -g)
    elseif(CMAKE_BUILD_TYPE MATCHES DEBUG)
        message("setup for debug build ...")
        add_compile_options(-O0 -g -fno-inline)
        add_definitions(-DDEBUG)
    endif()

elseif(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    #=========================================================================
    #setup for the Microsoft C++ compiler
    #=========================================================================
    message(STATUS "found Microsoft C++ compiler ...")
    add_definitions(-DBOOST_ALL_DYN_LINK)
    add_definitions(-DDLL_BUILD)

elseif(CMAKE_CXX_COMPILER_ID MATCHES Clang)
    #=========================================================================
    #setup for Clang
    #=========================================================================

    message("found clang compliler...")

    add_compile_options(-Wextra -pedantic -Wall)
    if(CMAKE_BUILD_TYPE MATCHES RELEASE)
        message("setup for release build ...")
        add_compile_options(-O3 -g)
    elseif(CMAKE_BUILD_TYPE MATCHES DEBUG)
        message("setup for debug build ...")
        add_compile_options(-O0 -g -fno-inline)
        add_definitions(-DDEBUG)
    endif()

endif()

#===================================check the size of data types===============
include(configure/CheckTypeSizes.cmake)
