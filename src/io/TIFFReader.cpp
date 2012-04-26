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

#include <numeric>

#include "../Exceptions.hpp"
#include "../Array.hpp"
#include "../Types.hpp"
#include "../Buffer.hpp"
#include "TIFFReader.hpp"

namespace pni{
namespace io{

    //============implementation of private methods============================
    //implementation of _set_endianess
    bool TIFFReader::_is_little_endian(std::ifstream &stream)
    {
        //TIFF file and how it looks with endieness
        char buffer[2];
        stream.read(buffer,2);
        if((buffer[0]=='I')&&(buffer[1]=='I')) return true;
        if((buffer[0]=='M')&&(buffer[1]=='M')) return false;

        return false; //just to avoid compiler warnings
    }

    //-------------------------------------------------------------------------
    //implementation of check tiff
    void TIFFReader::_check_if_tiff(std::ifstream &stream)
    {
        EXCEPTION_SETUP("void TIFFReader::_check_if_tiff(std::ifstream &"
                "stream)");

        UInt16 magic;
        stream.read((char *)(&magic),2);
        if(magic!=42){
            EXCEPTION_INIT(FileError,"File "+filename()+" is not a valid "
                    "TIFF file!");
            EXCEPTION_THROW();
        }
    }
    
    //--------------------------------------------------------------------------
    //implementation of read IFD offset
    Int32 TIFFReader::_read_ifd_offset(std::ifstream &stream)
    {
        //no we need to read the IFD entries read the first IFD offset
        Int32 offset = 0;
        stream.read((char*)(&offset),4);
        return offset;
    }
    
    //-------------------------------------------------------------------------
    size_t TIFFReader::_read_ifd_size(std::ifstream &stream)
    {
        size_t size = 0;
        stream.read((char *)(&size),2);
        return size;
    }

    //-------------------------------------------------------------------------
    //implementation of _read_image_info
    void TIFFReader::_read_ifds()
    {
        EXCEPTION_SETUP("void TIFFReader::_read_ifds()");
        //obtain stream
        std::ifstream &stream = _get_stream();

        //check endianess of the data - we need to do this before all other
        //things in order to interpret binary data correctly
        _little_endian = _is_little_endian(stream);
        
        //now we check if the file is really a TIFF file
        _check_if_tiff(stream);

        //no we need to read the IFD entries read the first IFD offset
        Int32 ifd_offset = _read_ifd_offset(stream);
        if(ifd_offset == 0)
        {
            EXCEPTION_INIT(FileError,"File "+filename()+" does not "
                    "contain an IDF entry!");
            EXCEPTION_THROW();
        }

        //read IFDs from the file
        do{
            //move the stream to the staring position of the IDF
            stream.seekg(ifd_offset, std::ios::beg);

            //create the IDF from the stream - here we assume that the IFD
            //constructor returns the stream at the position where the offset of
            //the next IFD is stored.
            tiff::IFD ifd(_read_ifd_size(stream));
            for(tiff::IFDEntry &entry: ifd) 
            {
                entry = std::move(tiff::IFDEntry::create_from_stream(stream));
            }
            //store the IFD
            _ifds.push_back(ifd);

            //read next IFD offset
            ifd_offset = _read_ifd_offset(stream);
        }while(ifd_offset);
    }

    //-------------------------------------------------------------------------
    std::vector<size_t> 
        TIFFReader::_get_bits_per_sample(const tiff::IFD &ifd) const
    {
        std::vector<size_t> bits_per_sample(1);
        try
        {
            bits_per_sample =
                ifd["BitsPerSample"].value<size_t>(_get_stream());
        }catch(...)
        {
            //ok - a bilevel image has only one bit per sample and only one
            //sample per pixel 
            bits_per_sample[0] = 1; 
        }
        return bits_per_sample;
    }

    //-------------------------------------------------------------------------
    std::vector<size_t> 
        TIFFReader::_get_sample_format(const tiff::IFD &ifd) const
    {
        std::vector<size_t> sample_format(1);
        try
        {
            sample_format = ifd["SampleFormat"].value<size_t>(_get_stream());
        }
        catch(...)
        {
            sample_format[0] = 1;
        }
        return sample_format;
    }

    //---------------------------------------------------------------------
    TypeID TIFFReader::_get_type_id(size_t bps,size_t sf) const
    {
        EXCEPTION_SETUP("TypeID TIFFReader::_get_type_id(size_t bps,"
                        "size_t sf) const");

        switch(sf)
        {
            case 1:
                //unsigned integer data
                switch(bps)
                {
                    case 8: return TypeID::UINT8;
                    case 16: return TypeID::UINT16;
                    case 32: return TypeID::UINT32;
                    case 64: return TypeID::UINT64;
                    default:
                         EXCEPTION_INIT(TypeError,
                                 "Invalid unsiged integer type!");
                         EXCEPTION_THROW();
                }
                break;
            case 2:
                //signed integer data
                switch(bps)
                {
                    case 8: return TypeID::INT8;
                    case 16: return TypeID::INT16;
                    case 32: return TypeID::INT32;
                    case 64: return TypeID::INT64;
                    default:
                         EXCEPTION_INIT(TypeError,
                                 "Invalid siged integer type!");
                         EXCEPTION_THROW();
                }
                break;
            case 3: 
                //IEEE floating point data
                switch(bps)
                {
                    case 32: return TypeID::FLOAT32;
                    case 64: return TypeID::FLOAT64;
                    default:
                         EXCEPTION_INIT(TypeError,
                                 "Invalid floating point type!");
                         EXCEPTION_THROW();
                }
                break;

            default:
                //throw an exception here
                EXCEPTION_INIT(TypeError,"Cannot derive type id!");
                EXCEPTION_THROW();

        }
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
        _ifds(std::move(r._ifds))
    {}

    //---------------------------------------------------------------------
    //implementation of the standard constructor
    TIFFReader::TIFFReader(const String &fname):ImageReader(fname,true)
    { 
        _read_ifds(); 
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
        _ifds = std::move(r._ifds);

        return *this;
    }

    //=====================implementation of member methods====================

    size_t TIFFReader::nimages() const
    {
        return _ifds.size();
    }

    ImageInfo TIFFReader::info(size_t i) const 
    {
        //get the right ifd
        const tiff::IFD &ifd = _ifds[i];

        //the number of pixels in x-direction is associated with the image width
        //in TIFF
        size_t nx = ifd["ImageWidth"].value<size_t>(_get_stream())[0];
        //the number of pixels in y-direction is associated with the image
        //length in TIFF
        size_t ny = ifd["ImageLength"].value<size_t>(_get_stream())[0];

        
        //need to obtain the number of bits per sample. From this field we can
        //also obtain the number of channels. If the field BitsPerSample does
        //not exists the image is Bilevel image which is very unlikely to be
        //used for detectors :)
        std::vector<size_t> bits_per_sample(_get_bits_per_sample(ifd));

        //the other information required is the sample format for each channel
        std::vector<size_t> sample_format(_get_sample_format(ifd));

        //the information gathered so far should be enough to assemble image
        //information
        ImageInfo info(nx,ny,
                       std::accumulate(bits_per_sample.begin(),
                                       bits_per_sample.end(),0)
                      );
        //now we need to add the channels
        for(size_t i=0;i<bits_per_sample.size();i++)
        {
            ImageChannelInfo channel(_get_type_id(bits_per_sample[i],
                                                  sample_format[i])
                                    );
            info.append_channel(channel);
        }

        //assemble the ImageInfo object form the IFD
        return info;

    }

    //-------------------------------------------------------------------------
    //implementation of open
    void TIFFReader::open()
    {
        DataReader::open();
        _read_ifds();
    }

    //-------------------------------------------------------------------------
    //implementation of close
    void TIFFReader::close()
    {
        DataReader::close();
        _ifds.clear();
    }

    //=====================implementation of friend functions and operators====
    std::ostream &operator<<(std::ostream &o,const TIFFReader &r)
    {
        o<<"TIFFReader for file: "<<r.filename()<<std::endl;
        o<<"File contains: "<<r.nimages()<<" images"<<std::endl; 
        for(auto ifd: r._ifds) o<<ifd;
        return o;
    }


//end of namespace
}
}
