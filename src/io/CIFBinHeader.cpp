/*
 * Implementation of class CIFBinHeader
 *
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniutils.
 *
 * libpniutils is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniutils is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Implementation of class CIFBinHeader declared in CBFHeader.hpp
 *
 * Created on: Apr 19, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#include<iostream>

#include "CBFHeader.hpp"
#include "../DataObject.hpp"
#include "../Array.hpp"

namespace pni{
namespace utils{

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

ArrayObject *CIFBinaryHeader::createArray(){
	Shape s;
	s.rank(_ndims);
	for(UInt32 i=0;i<_ndims;i++){
		//std::cout<<_dims[2-i]<<std::endl;
		s.dim(_ndims-1-i,_dims[2-i]);
	}

	switch(_data_type){
	case(SIGNED_INT_32): return (ArrayObject*)(new Array<Int32>(s)); break;
	case(SIGNED_INT_16): return (ArrayObject*)(new Array<Int16>(s)); break;
	default: return NULL;
	}

}

//end of namespace
}
}


