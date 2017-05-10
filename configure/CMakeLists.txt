include(CheckTypeSize)
include(CheckCXXSourceCompiles)
include(CheckCXXCompilerFlag)
include(FindBoost)

if((CMAKE_HOST_SYSTEM_NAME MATCHES Linux) AND 
    (CMAKE_SYSTEM_NAME MATCHES Linux))
    # --- if we are building on Linux for Linux ----
    # on the Linux host we rely on the GNUInstallDirs module to 
    # determine the installation paths    
    include(GNUInstallDirs)
    message(STATUS "Installation directories for Linux: ")
    
    set(CMAKE_INSTALL_DOCDIR ${CMAKE_INSTALL_DATAROOTDIR}/doc/${PROJECT_NAME}-${PROJECT_VERSION})
   
elseif(CMAKE_SYSTEM_NAME MATCHES Windows)

    #if we are building for Windows the GNU installation paths do 
    #not make sens (actually the module may not even exists.
    #In this case we set the installation paths manually
    #
    #Please note that on Windows we can only use relative installation 
    #paths. However, we use the same variables as GNUInstallDirs would 
    #use in order to simplify the CMake code. 
    #
    set(CMAKE_INSTALL_LIBDIR lib)
    set(CMAKE_INSTALL_BINDIR bin)
    set(CMAKE_INSTALL_INCLUDEDIR include)
    set(CMAKE_INSTALL_DATAROOTDIR share)
    set(CMAKE_INSTALL_DOCDIR share/doc/${PROJECT_NAME}-${PROJECT_VERSION})
    
    message(STATUS "Installation directories for Windows: ")
    
endif()
    #
    # the installation path the the cmake package file is the same 
    # for both platforms
    #
    set(CMAKE_INSTALL_PACKAGEDIR ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})
    
    if(CMAKE_INSTALL_PREFIX)
        message(STATUS "Prefix is: ${CMAKE_INSTALL_PREFIX}")
    else()
        message(STATUS "Prefix is: unknown")
    endif()
    message(STATUS "Libraries: ${CMAKE_INSTALL_LIBDIR}")
    message(STATUS "Binaries:  ${CMAKE_INSTALL_BINDIR}")
    message(STATUS "Headers :  ${CMAKE_INSTALL_INCLUDEDIR}")
    message(STATUS "Data:      ${CMAKE_INSTALL_DATAROOTDIR}")
    message(STATUS "Docs:      ${CMAKE_INSTALL_DOCDIR}")
    message(STATUS "CMake PKG: ${CMAKE_INSTALL_PACKAGEDIR}")

#==========need to check for several libraries if they are installed===========

# boost parameters common to all platforms
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

#find first the dynamic libraries
if(BUILD_SHARED_LIBRARIES)
    set(Boost_USE_STATIC_LIBS OFF)
    find_package(Boost 1.41 REQUIRED COMPONENTS program_options 
                                                system       
                                                unit_test_framework)
                                                
    set(Boost_UNIT_TEST_FRAMEWORK_SHARED_LIBRARY ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
    set(Boost_SYSTEM_SHARED_LIBRARY ${Boost_SYSTEM_LIBRARY})
    set(Boost_PROGRAM_OPTIONS_SHARED_LIBRARY ${Boost_PROGRAM_OPTIONS_LIBRARY})
    message(STATUS "Found shared libraries for Boost")
    message(STATUS "Unit test framework: ${Boost_UNIT_TEST_FRAMEWORK_SHARED_LIBRARY}")
    message(STATUS "System: ${Boost_SYSTEM_SHARED_LIBRARY}")
    message(STATUS "Program Options: ${Boost_PROGRAM_OPTIONS_SHARED_LIBRARY}")
endif(BUILD_SHARED_LIBRARIES)

if(BUILD_STATIC_LIBRARIES)
    set(Boost_USE_STATIC_LIBS ON)
    find_package(Boost 1.41 REQUIRED COMPONENTS program_options 
                                                system       
                                                unit_test_framework)
                                                
    set(Boost_UNIT_TEST_FRAMEWORK_STATIC_LIBRARY ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
    set(Boost_SYSTEM_STATIC_LIBRARY ${Boost_SYSTEM_LIBRARY})
    set(Boost_PROGRAM_OPTIONS_STATIC_LIBRARY ${Boost_PROGRAM_OPTIONS_LIBRARY})
    message(STATUS "Found static libraries for Boost")
    message(STATUS "Unit test framework: ${Boost_UNIT_TEST_FRAMEWORK_STATIC_LIBRARY}")
    message(STATUS "System: ${Boost_SYSTEM_STATIC_LIBRARY}")
    message(STATUS "Program Options: ${Boost_PROGRAM_OPTIONS_STATIC_LIBRARY}")
endif(BUILD_STATIC_LIBRARIES)

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
endif()


if()
endif()

#===================================check the size of data types===============
include(configure/CheckTypeSizes.txt)

