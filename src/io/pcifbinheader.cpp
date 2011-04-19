/*
 * pcifbinheader.cpp
 *
 *  Created on: Apr 19, 2011
 *      Author: Eugen Wintersberger
 */

//implementation of class PCIFBinaryHeader

#include<iostream>
#include<string>

#include "cbf.hpp"
#include "strutils.hpp"

PCIFBinaryHeader::PCIFBinaryHeader(std::ifstream &stream){
    unsigned char byte;
    std::string linebuffer;
    std::string key;
    std::string value;

    //set some initial values
    ndims_ = 0;

    linebuffer.empty();
    byte = stream.get();
    do
    {
        if((byte == '\n')&&(!linebuffer.empty())){
            linebuffer = strip(linebuffer);
            get_key_value(linebuffer,":= ",key,value);

            if(key=="conversions"){
                if(value == "\"x-CBF_BYTE_OFFSET\""){
                    converion_id_ = CONVERSION_BYTE_OFFSET;
                }
                linebuffer.clear();
                continue; //there is nothing more to do here
            }

            if(key == CIF_DATA_TYPE_KEY){
                if(value == CIF_DATA_SIGNED_INT32) data_type_ = SIGNED_INT_32;

                linebuffer.clear();
                continue;
            }

            if(key == CIF_DATA_BYTE_ORDER_KEY){
                if(value == "LITTLE ENDIAN"){
                    byte_order_ = BYTE_ORDER_LITTLE_ENDIAN;
                }else{
                    byte_order_ = BYTE_ORDER_BIG_ENDIAN;
                }
                linebuffer.clear();
                continue;
            }

            if(key == CIF_DATA_NELEMENTS_KEY){
                nofelements_ = (unsigned long)std::atoi(value.data());
                linebuffer.clear();
                continue;
            }

            if(key==CIF_DATA_1FAST_DIM_KEY){
                dims_[2] = (unsigned long)std::atoi(value.data());
                //increase the rank counter
                ndims_++;
                linebuffer.clear();
                continue; //there is nothing more to do here
            }

            if(key==CIF_DATA_2FAST_DIM_KEY){
                dims_[1] = (unsigned long)std::atoi(value.data());
                //increase the rank counter
                ndims_++;
                linebuffer.clear();
                continue; //there is nothing more to do here
            }

            if(key==CIF_DATA_3FAST_DIM_KEY){
                dims_[0] = (unsigned long)std::atoi(value.data());
                //increase the rank counter
                ndims_++;
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
