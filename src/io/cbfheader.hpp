/*
 * cbfheader.hpp
 *
 *  Created on: Apr 19, 2011
 *      Author: eugen
 */

#ifndef CBFHEADER_HPP_
#define CBFHEADER_HPP_

#include "cbfbinstreamreader.hpp"
#include "../datavalue.hpp"

#define CIF_DATA_TYPE_KEY  "X-Binary-Element-Type"
#define CIF_DATA_SIGNED_INT32  "\"signed 32-bit integer\""
#define UNSIGNED_INT_8 1
#define SIGNED_INT_8 2
#define UNSIGNED_INT_16 3
#define SIGNED_INT_16 4
#define UNSIGNED_INT_32 5
#define SIGNED_INT_32 6
#define UNSIGNED_INT_64 7
#define SIGNED_INT_64 8

#define CIF_DATA_BYTE_ORDER_KEY  "X-Binary-Element-Byte-Order"
#define BYTE_ORDER_LITTLE_ENDIAN 1
#define BYTE_ORDER_BIG_ENDIAN 2

#define CIF_DATA_CONVERSION_KEY  "conversions"
#define CIF_DATA_CONVERSION_BO_VALUE  "\"x-CBF_BYTE_OFFSET\""
#define CONVERSION_BYTE_OFFSET 1

#define CIF_DATA_1FAST_DIM_KEY  "X-Binary-Size-Fastest-Dimension"
#define CIF_DATA_2FAST_DIM_KEY  "X-Binary-Size-Second-Dimension"
#define CIF_DATA_3FAST_DIM_KEY  "X-Binary-Size-Third-Dimension"
#define CIF_DATA_NELEMENTS_KEY  "X-Binary-Number-of-Elements"

class CIFBinaryHeader{
    protected:
        unsigned int _conversion_id;    //which type of compression used
        unsigned int _byte_order;      //byte order of the data
        unsigned long _nofelements;    //number of elements stored
        unsigned long _dims[3];        //number of dimension along each direction
        //a few words about how the dimensions are stored
        //since we do not know in the beginning of the reading process
        //how many dimension are present in the data (maximum 3)
        //the data is stored in the following:
        //dims_[2] - fastest dimension
        //dims_[1] - second fastest dimension
        //dims_[0] - third fastest dimension
        //this is not important for the user - however for developers
        //this is maybe interesting.

        unsigned int _data_type;       //datatype used to store the data
        unsigned int _ndims;           //rank of the data stored

    public:
        CIFBinaryHeader(){};
        CIFBinaryHeader(std::ifstream &){}
        virtual ~CIFBinaryHeader(){}

        friend std::ostream &operator<<(std::ostream &o,const CIFBinaryHeader &h);

        virtual CBFBinStreamReader *createBinaryReader(){ return NULL;}
        virtual DataValue *createArray();
        unsigned long getNumberOfElements() const { return _nofelements;}
        unsigned int getNumberOfDimensions() const { return _ndims;}
        const unsigned long *getDimensions() const { return _dims;}
};

//class for Pilatus (Dectris) binary header
class PCIFBinaryHeader:public CIFBinaryHeader{
    public:
    PCIFBinaryHeader(){}
    PCIFBinaryHeader(std::ifstream &stream);

    virtual CBFBinStreamReader *createBinaryReader();
};



#endif /* CBFHEADER_HPP_ */
