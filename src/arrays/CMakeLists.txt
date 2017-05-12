set(SOURCES array_selection.cpp 
            slice.cpp)

add_library(array_objects OBJECT ${SOURCES})
set_property(TARGET array_objects PROPERTY POSITION_INDEPENDENT_CODE ON)
target_include_directories(array_objects PUBLIC
                           $<BUILD_INTERFACE: ${Boost_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE: ${CMAKE_INSTALL_INCLUDEDIR}>)
target_compiler_features(array_objects PRIVATE cxx_std_11)                           

