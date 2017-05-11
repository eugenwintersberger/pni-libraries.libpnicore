set(SOURCES array.cpp value.cpp value_ref.cpp )

add_library(type_erasure_objects OBJECT ${SOURCES})
set_property(TARGET type_erasure_objects PROPERTY POSITION_INDEPENDENT_CODE ON)
target_include_directories(type_erasure_objects PUBLIC
                           $<BUILD_INTERFACE:${Boost_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

