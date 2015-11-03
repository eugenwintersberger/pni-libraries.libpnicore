set(SOURCES benchmark_result.cpp
            benchmark_runner.cpp
            chrono_timer.cpp
            clock_timer.cpp
   )

include_directories(${Boost_INCLUDE_DIR})
add_library(benchmark_objects OBJECT ${SOURCES})
