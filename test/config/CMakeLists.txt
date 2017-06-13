#need to define the version of the library
set(SOURCES  configuration_test.cpp)

set_boost_test_definitions(SOURCES "testing the configuration facilities")
add_executable(config_test ${SOURCES} $<TARGET_OBJECTS:test_common>)
target_link_libraries(config_test pnicore_shared Boost::unit_test_framework)

configure_file(pni.cfg.cmake pni.cfg)

add_boost_logging_test("config_test" config_test ${PROJECT_BINARY_DIR}/test/config)
