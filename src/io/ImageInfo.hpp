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

    /*! 
    \ingroup io_classes
    \brief function allocated image data

    This template function allocates an array capable of holding the data for an
    image as described by an ImageInfo object.
    */
    template<typename ATYPE> ATYPE array_from_imageinfo(const ImageInfo &info)
    {
        Shape s({info.nx(),info.ny()});
        ATYPE array(s);
        return array;
    }

    /*!
    \ingroup io_classes
    \brief check array

    Checks if an array is capable of holding the data for an image described by
    an Image info. The function throws exceptions if this is not the case.
    \throws MemoryAccessError if the array is not allocated
    \throws ShapeMissmatchError if the shape of the array does not fit 
    \param info the ImageInfo object for which to check the array
    \param array he array to check
    */

    template<typename ATYPE> void array_check_from_imageinfo(const ImageInfo
            &info,const ATYPE &array)
    {
        EXCEPTION_SETUP("template<typename ATYPE> void "
                "array_check_from_imageinfo(const ImageInfo &info,const "
                "ATYPE &array)");

        //check if the array is allocated
        if(!array.is_allocated())
        {
            EXCEPTION_INIT(MemoryAccessError, "Array is not allocated!");
            EXCEPTION_THROW();
        }

        //check the shape of the array
        Shape s(array.shape());

        if(s.rank() != 2)
        {
            EXCEPTION_INIT(ShapeMissmatchError,"Array is not of rank 2!");
            EXCEPTION_THROW();
        }

        if((s.dim(0)!=info.ny()) || (s.dim(1) != info.nx()))
        {
            std::stringstream ss;
            ss<<"Array shape ("<<s.dim(1)<<","<<s.dim(0)<<") does not match ";
            ss<<"image size ("<<info.nx()<<","<<info.ny()<<")!";
            EXCEPTION_INIT(ShapeMissmatchError,ss.str());
            EXCEPTION_THROW();
        }

    }




//end of namespace
}
}

#endif
