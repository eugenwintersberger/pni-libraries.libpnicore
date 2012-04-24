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
 * Implementation of class TIFFReader.
 *
 * Created on: Jun 15, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#include "../Exceptions.hpp"
#include "../Array.hpp"
#include "../Types.hpp"
#include "../Buffer.hpp"
#include "TIFFReader.hpp"

namespace pni{
    namespace utils{
        //============implementation of private methods========================
        //implementation of _read_image_info
        void TIFFReader::_read_file_info()
        {
            EXCEPTION_SETUP("void TIFFReader::_read_image_info()");
            //obtain stream
            std::ifstream &stream = _get_stream();
            
            //in the first step we need to find out if the file is really a
            //TIFF file and how it looks with endieness
            char buffer[2];
            stream.read(buffer,2);
            if((buffer[0]=='I')&&(buffer[1]=='I')) _little_endian = true;
            if((buffer[0]=='M')&&(buffer[1]=='M')) _little_endian = false;

            UInt16 magic;
            stream.read((char *)(&magic),2);
            if(magic!=42){
                EXCEPTION_INIT(FileError,"File "+filename()+"is not a valid TIFF file!");
                EXCEPTION_THROW();
            }

            //no we need to read the IFD entries
            //read the first IFD offset
            Int32 ifd_offset = 0;
            stream.read((char*)(&ifd_offset),4);

            //read IFDs from the file
            do{
                TIFFIFD::IFDSptr ifd(new TIFFIFD());
                stream.seekg(ifd_offset, std::ios::beg);
                stream >> *ifd;
                _ifd_list.push_back(ifd);
                ifd_offset = ifd->getNextOffset();
            }while(ifd_offset);

 
        }

        //---------------------------------------------------------------------
        //implementation of _IFD2ImageInfo 
        void TIFFReader::_IFD2ImageInfo()
        {
            EXCEPTION_SETUP("void TIFFReader::_IFD2ImageInfo()");
            

        }

        //=============implementation of constructors and destructor===========
        //implementation of the default constructor
        TIFFReader::TIFFReader():ImageReader()
        { 
            //set the stream format to binary
            DataReader::_set_binary();
        }

        //---------------------------------------------------------------------
        //implementation of the move constructor
        TIFFReader::TIFFReader(TIFFReader &&r):
            ImageReader(std::move(r)),
            _little_endian(std::move(r._little_endian)),
            _ifd_list(std::move(r._ifd_list)),
            _image_info(std::move(r._image_info))
        {}

        //---------------------------------------------------------------------
        //implementation of the standard constructor
        TIFFReader::TIFFReader(const String &fname):ImageReader(fname,true)
        { 
            _read_file_info(); 
        }

        //---------------------------------------------------------------------
        //imlementation of the destructor
        TIFFReader::~TIFFReader() 
        { }

        //==================implementation of assignment operators=============
        TIFFReader &TIFFReader::operator=(TIFFReader &&r)
        {
            if(this == &r) return *this;
            ImageReader::operator=(std::move(r));
            _ifd_list = std::move(r._ifd_list);
            _image_info = std::move(r._image_info);

            return *this;
        }

        //=====================implementation of member methods================

        size_t TIFFReader::nimages() const
        {
            return _ifd_list.size();
        }

        std::vector<ImageInfo> TIFFReader::info() const
        {
            return std::vector<ImageInfo>();
        }

        void TIFFReader::open()
        {
            DataReader::open();
            _read_file_info();
        }

        void TIFFReader::close()
        {
            DataReader::close();
            _ifd_list.clear();
            _image_info.clear();

        }


    //end of namespace
    }
}
