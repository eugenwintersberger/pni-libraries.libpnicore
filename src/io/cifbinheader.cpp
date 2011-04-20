/*
 * cifbinheader.cpp
 *
 *  Created on: Apr 19, 2011
 *      Author: Eugen Wintersberger
 */

//implementation of class CIFBinHeader

#include<iostream>

#include "cbfheader.hpp"
#include "../datavalue.hpp"
#include "../array.hpp"

std::ostream &operator<<(std::ostream &o,const CIFBinaryHeader &h){
    long i;

    o<<"CIF Binary header information"<<std::endl;
    o<<"Data type: ";
    switch(h._data_type){
        case SIGNED_INT_32:
            o<<"32Bit signed integer";
            break;
    }
    o<<std::endl<<"Byte order: ";
    switch(h._byte_order){
        case BYTE_ORDER_BIG_ENDIAN:
            o<<"big endian";break;
        case BYTE_ORDER_LITTLE_ENDIAN:
            o<<"little endian";break;
    }
    o<<std::endl<<"Compression: ";
    switch(h._conversion_id){
        case CONVERSION_BYTE_OFFSET:
            o<<"byte offset compression";break;
    }
    o<<std::endl<<"Dimensions "<<h._ndims<<" (from fastest to slowest): ";
    for(i=2;i>=3-(long)h._ndims;i--){
        o<<h._dims[i]<<" ";
    }
    o<<std::endl<<"Total number of elements: "<<h._nofelements;

    return o;
}

DataValue *CIFBinaryHeader::createArray(){
	unsigned int *dims;
	dims = new unsigned int[_ndims];
	for(unsigned int i=0;i<_ndims;i++){
		std::cout<<_dims[2-i]<<std::endl;
		dims[i]=_dims[2-i];
	}

	switch(_data_type){
	case(SIGNED_INT_32): return new Array<int>(_ndims,dims); break;
	case(SIGNED_INT_16): return new Array<short>(_ndims,dims); break;
	default: return NULL;
	}

	delete [] dims;
}



