if((NOT TARGET Boost::system) AND (NOT TARGET Boost::program_options))
	
	set(Boost_USE_MULTITHREADED ON)
	set(Boost_USE_STATIC_RUNTIME OFF)
	find_package(Boost 1.41 REQUIRED COMPONENTS program_options system)
	if(NOT Boost_FOUND)
		message(FATAL_ERROR "Could not find boost libraries - you may have to set the BOOST_ROOT variable!")		
	endif()	
endif()
link_directories(${Boost_LIBRARY_DIRS})
include(${CMAKE_CURRENT_LIST_DIR}/pnicore_targets.cmake)

#we create a list of files which need to be installed on windows
if(CMAKE_SYSTEM_NAME MATCHES Windows)
	set(pnicore_REQUIRED_INSTALL_FILES)
	
	get_target_property(FILE_NAME pnicore_shared LOCATION)
	list(APPEND pnicore_REQUIRED_INSTALL_FILES ${FILE_NAME})


	get_target_property(FILE_NAME Boost::program_options LOCATION)
	string(REPLACE ".lib" ".dll" FILE_NAME ${FILE_NAME} )
	list(APPEND pnicore_REQUIRED_INSTALL_FILES ${FILE_NAME})

	get_target_property(FILE_NAME Boost::system LOCATION)
	string(REPLACE ".lib" ".dll" FILE_NAME ${FILE_NAME})
	list(APPEND pnicore_REQUIRED_INSTALL_FILES ${FILE_NAME})

	message(STATUS "The following files should be installed along with the product")
	foreach(F ${pnicore_REQUIRED_INSTALL_FILES})
		message(STATUS ${F})
	endforeach()
	
endif()