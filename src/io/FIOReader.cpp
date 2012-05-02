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
 * FIOReader class implementation
 *
 * Created on: Apr 30, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#include <string>
#include "FIOReader.hpp"

namespace pni{
namespace io{
    //======================private member functions===========================
    void FIOReader::_parse_file(std::ifstream &stream)
    {
        String::value_type buffer; 
        while(!stream.eof())
        {
            //read a character
            stream>>buffer;
            if(buffer == '%')
            {
                //each section in the file starts with a % sign - now we need to
                //figure out which section we are
                stream>>buffer;
                switch(buffer){
                    case 'p':
                        //parameters section
                        _parse_parameters(stream); break;
                    case 'd':
                        //data section
                        _parse_data(stream); 
                        return; 
                        break;
                }

            }
        }

    }

    //-------------------------------------------------------------------------
    void FIOReader::_parse_parameters(std::ifstream &stream)
    {
        String::value_type buffer;
        String param_name;
        //clear the parameter map
        _param_map.clear();

        //read the parameter section
        while(!stream.eof())
        {
            //read a single character form the file
            stream>>buffer;
            
            //reached end of section
            if(buffer == '%') break;

            //handle comment lines
            if(buffer == '!')
            {
                while(stream.get() != '\n');
                continue;
            }

            //the first = character indicates the end of the parameter name
            if(buffer == '=')
            {
                //finished with this parameter
                _param_map.insert({param_name,stream.tellg()});
                std::cout<<param_name<<" at "<<stream.tellg()<<std::endl;
               
                //reset the paremter name
                param_name.clear();

                //move stream to end of line before continuing with 
                //all other parameters
                while(stream.get() != '\n');
                continue;
            }

            if(buffer != ' ') param_name.push_back(buffer);

        }

        //reset the stream for one position
        stream.seekg(-1,std::ios::cur);
        
    }

    //-------------------------------------------------------------------------
    void FIOReader::_parse_data(std::ifstream &stream)
    {
        boost::regex comment("^!"); //regular expression for comment lines
        boost::regex col("^ Col");
        boost::cmatch match;

        char linebuffer[1024];

        while(!stream.eof())
        {
            stream.getline(linebuffer,1024);                
            //std::cout<<linebuffer<<std::endl;
            if(boost::regex_match(linebuffer,match,col))
            {
                std::cout<<linebuffer<<std::endl;
            }
           
        }
    }

    //-------------------------------------------------------------------------
    void FIOReader::_get_parameter_data(std::ifstream &stream,String &value)
        const
    {
        char buffer;
        value.clear();

        while(!stream.eof())
        {
            stream.get(buffer);
            if(buffer == '\n') break;
            value.push_back(buffer);
        }
    }

    //=======================constructors and destructor======================= 
    //default constructor implementation
    FIOReader::FIOReader():SpreadsheetReader() {}

    //--------------------------------------------------------------------------
    //move constructor implementation
    FIOReader::FIOReader(FIOReader &&r):SpreadsheetReader(std::move(r)){}

    //-------------------------------------------------------------------------
    //standard constructor implementation
    FIOReader::FIOReader(const String &n):
        SpreadsheetReader(n)
    {
        _parse_file(_get_stream()); 
    }

    //-------------------------------------------------------------------------
    //! destructor
    FIOReader::~FIOReader()
    {}

    //=================assignment operators====================================
    //move assignment implementation
    FIOReader &FIOReader::operator=(FIOReader &&r)
    {
        if(this == &r) return *this;
        SpreadsheetReader::operator=(std::move(r));


        return *this;
    }

    //=============public memeber methods======================================
    //implementation of nparameters
    size_t FIOReader::nparameters() const
    {
        return _param_map.size();
    }
    
    //-------------------------------------------------------------------------
    //implementation of parameter names
    std::vector<String> FIOReader::parameter_names() const
    {
        std::vector<String> pnames;
        for(auto value: _param_map) pnames.push_back(value.first);
        return pnames;
    }

    //-------------------------------------------------------------------------
    //implementation of nrecords()
    size_t FIOReader::nrecords() const
    {

    }

    //-------------------------------------------------------------------------
    std::vector<String> FIOReader::column_names() const
    {

    }

    //-------------------------------------------------------------------------
    std::vector<TypeID> FIOReader::column_types() const
    {


    }

//end of namespace
}
}
