




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




















