set(HEADER_FILES benchmark_result.hpp 
                 benchmark_runner.hpp 
                 chrono_timer.hpp 
                 clock_timer.hpp
                 )

install(FILES ${HEADER_FILES} 
    DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/pni/core/benchmark)
