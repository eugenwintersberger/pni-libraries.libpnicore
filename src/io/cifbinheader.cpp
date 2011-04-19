/*
 * cifbinheader.cpp
 *
 *  Created on: Apr 19, 2011
 *      Author: Eugen Wintersberger
 */

//implementation of class CIFBinHeader

#include<iostream>

#include "cbf.hpp"

std::ostream &operator<<(std::ostream &o,const CIFBinaryHeader &h){
    long i;

    o<<"CIF Binary header information"<<std::endl;
    o<<"Data type: ";
    switch(h.data_type_){
        case SIGNED_INT_32:
            o<<"32Bit signed integer";
            break;
    }
    o<<std::endl<<"Byte order: ";
    switch(h.byte_order_){
        case BYTE_ORDER_BIG_ENDIAN:
            o<<"big endian";break;
        case BYTE_ORDER_LITTLE_ENDIAN:
            o<<"little endian";break;
    }
    o<<std::endl<<"Compression: ";
    switch(h.converion_id_){
        case CONVERSION_BYTE_OFFSET:
            o<<"byte offset compression";break;
    }
    o<<std::endl<<"Dimensions "<<h.ndims_<<" (from fastest to slowest): ";
    for(i=2;i>=3-(long)h.ndims_;i--){
        o<<h.dims_[i]<<" ";
    }
    o<<std::endl<<"Total number of elements: "<<h.nofelements_;

    return o;
}

