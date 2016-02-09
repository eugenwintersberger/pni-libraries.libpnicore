#need to define the version of the library
set(SOURCES  configuration_test.cpp)


link_directories("${CMAKE_CURRENT_BINARY_DIR}/../../src")
add_executable(config_test EXCLUDE_FROM_ALL ${SOURCES} $<TARGET_OBJECTS:test_common>)
target_link_libraries(config_test pnicore)

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    target_link_libraries(config_test ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
endif()

configure_file(pni.cfg.cmake pni.cfg)

add_test(NAME config_test 
         COMMAND config_test
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../
         )

add_dependencies(check config_test)
