/*
 * cbfboreaders.hpp
 *
 *  Created on: Apr 19, 2011
 *      Author: eugen
 */

#ifndef CBFBOREADERS_HPP_
#define CBFBOREADERS_HPP_

#include "cbf.hpp"
#include "../exceptions.hpp"

template<typename T> class CBFBinReaderByteOffset:public CBFBinReader{
    private:
        T *_data;
    public:
        CBFBinReaderByteOffset():CBFBinReader(){}
        CBFBinReaderByteOffset(unsigned long);

        const T* getData(); //returns the data



};

template<typename T> CBFBinReaderByteOffset<T>::CBFBinReaderByteOffset():CBFBinReader(){
	_data = NULL;
}


template<typename T> CBFBinReaderByteOffset::CBFBinReaderByteOffset(unsigned long n)
    :CBFBinReader(n)
{
    unsigned long i;
    _data = NULL;

    elemsize_ = sizeof(T);

    _data = new T[nelements_];
    if(!_data){
    	MemoryAllocationError e("CBFBinReaderByteOffset::CBFBinReaderByteOffset(unsigned long n)",
    			"Error allocating memory for data");
    	throw e;
    }

};

template<typename T> CBFBinReaderByteOffset<T>::read(std::ifstream &stream){
    unsigned long i;
    unsigned long ecnt;  // element counter
    T buffer;

    buffer = 0;
    ecnt = 0;

    //initialize all data values with 0
    for(i=0;i<nelements_;i++) _data[i] = 0;

    while((!stream.eof())&&(ecnt!=nelements_)){

        stream.read(&buffer,1);
        if(((unsigned char)buffer)!=0x80){
        	//this byte is a valid offset
        	_data[ecnt] += (char)buffer;
        	//now we have to increment the element counter
        	ecnt ++;


        	buffer = 0;
        	ecnt++;
        	continue;
        }

        if(((unsigned short)buffer)!=8x8000){
        	_data[ecnt] = buffer;
        	buffer = 0;
        	ecnt++;
        	continue;
        }

    }
}

#endif /* CBFBOREADERS_HPP_ */
