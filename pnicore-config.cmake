# if the required Boost targets do not exist we have to add them 
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
