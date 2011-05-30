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

#include "../PNITypes.hpp"
#include "../DataObject.hpp"

#include "Reader.hpp"
#include "CBFHeader.hpp"


#define CIF_BINARY_SECTION "--CIF-BINARY-FORMAT-SECTION--"
#define CIF_HEADER_CONVENTION "_array_data.header_convention"
#define CIF_HEADER_CONVENTION_SLS "\"SLS_1.0\""
#define CIF_HEADER_CONVENTION_SLS_11 "\"SLS/DECTRIS_1.1\""

namespace pni{
namespace utils{


class CBFReader:public Reader{
    private:
        String _header_convention_;   //!< string defining the header convention
        char buffer_[1024];           //!< buffer for what ever purpose
        CIFBinaryHeader *_binheader;  //!< header object

    public:
        CBFReader();
        CBFReader(const char* filename);
        CBFReader(const String &fname);
        virtual ~CBFReader();

        virtual DataObject *read();
};

}
}

#endif /* CBFREADER_HPP_ */
