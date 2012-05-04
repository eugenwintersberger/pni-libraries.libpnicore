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
 * Class Reader is the base class for all readers which retrieve data from
 * files and other sources.
 *
 * Created on: Apr 23, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */


#ifndef __IMAGEREADER_HPP__
#define __IMAGEREADER_HPP__

#include<iostream>
#include<fstream>
#include<string>
#include<vector>

#include "../Types.hpp"
#include "../Array.hpp"
#include "DataReader.hpp"
#include "ImageInfo.hpp"

using namespace pni::utils;

namespace pni{
namespace io{

    /*! 
    \ingroup io_classes
    \brief base class for image readers

    The ImageReader class provides the basic functionality for all other
    image readers. It opens the file and provides a stream from which to
    read data. ImageReader objects cannot be copied or copy-assigned. 
    However, they can be moved using std::move. 

    Like DataReader (from which it is derived) an ImageReader object cannot
    be instantiated using this class. All constructors and assignment
    operators are thus protected making them only available to derived
    classes.
    */
    class ImageReader:public DataReader{
        protected:
            //===================constructors and destructor===================
            //! default constructor
            ImageReader();
            // copy constructor is deleted
            ImageReader(const ImageReader &) = delete;
            //! move constructor
            ImageReader(ImageReader &&r);
            //! standard constructor taking the filename as string object
            explicit ImageReader(const String &fname,bool binary=false);
            
            //==================assignment operators===========================
            //copy assignment is deleted
            ImageReader &operator=(const ImageReader &r) = delete;

            //! move assignment operator
            ImageReader &operator=(ImageReader &&r);

        public:
            //! destructor
            virtual ~ImageReader();


            //====================methods======================================
            /*! \brief get number of images

            Returns the number of images stored in the file. This methods
            reflects the fact that many image formats can hold more than one
            image in a single file (CBF, TIFF). Although this feature is hardly 
            used for experiments it should be taken into account.  This is a 
            virtual function which must be implemented by the concrete reader 
            classes.
            \return number of images
            */
            virtual size_t nimages() const = 0;

            //-----------------------------------------------------------------
            /*! \brief get image info

            Return an instance of ImageInfo with the information of image i 
            in the image stack. This is a virtual function which must be 
            implemented by the concrete reader classes.
            \return vector with ImageInfo objects
            */
            virtual ImageInfo info(size_t i) const = 0;

            //-----------------------------------------------------------------
            /*! \brief method to read a single channel

            This method returns an object determined by ArrayType holding the 
            data from channel c (default is 0) of image i in the file.  This 
            method must be implemented by all child classes of ImageReader. It 
            is assumed that the method will allocate enough memory and 
            configure the returning object appropriately.
            \param i index of the image in the file
            \param c (default = 0) image channel to read
            \return instance of ArrayType holding the channel data
            */
            template<typename ArrayType> ArrayType image(size_t i,size_t c=0) 
            {
                EXCEPTION_SETUP("template<typename T,typename BT> "
                                 "Array<T,BT> image(size_t i=0) const");
                EXCEPTION_INIT(NotImplementedError,
                               "Method not implemented!");
                EXCEPTION_THROW();
                return ArrayType();
            }
           
            //-----------------------------------------------------------------
            /*! \brief method to read a single image channel

            This method reads the data from channle c (default = 0) of image i 
            in the file and stores it in an Array template supplied by the user. 
            The array must provide enough space to hold the data otherwise 
            exceptions will be thrown. The addvantage of this method is that it 
            does not waste time with memory allocation. It is thus useful in 
            cases where data from many files of same size must be read.
            \param array array where to store the data
            \param i index of the image in the file
            \param c (default = 0) index of the channel from which to read data.
            */
            template<typename T,template<typename,typename> class BT,typename
                Allocator> 
                void image(Array<T,BT,Allocator> &array,size_t i,size_t c=0) 
            {
                EXCEPTION_SETUP("template<typename T, template<typename> "
                        "class BT> void image(size_t i=0,Array<T,BT>"
                        "&array) const");

                EXCEPTION_INIT(NotImplementedError,
                               "Method not implemented!");
                EXCEPTION_THROW();
            }

    };


//end of namepsace
}
}


#endif 
