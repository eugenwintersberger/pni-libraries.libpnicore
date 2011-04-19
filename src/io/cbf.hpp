
#ifndef __CBF_HPP__
#define __CBF_HPP__


#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdio>
#include<cstdlib>

#define CIF_BINARY_SECTION "--CIF-BINARY-FORMAT-SECTION--"
#define CIF_HEADER_CONVENTION "_array_data.header_convention"
#define CIF_HEADER_CONVENTION_SLS "\"SLS_1.0\""

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

};

//class for Pilatus (Dectris) binary header
class PCIFBinaryHeader:public CIFBinaryHeader{
    public:
    PCIFBinaryHeader(){}
    PCIFBinaryHeader(std::ifstream &stream);
};

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

template<typename T> class CBFBinReaderByteOffset:public CBFBinReader{
    private:
        T *data_;
    public:
        CBFBinReaderByteOffset():CBFBinReader(){}
        CBFBinReaderByteOffset(unsigned long);

        const T* getData(); //returns the data



};




#endif
