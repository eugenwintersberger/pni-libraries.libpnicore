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

#define CIF_BINARY_SECTION "--CIF-BINARY-FORMAT-SECTION--"
#define CIF_HEADER_CONVENTION "_array_data.header_convention"
#define CIF_HEADER_CONVENTION_SLS "\"SLS_1.0\""


class CBFReader{
    private:
        std::ifstream *stream_;
        std::string header_convention_;
        char buffer_[1024];
        CIFBinaryHeader binheader;

    public:
        CBFReader(){ stream_=NULL;}
        CBFReader(const char* filename);
        ~CBFReader();

        void setFileName(const char* filename);
        void read();


};


//! binary CBF data reader

//! This is the base class for all binary CBF reades. The aim of all this
//! classes is to decode the binary data stream in a CBF file and
//! store it to a buffer for further processing.
class CBFBinReader{
    protected:
        unsigned long nelements_;   //!< total number of elements to read
        unsigned int  elemsize_;    //!< size of each element in bytes (depends on the type)

    public:
        //! default constructor
        CBFBinReader();
        //! copy constructor
        CBFBinReader(const CBFBinReader &);
        //! constructor

        //! \param n number of elements to read from the stream.
        CBFBinReader(unsigned long n);
        virtual ~CBFBinReader();

        void freeBuffer(); //free the data buffer
        void allocateBuffer(); //allocate data buffer

};


#endif /* CBFREADER_HPP_ */
