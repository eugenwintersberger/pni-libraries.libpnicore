#need to define the version of the library

if(CPPUNIT_FOUND)
    #add include directories
    include_directories(${CPPUNIT_INCLUDE_DIRS})

endif()
add_subdirectory(value)
add_subdirectory(value_ref)
add_subdirectory(array)


