include(CheckTypeSize)

#check the size of data types
check_type_size(uint8_t UINT8_SIZE)
check_type_size(int8_t INT8_SIZE)
check_type_size(uint16_t UINT16_SIZE)
check_type_size(int16_t INT16_SIZE)
check_type_size(uint32_t UINT32_SIZE)
check_type_size(int32_t INT32_SIZE)
check_type_size(uint64_t UINT64_SIZE)
check_type_size(int64_t INT64_SIZE)
check_type_size(float FLOAT32_SIZE)
check_type_size(double FLOAT64_SIZE)

#need to check for several libraries if they are installed
find_library(BOOST_OPTIONS_SEARCH boost_program_options PATHS "${BOOST_PREFIX}/lib")
if(NOT BOOST_OPTIONS_SEARCH)
    message(FATAL_ERROR "boost_program_options library not found!")
endif(NOT BOOST_OPTIONS_SEARCH)

find_library(BOOST_SYSTEM_SEARCH boost_system PATHS "${BOOST_PREFIX}/lib")
if(NOT BOOST_SYSTEM_SEARCH)
    message(FATAL_ERROR "boost_system library not found!")
endif(NOT BOOST_SYSTEM_SEARCH)

find_library(BOOST_REGEX_SEARCH boost_regex PATHS "${BOOST_PREFIX}/lib")
if(NOT BOOST_REGEX_SEARCH)
    message(FATAL_ERROR "boost_regex library not found!")
endif(NOT BOOST_REGEX_SEARCH)
