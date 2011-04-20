/*
 * cbfreader.hpp
 *
 *  Created on: Apr 19, 2011
 *      Author: eugen
 */

#ifndef CBFREADER_HPP_
#define CBFREADER_HPP_

#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdio>
#include<cstdlib>

#include "cbfheader.hpp"
#include "../datavalue.hpp"

#define CIF_BINARY_SECTION "--CIF-BINARY-FORMAT-SECTION--"
#define CIF_HEADER_CONVENTION "_array_data.header_convention"
#define CIF_HEADER_CONVENTION_SLS "\"SLS_1.0\""


class CBFReader{
    private:
        std::ifstream *stream_;			 //!< input stream from which to read data
        std::string header_convention_;  //!< string defining the header convention
        char buffer_[1024];              //!< buffer for what ever purpose
        CIFBinaryHeader *_binheader;       //!< header object

    public:
        CBFReader(){ stream_=NULL; _binheader=NULL;}
        CBFReader(const char* filename);
        ~CBFReader();

        void setFileName(const char* filename);
        DataValue *read();
};



#endif /* CBFREADER_HPP_ */
