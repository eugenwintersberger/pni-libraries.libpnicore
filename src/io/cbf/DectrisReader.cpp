/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * DectrisCBFReader class implementation
 *
 * Created on: Apr 23, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#include<boost/regex.hpp>
#include "DectrisReader.hpp"
#include "../../Exceptions.hpp"


namespace pni{
namespace io{
namespace cbf{

    //==================implementation of static memeber functions=========
    //implementation of the read_header method
    std::streampos DectrisReader::read_header(std::ifstream &is,
            std::vector<pni::io::ImageInfo> &info,CompressionID &ct)
    {
        UInt8 byte;
        String linebuffer;
        size_t nx=0,ny=0,bits_per_pixel;
        TypeID tid;
        
        //define some useful regular expressions
        boost::regex quoted_text("\".*\"");
        boost::regex int_numbers("[[:digit:]]+");
        boost::regex conversion_regex(".*conversions=.*"); //
        boost::regex type_regex("^X-Binary-Element-Type:.*"); // "signed 32-bit integer"
        boost::regex ny_regex("^X-Binary-Size-Fastest-Dimension:.*");// 487
        boost::regex nx_regex("^X-Binary-Size-Second-Dimension:.*"); // 195
        boost::smatch match;


        //we really need to parse such a file byte by byte as the marker
        //indicating the start of the data section is encoded in a single
        //byte. Thus if we would read header data line wise we would most
        //probably miss it.
        while(!is.eof()){
            byte = is.get();

            //the first thing we have to check here is if we have reached
            //the binary section of the data
            if(((unsigned char)byte) == 0xd5)
            {
                //ok - if we came here we are done with all the rubish
                ImageInfo iinfo(nx,ny);
                iinfo.append_channel(ImageChannelInfo(tid,bits_per_pixel));
                info.push_back(iinfo);

                //this means that we have to store the offset and can 
                //break the loop here
                return is.tellg();
                break;
            }

            
            if(byte == '\n'){
                //now we need to check the line for usefull information
          
                //--------------get compression algorithm------------------
                if(boost::regex_match(linebuffer,conversion_regex))
                {
                    if(!boost::regex_search(linebuffer,match,quoted_text))
                        throw FileError(EXCEPTION_RECORD,
                                "Cannot find conversion string!");
                    
                    if(match.str(0) == "\"x-CBF_BYTE_OFFSET\"")
                        ct = CompressionID::CBF_BYTE_OFFSET;
                    else
                        throw FileError(EXCEPTION_RECORD,
                                "Unknown compression algorithm!");

                }

                //---------------get data type----------------------------
                if(boost::regex_match(linebuffer,type_regex))
                {
                    if(!boost::regex_search(linebuffer,match,quoted_text))
                        throw FileError(EXCEPTION_RECORD,
                        "Cannot find data type string!");

                    //set the data type id
                    if(match.str(0) == "\"signed 32-bit integer\"")
                    {
                        tid=TypeID::INT32;
                        bits_per_pixel = 32;
                    }
                    else
                        throw FileError(EXCEPTION_RECORD,"Unkown data type!");
                }

                //---------get number of pixels in y-direction-------------
                if(boost::regex_match(linebuffer,ny_regex))
                {
                    if(!boost::regex_search(linebuffer,match,int_numbers))
                        throw FileError(EXCEPTION_RECORD,
                        "Cannot read number of pixels in y-direction!");

                    ny = std::atoi(match.str(0).c_str());
                }

                //---------get number of pixels in x-direction-------------
                if(boost::regex_match(linebuffer,nx_regex))
                {
                    if(!boost::regex_search(linebuffer,match,int_numbers))
                        throw FileError(EXCEPTION_RECORD,
                        "Cannot read number of pixels in x-direction!");

                    nx = std::atoi(match.str(0).c_str());
                }

                linebuffer.clear();
                continue;

            }else{
                //if there are no other things to do we add the
                //byte to the linebuffer
                linebuffer += byte;
            }

        }

        return 0; //just to make the compiler happy

    }

//end of namespace
}
}
}
