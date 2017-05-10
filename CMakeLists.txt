cmake_minimum_required(VERSION 3.0)
project(pnicore
        LANGUAGES CXX C
        VERSION 1.0.0)

include(CTest) # - activate testing

#
#as libpnicore is in most part a template library and should thus be 
#treated like a static library. In most cases all code using 
#libpnicore has to be rebuilt if something in the headers is changed.
#we thus set the SO version to the package version. This is also 
#the way the boost libraries are packaged.
#
set(SO_VERSION ${PROJECT_VERSION})

#
# for windows we need two additional components 
# - we have to build an MSI package for installation
# - we need to add a package configuration file so that the library
#   can be found with the find_package command
#
if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    include(CPackComponent)
    include(CMakePackageConfigHelpers)
endif()


#
# set the default build type
# 
if(NOT CMAKE_BUILD_TYPE)
    message("No build type specified - default is RELEASE")
    set(CMAKE_BUILD_TYPE RELEASE)
endif()

#===========================provide some user options==========================
option(BOOST_PREFIX "installation prefix of the local BOOST installation" "/usr")
set(BOOST_ROOT CACHE PATH "Prefix of the Boost installation")
set(BOOST_INCLUDEDIR CACHE PATH "Path to the Boost header files")
set(BOOST_LIBRARYDIR CACHE PATH "Path to the Boost runtime libraries")
set(BUILD_SHARED_LIBRARIES ON CACHE BOOL "Build shared libraries")
set(BUILD_STATIC_LIBRARIES ON CACHE BOOL "Build static libraries")

#======================do here some setup work=================================
include(configure/CMakeLists.txt)


#need this to get the generated header files into the build.
add_subdirectory("include")
add_subdirectory("src")
add_subdirectory("doc")
add_subdirectory("test")
add_subdirectory("resources")

#-----------------------------------------------------------------------------
# Configuration for the package generator
#-----------------------------------------------------------------------------
if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    #for windows we also create a cmake config package    
    write_basic_package_version_file(
        "${PROJECT_BINARY_DIR}/libpnicore-config-version.cmake"
        VERSION ${LIBRARY_VERSION}
        COMPATIBILITY AnyNewerVersion)
    

    set(CPACK_GENERATOR WIX)
    set(CPACK_PACKAGE_VENDOR "DESY")
    set(CPACK_PACKAGE_VERSION_MAJOR "1")
    set(CPACK_PACKAGE_VERSION_MINOR "0")
    set(CPACK_PACKAGE_VERSION_PATCH "0")
    

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



    include(CPack)
    include(CPackWIX)
endif()
