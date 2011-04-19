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

class CBFBinReader{
    protected:
        unsigned long nelements_;   //total number of elements to read
        unsigned int  elemsize_;    //size of each element (depends on the type)
        void *raw_data_;             //general buffer where the data should
                                    //be read to
    public:
        CBFBinReader(){}
        CBFBinReader(unsigned long);
        virtual ~CBFBinReader();
        
        void freeBuffer(); //free the data buffer
        void allocateBuffer(); //allocate data buffer
        
    

    
};

template<typename T> class CBFBinReaderByteOffset:public CBFBinReader{
    private:
        T *data_;
    public:
        CBFBinReaderByteOffset():CBFBinReader()
        CBFBinReaderByteOffset(unsigned long);
        
        const T* getData(); //returns the data 
        
        
        
};

template<typename T> CBFBinReaderByteOffset::CBFBinReaderByteOffset(unsigned long n)
    :CBFBinReader(n)
{
    unsigned long i;
    
    elemsize_ = sizeof(T);
    
    allocateBuffer(); //allocate memory (done by the base class)
    
    data_ = (T *)raw_data_; //make the data vailable to the outside world
    
};

template<typename T> CBFBinReaderByteOffset<T>::read(std::ifstream &stream){
    unsigned long i;
    long buffer;
    
    buffer = 0
    while(!stream.eof()){
        
        stream.read(&buffer,1);
        if(((unsigned char)buffer)!=0x80)
        
    } 
}






std::string strip(std::string &s,const char *begrem="\n ",const char *endrem=" \n"){
    size_t start,stop;
    
    start = s.find_first_not_of(begrem);
    stop = s.find_last_not_of(endrem);
    
    return s.substr(start,(stop-start)); 
}

int get_key_value(std::string &s,const char *del,std::string &key,std::string &value){
    size_t start;
    
    start = s.find_first_of(del);
    
    key = s.substr(0,start);
    value = s.substr(start);
    
    start = value.find_first_not_of(del);
    value = value.substr(start);
    
    return 0;
}

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

std::ostream &operator<<(std::ostream &o,const CIFBinaryHeader &h){
    long i;
    
    o<<"CIF Binary header information"<<std::endl;
    o<<"Data type: ";
    switch(h.data_type_){
        case SIGNED_INT_32:
            o<<"32Bit signed integer";
            break;
    }
    o<<std::endl<<"Byte order: ";
    switch(h.byte_order_){
        case BYTE_ORDER_BIG_ENDIAN:
            o<<"big endian";break;
        case BYTE_ORDER_LITTLE_ENDIAN:
            o<<"little endian";break;
    }
    o<<std::endl<<"Compression: ";
    switch(h.converion_id_){
        case CONVERSION_BYTE_OFFSET:
            o<<"byte offset compression";break;
    }
    o<<std::endl<<"Dimensions "<<h.ndims_<<" (from fastest to slowest): ";
    for(i=2;i>=3-(long)h.ndims_;i--){
        o<<h.dims_[i]<<" ";
    }
    o<<std::endl<<"Total number of elements: "<<h.nofelements_;
    
    return o;
}



//class for Pilatus (Dectris) binary header
class PCIFBinaryHeader:public CIFBinaryHeader{
    public:
    PCIFBinaryHeader(){}
    PCIFBinaryHeader(std::ifstream &stream);
};

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

CBFReader::CBFReader(const char* filename){
    stream_ = new std::ifstream(filename,std::ios::binary);
    if(stream_ == NULL){
        std::string desc;
        desc = "Error opening the CBF file ";
        desc += filename;
        desc += "!\n";
        Exception exception("CBFReader",
        "CBFReader::CBFReader(const char* filename)",
        desc);
        throw exception;
    }
}

CBFReader::~CBFReader(){
    stream_->close();
}

void CBFReader::setFileName(const char *filename){
    if(stream_!=NULL) delete stream_;
    
    stream_ = new std::ifstream(filename,std::ios::binary);
    if(stream_ == NULL){
        std::string desc;
        desc = "Error opening the CBF file ";
        desc += filename;
        desc += "!\n";
        Exception exception("CBFReader",
        "CBFReader::CBFReader(const char* filename)",
        desc);
        throw exception;
    }
}



void CBFReader::read(){
    std::ifstream &ref = *stream_;
    unsigned char byte;    
    std::string linebuffer;
    std::string key,value;

    while(!ref.eof()){
        byte = ref.get();
        
        //if(byte == 0xd5) break;
          
        if(byte == '\n'){
            //reached end of line - here we have to do something
            linebuffer=strip(linebuffer); 
            try{
                get_key_value(linebuffer," ",key,value); 
                    
                if(key == CIF_HEADER_CONVENTION){
                    //need to set the proper header convention
                    if(value == CIF_HEADER_CONVENTION_SLS){
                        header_convention_ = CIF_HEADER_CONVENTION_SLS;
                        std::cout<<"header convention "<<header_convention_<<std::endl;
                    }
                }        
            }catch(...){
                //in case that the linebuffer cannot be split into 
                //key value pairs  - we do not care for the moment
            }
                       
          
            if(linebuffer == CIF_BINARY_SECTION){
                std::cout<<"found binary section"<<std::endl;
                if(header_convention_ == CIF_HEADER_CONVENTION_SLS){
                    //if the header convention identifies the file as a
                    //Dectris CBF file we use this particular reader 
                    //for the binary section
                    binheader = PCIFBinaryHeader(ref);
                }
                std::cout<<binheader<<std::endl;
                break;
            }
            linebuffer.clear();
            continue;
        }else if(byte == 0xd5){        
            //ok here comes the tricky part - we have to start the
            //binary reader - this depends mainly on the compression 
            //algorithm used. However, we do not have to make this 
            //decision by ourself - the header object will act as a
            //factory for the reader 
            
        }else{
            //if there are no other things to do we add the 
            //byte to the linebuffer
            linebuffer += byte;        
        }

    }

}

int main(int argc,char **argv){
    CBFReader reader;
    
    reader.setFileName("org_00009.cbf");
    reader.read();
    

    return 0;
}
