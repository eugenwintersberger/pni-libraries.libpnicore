#
# manage header files
#
set(HEADER_FILES benchmark_result.hpp 
                 benchmark_runner.hpp 
                 chrono_timer.hpp 
                 clock_timer.hpp
                 )

install(FILES ${HEADER_FILES} 
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/core/benchmark
    COMPONENT development)
add_doxygen_source_deps(${HEADER_FILES})

#
# build submodule
#
set(SOURCES benchmark_result.cpp
            benchmark_runner.cpp
            chrono_timer.cpp
            clock_timer.cpp
   )


add_library(benchmark_objects OBJECT ${SOURCES})
set_property(TARGET benchmark_objects PROPERTY POSITION_INDEPENDENT_CODE ON)
target_include_directories(benchmark_objects PUBLIC
                           $<BUILD_INTERFACE: ${Boost_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE: ${CMAKE_INSTALL_INCLUDEDIR}>)