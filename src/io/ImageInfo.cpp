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
 * ImageInfo class implementation
 *
 * Created on: Apr 23, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#include "ImageInfo.hpp"

namespace pni{
    namespace utils{
       
        //---------------------------------------------------------------------
        //implementation of the standard constructor
        ImageInfo::ImageInfo(size_t nx,size_t ny,size_t bits_per_pixel):
            _bits_per_pixel(bits_per_pixel),
            _nx(nx),
            _ny(ny),
            _channel_info()
        {}

        //---------------------------------------------------------------------
        //implementation of the move constructor
        ImageInfo::ImageInfo(ImageInfo &&i):
            _bits_per_pixel(std::move(i._bits_per_pixel)),
            _nx(std::move(i._nx)),
            _ny(std::move(i._ny)),
            _channel_info(std::move(i._channel_info))
        {}

        //---------------------------------------------------------------------
        //implementation of move assignment operator
        ImageInfo &ImageInfo::operator=(ImageInfo &&i) 
        {
            if(this == &i) return *this;

            _bits_per_pixel = std::move(i._bits_per_pixel);
            _nx = std::move(i._nx);
            _ny = std::move(i._ny);
            _channel_info = std::move(i._channel_info);

            return *this;
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


    //end of namespace
    }
}
