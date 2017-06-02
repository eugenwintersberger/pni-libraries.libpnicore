cmake_minimum_required(VERSION 3.0)
project(pnicore
        LANGUAGES CXX C
        VERSION 1.0.0)

include(CTest)             # - activate testing
set(CMAKE_CXX_STANDARD 11) # - we need C++11 for the entire code

#
# On linux it is mandatory to provide a build type during configuration
#
if(NOT CMAKE_BUILD_TYPE)
    message(MESSAGE "We only support single configuration builds!")
    message(FATAL_ERROR "CMAKE_BUILD_TYPE must be provided during configuration")
endif()

#
#as libpnicore is in most part a template library and should thus be
#treated like a static library. In most cases all code using
#libpnicore has to be rebuilt if something in the headers is changed.
#we thus set the SO version to the package version. This is also
#the way the boost libraries are packaged.
#
set(pnicore_SO_VERSION ${pnicore_VERSION})


# =============================================================================
# on Windows we try to fetch Boost by default from Conan
# =============================================================================
if(CMAKE_HOST_SYSTEM_NAME MATCHES Windows)
    set(PNICORE_CONAN_BOOST ON CACHE BOOL "Installing depdencies from Conan")
else()
    set(PNICORE_CONAN_BOOST OFF CACHE BOOL "Installing depdencies from Conan")
endif()

if(PNICORE_CONAN_BOOST)

    find_program(CONAN conan)
    if(CONAN MATCHES "CONAN-NONFOUND")
        message(FATAL_ERROR "Could not find conan executable to install dependencies")
    endif()

    if(NOT EXISTS ${PROJECT_BINARY_DIR}/conan.cmake)
        message(STATUS "Downloading conan.cmake file from github")
        file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
             ${PROJECT_BINARY_DIR}/conan.cmake)
    endif()

    include(${PROJECT_BINARY_DIR}/conan.cmake)

    conan_cmake_run(REQUIRES "Boost/1.62.0@lasote/stable"
                    BASIC_SETUP
                    OPTIONS "Boost:shared=True"
                    IMPORTS "bin, *.dll -> bin"
                    BUILD missing)

endif()



#
# for windows we need two additional components
# - we have to build an MSI package for installation
# - we need to add a package configuration file so that the library
#   can be found with the find_package command
# the packaging is independent of the compiler used thus we have to check the
# system name.
#
if(CMAKE_SYSTEM_NAME MATCHES Windows)
    include(CPackComponent)
endif()

# =============================================================================
# setting up the output directory for library, archive and runtime targets
#
# This should be the same on all platforms just to avoid confusion
# =============================================================================
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHVIE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

#======================do here some setup work=================================
include(configure/CMakeLists.txt)


#need this to get the generated header files into the build.
add_subdirectory("include")
add_subdirectory("src")
add_subdirectory("doc")
add_subdirectory("test")
add_subdirectory("resources")
add_subdirectory("cmake")

#-----------------------------------------------------------------------------
# Configuration for the package generator
#-----------------------------------------------------------------------------
if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)


    set(CPACK_GENERATOR WIX)
    set(CPACK_PACKAGE_VENDOR "DESY")
    set(CPACK_PACKAGE_VERSION_MAJOR "${pnicore_VERSION_MAJOR}")
    set(CPACK_PACKAGE_VERSION_MINOR "${pnicore_VERSION_MINOR}")
    set(CPACK_PACKAGE_VERSION_PATCH "${pnicore_VERSION_PATCH}")


    set(CPACK_WIX_PRODUCT_ICON "resources/icon.ico")
    set(CPACK_WIX_UI_BANNER "resources/banner.bmp")
    set(CPACK_WIX_UI_DIALOG "resources/ui_dialog.bmp")
    set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/COPYING.txt")


    cpack_add_component(libraries
        DISPLAY_NAME "Libraries"
        DESCRIPTION "Runtime libraries"
        GROUP "Runtime")


    cpack_add_component(development
        DISPLAY_NAME "Development files"
        DESCRIPTION "Header files for the library"
        DEPENDS "libraries"
        GROUP "Development")

    cpack_add_component(doc_html
        DISPLAY_NAME "HTML"
        DESCRIPTION "Documentation as HTML pages"
        GROUP "Documentation")

    cpack_add_component(doc_examples
        DISPLAY_NAME "Examples"
        DESCRIPTION "Usage examples for the library"
        GROUP "Documentation")

    cpack_add_component(doc_pdf
        DISPLAY_NAME "PDF"
        DESCRIPTION "Documentation as PDF"
        GROUP "Documentation")

    cpack_add_component_group(Documentation)

    set(CPACK_WIX_CMAKE_PACKAGE_REGISTRY "pnicore")

    include(CPack)
    include(CPackWIX)
endif()
