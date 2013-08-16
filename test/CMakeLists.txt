
#need to define the version of the library
file(GLOB TEST_SOURCES *.cpp)

link_directories("${CMAKE_CURRENT_BINARY_DIR}/../src")
add_executable(pnicoretest ${TEST_SOURCES})
target_link_libraries(pnicoretest pnicore cppunit)
configure_file(pni.cfg.cmake pni.cfg)

