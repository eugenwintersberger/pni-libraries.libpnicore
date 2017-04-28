set(SOURCES benchmark_result.cpp
            benchmark_runner.cpp
            chrono_timer.cpp
            clock_timer.cpp
   )

include_directories(${Boost_INCLUDE_DIR})

if(BUILD_SHARED_LIBRARIES)
    add_library(benchmark_objects_shared OBJECT ${SOURCES})
    set_property(TARGET benchmark_objects_shared PROPERTY 
                 POSITION_INDEPENDENT_CODE ON)
endif(BUILD_SHARED_LIBRARIES)

if(BUILD_SHARED_LIBRARIES)
    add_library(benchmark_objects_static OBJECT ${SOURCES})
    set_property(TARGET benchmark_objects_static PROPERTY
                 POSITION_INDEPENDENT_CODE OFF)
endif(BUILD_SHARED_LIBRARIES)
