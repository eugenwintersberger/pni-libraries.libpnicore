
#need to define the version of the library
file(GLOB TEST_SOURCES *.cpp)

link_directories("${CMAKE_CURRENT_BINARY_DIR}/../src")
add_executable(pnicoretest ${TEST_SOURCES})
target_link_libraries(pnicoretest pnicore)

if(CPPUNIT_FOUND)
    #add include directories
    include_directories(${CPPUNIT_INCLUDE_DIRS})

    #add libraries
    target_link_libraries(pnicoretest ${CPPUNIT_LIBRARIES})

endif()

if("${CMAKE_FAMILY_VERSION}" EQUAL "2.6")
    configure_file(pni.cfg.cmake ./test/pni.cfg)
else()
    configure_file(pni.cfg.cmake pni.cfg)
endif()

