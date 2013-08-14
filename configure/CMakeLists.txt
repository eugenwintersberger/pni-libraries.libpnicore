include(CheckTypeSize)

#check the size of data types
check_type_size(uint8_t UINT8_SIZE)
if(NOT ${UINT8_SIZE} EQUAL 1)
    message(FATAL_ERROR "uint8_t size is not 1Byte!")
endif(NOT ${UINT8_SIZE}  EQUAL 1)

check_type_size(int8_t INT8_SIZE)
if(NOT ${INT8_SIZE} EQUAL 1)
    message(FATAL_ERROR "int8_t size is not 1Byte!")
endif(NOT ${INT8_SIZE}  EQUAL 1)

check_type_size(uint16_t UINT16_SIZE)
if(NOT ${UINT16_SIZE} EQUAL 2)
    message(FATAL_ERROR "uint16_t size is not 2Byte!")
endif(NOT ${UINT16_SIZE}  EQUAL 2)

check_type_size(int16_t INT16_SIZE)
if(NOT ${INT16_SIZE} EQUAL 2)
    message(FATAL_ERROR "int16_t size is not 2Byte!")
endif(NOT ${INT16_SIZE}  EQUAL 2)

check_type_size(uint32_t UINT32_SIZE)
if(NOT ${UINT32_SIZE} EQUAL 4)
    message(FATAL_ERROR "uint32_t size is not 4Byte!")
endif(NOT ${UINT32_SIZE}  EQUAL 4)

check_type_size(int32_t INT32_SIZE)
if(NOT ${INT32_SIZE} EQUAL 4)
    message(FATAL_ERROR "int32_t size is not 4Byte!")
endif(NOT ${INT32_SIZE}  EQUAL 4)

check_type_size(uint64_t UINT64_SIZE)
if(NOT ${UINT64_SIZE} EQUAL 8)
    message(FATAL_ERROR "uint64_t size is not 8Byte!")
endif(NOT ${UINT64_SIZE}  EQUAL 8)

check_type_size(int64_t INT64_SIZE)
if(NOT ${INT64_SIZE} EQUAL 8)
    message(FATAL_ERROR "int64_t size is not 8Byte!")
endif(NOT ${INT64_SIZE}  EQUAL 8)

check_type_size(float FLOAT32_SIZE)
if(NOT ${FLOAT32_SIZE} EQUAL 4)
    message(FATAL_ERROR "float size is not 4Byte!")
endif(NOT ${FLOAT32_SIZE}  EQUAL 4)

check_type_size(double FLOAT64_SIZE)
if(NOT ${FLOAT64_SIZE} EQUAL 8)
    message(FATAL_ERROR "double size is not 8Byte!")
endif(NOT ${FLOAT64_SIZE}  EQUAL 8)

check_type_size("long double" FLOAT128_SIZE)
if(NOT ${FLOAT128_SIZE} EQUAL 16)
    message(FATAL_ERROR "long double size is not 16Byte!")
endif(NOT ${FLOAT128_SIZE}  EQUAL 16)


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
