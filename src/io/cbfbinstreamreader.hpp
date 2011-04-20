/*
 * cbfbinstreamreader.hpp
 *
 *  Created on: Apr 20, 2011
 *      Author: eugen
 */

#ifndef CBFBINSTREAMREADER_HPP_
#define CBFBINSTREAMREADER_HPP_

#include<iostream>

#include "../buffer.hpp"

//! binary CBF data reader

//! This is the base class for all binary CBF reades. The aim of all this
//! classes is to decode the binary data stream in a CBF file and
//! store it to a buffer for further processing.
class CBFBinStreamReader{
    protected:
        unsigned long nelements_;   //!< total number of elements to read
        unsigned int  elemsize_;    //!< size of each element in bytes (depends on the type)
        std::ifstream *_stream;     //!< stream from which to read the data

    public:
        //! default constructor
        CBFBinStreamReader();
        //! copy constructor
        CBFBinStreamReader(const CBFBinStreamReader &);
        //! constructor

        //! \param n number of elements to read from the stream.
        CBFBinStreamReader(unsigned long n);
        virtual ~CBFBinStreamReader();

        virtual void setStream(std::ifstream *s) { _stream = s;}

        virtual void read(){
        	std::cout<<"call base reader - does nothing!"<<std::endl;
        };
        virtual void setBuffer(AbstractBuffer *b){
        	std::cout<<"call base class - does nothing!"<<std::endl;
        }

};

#endif /* CBFBINSTREAMREADER_HPP_ */
