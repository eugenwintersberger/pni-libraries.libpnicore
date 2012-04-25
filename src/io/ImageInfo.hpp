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
 * ImageInfo class definition
 *
 * Created on: Apr 23, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#ifndef __IMAGEINFO_HPP__
#define __IMAGEINFO_HPP__

#include<iostream>
#include<vector>

#include "../Types.hpp"
#include "ImageChannelInfo.hpp"

using namespace pni::utils;

namespace pni{
namespace io{
       
    /*! 
    \ingroup io_classes
    \brief image information type

    ImageInfo holds basic information about a particular image. 
    */
    class ImageInfo{
        private:
            size_t _bits_per_pixel; //!< number of bits per pixel
            size_t _nx;             //!< number of pixels in x-direction
            size_t _ny;             //!< number of pixels in y-direction
            std::vector<ImageChannelInfo> _channel_info; //!< channel information
        public:
            /*! \brief standard constructor

            */
            ImageInfo(size_t nx,size_t ny,size_t bits_per_pixel);

            //! move constructor
            ImageInfo(ImageInfo &&i);

            //! copy constructor
            ImageInfo(const ImageInfo &i);

            //! move assignment operator
            ImageInfo &operator=(ImageInfo &&i);

            //! copy assignment operator
            ImageInfo &operator=(const ImageInfo &i);

            //====================general class methods====================
            /*! \brief get pixels along x

            */
            size_t nx() const { return _nx; }

            /*! \brief get pixels along y

            */
            size_t ny() const { return _ny; }

            /*! \brief get total number of pixels

            */
            size_t npixels() const { return _nx*_ny;}

            /*! \brief get number of bits per pixel

            */
            size_t bit_per_pixel() const { return _bits_per_pixel; }

            /*! \brief get number of channels

            */
            size_t nchannels() const { return _channel_info.size(); }

            
            /*! \brief append a new channel
            
            */ 
            void append_channel(const ImageChannelInfo &i);

            /*! \brief get channel information

            */
            ImageChannelInfo get_channel(size_t i) const;

    };

    //! output operator
    std::ostream &operator<<(std::ostream &o,const ImageInfo &i);


//end of namespace
}
}

#endif
