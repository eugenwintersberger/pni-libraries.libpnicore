/*
 * cbfreader.cpp
 *
 *  Created on: Apr 19, 2011
 *      Author: Eugen Wintersberger
 */

//Implementation of the class CBFReader

#include "cbf.hpp"
#include "strutils.hpp"
#include "../exceptions.hpp"

CBFReader::CBFReader(const char* filename){
    stream_ = new std::ifstream(filename,std::ios::binary);
    if(stream_ == NULL){
    	// raise an exception in the case that opening
    	// the file fails.
        std::string desc;
        desc = "Error opening the CBF file ";
        desc += filename;
        desc += "!\n";
        FileError e("CBFReader::CBFReader(const char* filename)",desc);
        throw e;
    }
}

CBFReader::~CBFReader(){
    stream_->close();
}

void CBFReader::setFileName(const char *filename){
    if(stream_!=NULL) delete stream_;

    stream_ = new std::ifstream(filename,std::ios::binary);
    if(stream_->fail()){
        std::string desc;
        desc = "Error opening the CBF file ";
        desc += filename;
        desc += "!\n";
        FileError e("CBFReader::CBFReader(const char* filename)",desc);
        throw e;
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
