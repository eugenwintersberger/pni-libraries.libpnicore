/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniutils.
 *
 * libpniutils is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniutils is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
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
        EXCEPTION_SETUP("std::streampos DectrisCBFReader::read_header("
            "std::ifstream &is,std::vector<ImageInfo> &info)");

        UInt8 byte;
        String linebuffer;
        size_t nx,ny,bits_per_pixel;
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
                std::cout<<"reached binary data section"<<std::endl;
                return is.tellg();
                break;
            }

            
            if(byte == '\n'){
                //now we need to check the line for usefull information
          
                //--------------get compression algorithm------------------
                if(boost::regex_match(linebuffer,conversion_regex))
                {
                    if(!boost::regex_search(linebuffer,match,quoted_text))
                    {
                        EXCEPTION_INIT(FileError,"Cannot find conversion"
                                " string!");
                        EXCEPTION_THROW();
                    }
                    
                    if(match.str(0) == "\"x-CBF_BYTE_OFFSET\"")
                    {
                        ct = CompressionID::CBF_BYTE_OFFSET;
                    }
                    else
                    {
                        EXCEPTION_INIT(FileError,"Unknown compression"
                                " algorithm!");
                        EXCEPTION_THROW();
                    }

                }

                //---------------get data type----------------------------
                if(boost::regex_match(linebuffer,type_regex))
                {
                    if(!boost::regex_search(linebuffer,match,quoted_text))
                    {
                        EXCEPTION_INIT(FileError,"Cannot find data type"
                                " string!");
                        EXCEPTION_THROW();
                    }
                    //set the data type id
                    if(match.str(0) == "\"signed 32-bit integer\"")
                    {
                        tid=TypeID::INT32;
                        bits_per_pixel = 32;
                    }
                    else
                    {
                        EXCEPTION_INIT(FileError,"Unkown data type!");
                        EXCEPTION_THROW();
                    }
                }

                //---------get number of pixels in y-direction-------------
                if(boost::regex_match(linebuffer,ny_regex))
                {
                    if(!boost::regex_search(linebuffer,match,int_numbers))
                    {
                        EXCEPTION_INIT(FileError,"Cannot read number of "
                                "pixels in y-direction!");
                        EXCEPTION_THROW();
                    }
                    ny = std::atoi(match.str(0).c_str());
                }

                //---------get number of pixels in x-direction-------------
                if(boost::regex_match(linebuffer,nx_regex))
                {
                    if(!boost::regex_search(linebuffer,match,int_numbers))
                    {
                        EXCEPTION_INIT(FileError,"Cannot read number of "
                                "pixels in x-direction!");
                        EXCEPTION_THROW();
                    }
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

    }

//end of namespace
}
}
}
