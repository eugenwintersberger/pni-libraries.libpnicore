/*
 * Implementation of class CBFReader
 *
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
 * CBFReader is the base class for readers for the CBF format and a descendant
 * of Reader (see Reader.hpp).
 *
 * Created on: Apr 19, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#include "CBFReader.hpp"
#include "strutils.hpp"
#include "../Exceptions.hpp"
#include "../Array.hpp"
#include "../Types.hpp"

//need to use regular expressions from boost
#include<boost/regex.hpp>


namespace pni{
namespace io{

    //================implementation of constructors and destructor========
    //implementation of the default constructor
    CBFReader::CBFReader():ImageReader()
    { }

    //---------------------------------------------------------------------
    //implementation of the standard constructor
    CBFReader::CBFReader(const String &fname):
        ImageReader(fname)
    {
        //here the file is immediately opened  - we have to parse the 
        //header to obtain information about the data
        _parse_file();
    
    }

    //---------------------------------------------------------------------
    //implementation of the destructor
    CBFReader::~CBFReader()
    { }

    //================implementation of assignment operators===============
    CBFReader &CBFReader::operator=(CBFReader &&r)
    {
        if(this == &r) return *this;

        ImageReader::operator=(std::move(r));
        return *this;
    }

    //===============implemenetation of private methods====================
    void CBFReader::_parse_file(){
        EXCEPTION_SETUP("void CBFReader::_parse_file()");

        char linebuffer[1024];
        std::ifstream &_istream = _get_stream();

        boost::regex header_convention("^_array_data.header_convention.*");
        boost::regex regex_sls("SLS");
        boost::regex regex_dectris("DECTRIS");
        boost::regex quoted_text("\".*\"");
        boost::cmatch match;

        while(!_istream.eof())
        {
            _istream.getline(linebuffer,1024);    
            if(boost::regex_match(linebuffer,match,header_convention)){
                //extract the convention string from the header
                //convention
                boost::regex_search(linebuffer,match,quoted_text);
                if(boost::regex_search(match.str(0),regex_sls)||
                   boost::regex_search(match.str(0),regex_dectris))
                {
                    _data_offset = cbf::DectrisReader::read_header(_istream,
                            _image_info,_compression_type);
                    _detector_vendor = cbf::VendorID::DECTRIS;
                    return;
                }else{
                    //should raise an exception here
                    EXCEPTION_INIT(FileError,"Unknown CBF style!");
                    EXCEPTION_THROW();
                }
            }
        }
    }


//end of namespace
}
}

