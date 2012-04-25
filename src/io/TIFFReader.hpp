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
 * Declaration of class TIFFReader.
 *
 * Created on: Jun 15, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#ifndef __TIFFREADER_HPP__
#define __TIFFREADER_HPP__

#include<iostream>
#include<vector>

#include "ImageReader.hpp"
#include "ImageInfo.hpp"
#include "tiff/IFD.hpp"
#include "tiff/IFDEntry.hpp"

using namespace pni::utils;

namespace pni{
namespace io{

    /*! 
    \ingroup io_classes
    \brief TIFF file reader

    TIFFReader is an implementation of the Reader class for reading TIFF
    image files. Actually only uncompressed TIFF images are supported. 

    */
    class TIFFReader:public ImageReader {
        private:
            bool _little_endian;  //!< true if data is stored as littel endian
            std::vector<tiff::IFD> _ifds; //!< IFD list
           
            /*! \brief read image information

            Reads all the image information contained in the file.
            */
            bool _is_little_endian(std::ifstream &stream);
            void _check_if_tiff(std::ifstream &stream);
            Int32 _read_ifd_offset(std::ifstream &stream);
            size_t _read_ifd_size(std::ifstream &stream);
            
            void _read_ifds(); 
        public:
            //==========constructors and destructor========================
            //! default constructor
            TIFFReader();

            //! move constructor
            TIFFReader(TIFFReader &&r);

            //! standard constructor
            explicit TIFFReader(const String &fname);

            //copy constructor is deleted 
            TIFFReader(const TIFFReader &) = delete;
            //! destructor
            ~TIFFReader();

            //==================assignment operators=======================
            //! move assignment operator
            TIFFReader &operator=(TIFFReader &&r);

            //! copy assignment operator is deleted
            TIFFReader &operator=(const TIFFReader &r) = delete;

            //=====================class methods===========================
            virtual size_t nimages() const;

            virtual ImageInfo info(size_t i) const;

            virtual void open();

            virtual void close();

            friend std::ostream &operator<<(std::ostream &o,const TIFFReader
                    &r);

    };




//end of namespace
}
}

#endif /* TIFFREADER_HPP_ */
