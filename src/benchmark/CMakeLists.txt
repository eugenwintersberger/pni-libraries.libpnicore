set(SOURCES benchmark_result.cpp
            benchmark_runner.cpp
            chrono_timer.cpp
            clock_timer.cpp
   )


add_library(benchmark_objects OBJECT ${SOURCES})
set_property(TARGET benchmark_objects PROPERTY POSITION_INDEPENDENT_CODE ON)
target_include_directories(benchmark_objects INTERFACE
                           ${Boost_INCLUDE_DIRS})

