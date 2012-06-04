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
 * DataReader class implementation
 *
 * Created on: Apr 23, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */


#include "DataReader.hpp"
#include "../Exceptions.hpp"


namespace pni{
namespace io{

    //===========implementation of private methods=========================
    //default implementation
    std::unique_ptr<std::ifstream> DataReader::
        _open_stream(const String &fname) const
    {
        EXCEPTION_SETUP("std::unique_ptr<std::ifstream> DataReader::"
                "_open_stream(const String &fname,bool binary)");

        std::unique_ptr<std::ifstream> stream(new std::ifstream()); 
        if(!stream)
        {
            EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory "
                    "for stream object!");
            EXCEPTION_THROW();
        }

        if(_is_binary)
        {
            stream->open(fname);
        }
        else
        {
            stream->open(fname,std::ifstream::binary);
        }

        return stream;
    }

    //====================Implementation of constructors===================
    //implementation of the default constructor
    DataReader::DataReader() {}

    //implementation of the standard constructor
    DataReader::DataReader(const String &fname,bool binary):
        _fname(fname),
        _is_binary(binary),
        _istream(_open_stream(fname))
    { 
        EXCEPTION_SETUP("DataReader::DataReader(const String &fname,"
                        "bool binary)");

        if(_istream->fail())
        {
            EXCEPTION_INIT(FileError,"Error opening file ["+fname+"]!");
            EXCEPTION_THROW();
        }
    }

    //implementation of the move constructor
    DataReader::DataReader(DataReader &&r):
        _fname(std::move(r._fname)),
        _is_binary(std::move(r._is_binary)),
        _istream(std::move(r._istream))
    {}

    //implementation of the destructor
    DataReader::~DataReader() 
    {
        //close the file in case the object is getting destroied.
        if(_istream)
            if(_istream->good() && _istream->is_open()) _istream->close();
    }

    //=============implementation of assignment operators==================
    DataReader &DataReader::operator=(DataReader &&r)
    {
        if(this == &r) return *this;

        _fname = std::move(r._fname);
        _istream = std::move(_istream);

        return *this;
    }

    //============implementation of utilty methods=========================
    String DataReader::filename() const
    {
        return _fname;
    }

    //---------------------------------------------------------------------
    void DataReader::filename(const String &fname)
    {
        _fname = fname;
    }
    
    //----------------------------------------------------------------------
    void DataReader::close()
    {
        if(_istream->is_open()) _istream->close();
    }

    //---------------------------------------------------------------------
    void DataReader::open()
    {
        close(); //close the file if it is already open
        _istream = _open_stream(filename());
    }

//end of namespace
}
}
