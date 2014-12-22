set(SOURCES benchmark_result.cpp
            benchmark_runner.cpp
            chrono_timer.cpp
            clock_timer.cpp
   )

add_library(benchmark_objects OBJECT ${SOURCES})
