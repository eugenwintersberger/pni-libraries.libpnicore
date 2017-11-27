#
# manage header files
#
set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/benchmark_result.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/benchmark_runner.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/chrono_timer.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/clock_timer.hpp
                 )

install(FILES ${HEADER_FILES} 
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/core/benchmark
    COMPONENT development)
add_doxygen_source_deps(${HEADER_FILES})

#
# build submodule
#
set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/benchmark_result.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/benchmark_runner.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/chrono_timer.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/clock_timer.cpp
   )


set(PNICORE_LIBRARY_SOURCES ${PNICORE_LIBRARY_SOURCES} ${SOURCES} PARENT_SCOPE)
set(PNICORE_LIBRARY_HEADERS ${PNICORE_LIBRARY_HEADERS} ${HEADER_FILES} PARENT_SCOPE)