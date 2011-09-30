/*
 * Implementation of class PCIFBinHeader
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
 * Implementation of class PCIFBinHeader declared in CBFHeader.hpp.
 * This is a special header as written by the Pilatus detector manufactured
 * by DECTRIS.
 *
 * Created on: Apr 19, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<cstdio>
#include<cstdlib>

#include "CBFHeader.hpp"
#include "CBFBinStreamReader.hpp"
#include "CBFBOReaders.hpp"
#include "strutils.hpp"

namespace pni{
namespace utils{


PCIFBinaryHeader::PCIFBinaryHeader(std::ifstream &stream){
    unsigned char byte;
    std::string linebuffer;
    std::string key;
    std::string value;

    //set some initial values
    _ndims = 0;

    linebuffer.empty();
    byte = stream.get();
    do
    {
        if((byte == '\n')&&(!linebuffer.empty())){
            linebuffer = strip(linebuffer);
            get_key_value(linebuffer,":= ",key,value);

            if(key=="conversions"){
                if(value == "\"x-CBF_BYTE_OFFSET\""){
                    _conversion_id = CONVERSION_BYTE_OFFSET;
                }
                linebuffer.clear();
                continue; //there is nothing more to do here
            }

            if(key == CIF_DATA_TYPE_KEY){
                if(value == CIF_DATA_SIGNED_INT32) _data_type = SIGNED_INT_32;

                linebuffer.clear();
                continue;
            }

            if(key == CIF_DATA_BYTE_ORDER_KEY){
                if(value == "LITTLE ENDIAN"){
                    _byte_order = BYTE_ORDER_LITTLE_ENDIAN;
                }else{
                    _byte_order = BYTE_ORDER_BIG_ENDIAN;
                }
                linebuffer.clear();
                continue;
            }

            if(key == CIF_DATA_NELEMENTS_KEY){
                _nofelements = (unsigned long)std::atoi(value.data());
                linebuffer.clear();
                continue;
            }

            if(key==CIF_DATA_1FAST_DIM_KEY){
                _dims[2] = (unsigned long)std::atoi(value.data());
                //increase the rank counter
                _ndims++;
                linebuffer.clear();
                continue; //there is nothing more to do here
            }

            if(key==CIF_DATA_2FAST_DIM_KEY){
                _dims[1] = (unsigned long)std::atoi(value.data());
                //increase the rank counter
                _ndims++;
                linebuffer.clear();
                continue; //there is nothing more to do here
            }

            if(key==CIF_DATA_3FAST_DIM_KEY){
                _dims[0] = (unsigned long)std::atoi(value.data());
                //increase the rank counter
                _ndims++;
                linebuffer.clear();
                continue; //there is nothing more to do here
            }



            //finally clear the linebuffer
            linebuffer.clear();
        }else{
            linebuffer += byte;
        }
        byte = stream.get();
    }while((!stream.eof())&&(
           !((byte=='\r')&&(linebuffer.empty())))
           );

}

CBFBinStreamReader *PCIFBinaryHeader::createBinaryReader(){
	//have to select the proper stream reader
	//using the header information

	switch(_conversion_id){
	case CONVERSION_BYTE_OFFSET:
		switch(_data_type){
		case SIGNED_INT_16: return (new CBFBinStreamBOInt16(_nofelements));
		case SIGNED_INT_32: return (new CBFBinStreamBOInt32(_nofelements));
		default: return NULL;
		}
		break;
	default:
		return NULL;
	}
}

//end of namespace
}
}

