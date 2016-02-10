cmake_minimum_required(VERSION 2.8)
project(libpnicore)
#need to define the version of the library
set(MAJOR_VERSION "1")
set(MINOR_VERSION "0")
set(PATCH_VERSION "0")
set(LIBRARY_VERSION "${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION}")

include(CTest)
include(CPackComponent)

set(CMAKE_FAMILY_VERSION "${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}")

if(NOT CMAKE_BUILD_TYPE)
    message("No build type specified - default is RELEASE")
    set(CMAKE_BUILD_TYPE RELEASE)
endif()

#===========================provide some user options==========================
option(BOOST_PREFIX "installation prefix of the local BOOST installation" "/usr")
set(BOOST_ROOT CACHE PATH "Prefix of the Boost installation")
set(BOOST_INCLUDEDIR CACHE PATH "Path to the Boost header files")
set(BOOST_LIBRARYDIR CACHE PATH "Path to the Boost runtime libraries")

#======================do here some setup work=================================
include(configure/CMakeLists.txt)


#as libpnicore is in most part a template library and should thus be 
#treated like a static library. In most cases all code using 
#libpnicore has to be rebuilt if something in the headers is changed.
#we thus set the SO version to the package version. This is also 
#the way the boost libraries are packaged.
set(SO_VERSION ${LIBRARY_VERSION})

include_directories("./include")

#need this to get the generated header files into the build.
include_directories("${CMAKE_CURRENT_BINARY_DIR}/include")
add_subdirectory("include")
add_subdirectory("src")
add_subdirectory("doc")
add_subdirectory("test")
add_subdirectory("resources")

#-----------------------------------------------------------------------------
# Configuration for the package generator
#-----------------------------------------------------------------------------
set(CPACK_GENERATOR WIX)
set(CPACK_PACKAGE_VENDOR "DESY")
set(CPACK_VERSION_MAJOR "${MAJOR_VERSION}")
set(CPACK_VERSION_MINOR "${MINOR_VERSION}")
set(CPACK_VERSION_PATCH "${PATCH_VERSION}")

set(CPACK_WIX_PRODUCT_ICON "resources/icon.ico")


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
