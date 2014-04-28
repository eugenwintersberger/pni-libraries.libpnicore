#need to define the version of the library
set(SOURCES config_test.cpp configuration_test.cpp)


link_directories("${CMAKE_CURRENT_BINARY_DIR}/../../src")
add_executable(config_test ${SOURCES} $<TARGET_OBJECTS:test_common>)

target_link_libraries(config_test pnicore)

if(CPPUNIT_FOUND)
    #add include directories
    include_directories(${CPPUNIT_INCLUDE_DIRS})

    #add libraries
    target_link_libraries(config_test ${CPPUNIT_LIBRARIES})

endif()

if("${CMAKE_FAMILY_VERSION}" EQUAL "2.6")
    configure_file(pni.cfg.cmake ./test/config/pni.cfg)
else()
    configure_file(pni.cfg.cmake pni.cfg)
endif()

message(${CMAKE_CURRENT_BINARY_DIR})
add_test(NAME config_test 
         COMMAND config_test
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../
         )
