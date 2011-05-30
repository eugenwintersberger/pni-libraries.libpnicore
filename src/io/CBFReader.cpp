/*
 * cbfreader.cpp
 *
 *  Created on: Apr 19, 2011
 *      Author: Eugen Wintersberger
 */

//Implementation of the class CBFReader

#include "CBFReader.hpp"
#include "strutils.hpp"
#include "../Exceptions.hpp"
#include "../Array.hpp"
#include "../DataObject.hpp"
#include "../PNITypes.hpp"

namespace pni{
namespace utils{

CBFReader::CBFReader():Reader()
{
	_binheader = NULL;
}

CBFReader::CBFReader(const char* filename):Reader(filename)
{
    _binheader = NULL;
}

CBFReader::~CBFReader(){
	//closes the file on object destruction.
    if(_binheader!=NULL) delete _binheader;
}

DataObject *CBFReader::read(){
    UInt8 byte;
    String linebuffer;
    String key,value;
    ArrayObject *v;

    while(!_istream.eof()){
        byte = _istream.get();

        //if(byte == 0xd5) break;


        if(byte == '\n'){
        	//if the byte we have read is a newline we reached the end of an ASCII line
            //the first thing to do is to get rid of leading and trailing blanks and other mess
            linebuffer=strip(linebuffer);

            try{
            	//try to split string into a key value pair - if this fails - who cares
                get_key_value(linebuffer," ",key,value);

                if(key == CIF_HEADER_CONVENTION){
                    //need to set the proper header convention
                    if(value == CIF_HEADER_CONVENTION_SLS){
                        _header_convention_ = CIF_HEADER_CONVENTION_SLS;
                        std::cout<<"header convention "<<_header_convention_<<std::endl;
                    }
                }
            }catch(...){
                //in case that the linebuffer cannot be split into
                //key value pairs  - we do not care for the moment
            }


            if(linebuffer == CIF_BINARY_SECTION){
            	//ok we reached the binary section of the file
            	std::cout<<"found binary section"<<std::endl;
                if(_header_convention_ == CIF_HEADER_CONVENTION_SLS){
                    //if the header convention identifies the file as a
                    //Dectris CBF file we use this particular reader
                    //for the binary section
                    _binheader = new PCIFBinaryHeader(_istream);
                }
                std::cout<<*_binheader<<std::endl;
            }
            linebuffer.clear();
            continue;
        }else if(((unsigned char)byte) == 0xd5){
            //ok here comes the tricky part - we have to start the
            //binary reader - this depends mainly on the compression
            //algorithm used. However, we do not have to make this
            //decision by ourself - the header object will act as a
            //factory for the reader
        	std::cout<<"create the binary stream reader!"<<std::endl;
        	CBFBinStreamReader *reader = _binheader->createBinaryReader();
        	v = _binheader->createArray();
        	v->setName(_fname);
        	v->setDescription("Dectris CBF detector data");

        	reader->setStream(&_istream);
        	BufferObject::sptr o = v->getBuffer();
        	reader->setBuffer(o);
        	//call the reader method
        	reader->read();

        	std::cout<<"finished with reading data!"<<std::endl;

        	//once we are done we have to destroy the reader again and leave the
        	//loop
        	delete reader;
        	break;

        }else{
            //if there are no other things to do we add the
            //byte to the linebuffer
            linebuffer += byte;
        }

    }
    return v;
}


}
}

