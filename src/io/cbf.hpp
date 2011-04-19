
#ifndef __CBF_HPP__
#define __CBF_HPP__


#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdio>
#include<cstdlib>


#define CIF_DATA_TYPE_KEY  "X-Binary-Element-Type"
#define CIF_DATA_SIGNED_INT32  "\"signed 32-bit integer\""
#define UNSIGNED_INT_8 1
#define SIGNED_INT_8 2
#define UNSIGNED_INT_16 3
#define SIGNED_INT_16 4
#define UNSIGNED_INT_32 5
#define SIGNED_INT_32 6
#define UNSIGNED_INT_64 7
#define SIGNED_INT_64 8

#define CIF_DATA_BYTE_ORDER_KEY  "X-Binary-Element-Byte-Order"
#define BYTE_ORDER_LITTLE_ENDIAN 1
#define BYTE_ORDER_BIG_ENDIAN 2

#define CIF_DATA_CONVERSION_KEY  "conversions"
#define CIF_DATA_CONVERSION_BO_VALUE  "\"x-CBF_BYTE_OFFSET\""
#define CONVERSION_BYTE_OFFSET 1

#define CIF_DATA_1FAST_DIM_KEY  "X-Binary-Size-Fastest-Dimension"
#define CIF_DATA_2FAST_DIM_KEY  "X-Binary-Size-Second-Dimension"
#define CIF_DATA_3FAST_DIM_KEY  "X-Binary-Size-Third-Dimension"
#define CIF_DATA_NELEMENTS_KEY  "X-Binary-Number-of-Elements"








#endif
