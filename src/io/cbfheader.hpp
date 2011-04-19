/*
 * cbfheader.hpp
 *
 *  Created on: Apr 19, 2011
 *      Author: eugen
 */

#ifndef CBFHEADER_HPP_
#define CBFHEADER_HPP_

#include "cbfreader.hpp"

class CIFBinaryHeader{
    protected:
        unsigned int converion_id_;    //which type of compression used
        unsigned int byte_order_;      //byte order of the data
        unsigned long nofelements_;    //number of elements stored
        unsigned long dims_[3];        //number of dimension along each direction
        //a few words about how the dimensions are stored
        //since we do not know in the beginning of the reading process
        //how many dimension are present in the data (maximum 3)
        //the data is stored in the following:
        //dims_[2] - fastest dimension
        //dims_[1] - second fastest dimension
        //dims_[2] - third fastest dimension
        //this is not important for the user - however for developers
        //this is maybe interesting.

        unsigned int data_type_;       //datatype used to store the data
        unsigned int ndims_;           //rank of the data stored

    public:
        CIFBinaryHeader(){};
        CIFBinaryHeader(std::ifstream &){}

        friend std::ostream &operator<<(std::ostream &o,const CIFBinaryHeader &h);

        virtual CBFBinReader *createBinaryReader() = 0;

};

//class for Pilatus (Dectris) binary header
class PCIFBinaryHeader:public CIFBinaryHeader{
    public:
    PCIFBinaryHeader(){}
    PCIFBinaryHeader(std::ifstream &stream);

    virtual CBFBinReader *createBinaryReader();
};



#endif /* CBFHEADER_HPP_ */
