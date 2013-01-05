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
 * ImageInfo class implementation
 *
 * Created on: Apr 23, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#include "ImageInfo.hpp"

namespace pni{
namespace io{
       
    //---------------------------------------------------------------------
    //implementation of the standard constructor
    ImageInfo::ImageInfo(size_t nx,size_t ny):
        _nx(nx),
        _ny(ny),
        _channel_info()
    {}

    //---------------------------------------------------------------------
    //implementation of the move constructor
    ImageInfo::ImageInfo(ImageInfo &&i):
        _nx(std::move(i._nx)),
        _ny(std::move(i._ny)),
        _channel_info(std::move(i._channel_info))
    {}
    

    //---------------------------------------------------------------------
    //implementation of the copy constructor
    ImageInfo::ImageInfo(const ImageInfo &i):
        _nx(i._nx),
        _ny(i._ny),
        _channel_info(i._channel_info)
    {}

    //---------------------------------------------------------------------
    //implementation of move assignment operator
    ImageInfo &ImageInfo::operator=(ImageInfo &&i) 
    {
        if(this == &i) return *this;

        _nx = std::move(i._nx);
        _ny = std::move(i._ny);
        _channel_info = std::move(i._channel_info);

        return *this;
    }

    //---------------------------------------------------------------------
    //implementation of the copy assignment operator
    ImageInfo &ImageInfo::operator=(const ImageInfo &i)
    {
        if(this == &i) return *this;

        _nx = i._nx;
        _ny = i._ny;
        _channel_info = i._channel_info;
        return *this;
    }

    //-------------------------------------------------------------------------
    std::vector<size_t> ImageInfo::bits_per_channel() const
    {
        std::vector<size_t> result;
#ifdef NOFOREACH
        for(auto iter = _channel_info.begin(); iter != _channel_info.end();iter++)
        {
            ImageChannelInfo c = *iter;
#else
        for(auto c: _channel_info) 
        {
#endif
            result.push_back(c.bits());
        }

        return result;
    }

    //-------------------------------------------------------------------------
    std::vector<TypeID> ImageInfo::types_per_channel() const
    {
        std::vector<TypeID> types;
#ifdef NOFOREACH
        for( auto iter = _channel_info.begin();iter!=_channel_info.end();iter++)
        {
            ImageChannelInfo c=*iter;
#else
        for(auto c: _channel_info)
        {
#endif
            types.push_back(c.type_id());
        }

        return types;
    }

    //---------------------------------------------------------------------
    void ImageInfo::append_channel(const ImageChannelInfo &i)
    {
        _channel_info.push_back(i);
    }

    //---------------------------------------------------------------------
    ImageChannelInfo ImageInfo::get_channel(size_t i) const
    {
        return _channel_info[i];
    }

    //=================implementation of the output operator===============
    std::ostream &operator<<(std::ostream &o,const ImageInfo &i)
    {
        o<<"Image of size ("<<i.nx()<<" x "<<i.ny()<<"):"<<std::endl;
        o<<"Total pixels:   "<<i.npixels()<<std::endl;
        o<<"Bits per pixel: "<<i.bit_per_pixel()<<std::endl;
        o<<"Number of channels: "<<i.nchannels()<<std::endl;
        o<<"Channel information: "<<std::endl;
        for(size_t n=0;n<i.nchannels();n++)
        {
            o<<"channel "<<n<<" of type "<<i.get_channel(n).type_id();
            o<<std::endl;      
        }
        return o;
    }


//end of namespace
}
}
