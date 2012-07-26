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
#include<boost/current_function.hpp>

#include "ImageReader.hpp"
#include "ImageInfo.hpp"
#include "tiff/IFD.hpp"
#include "tiff/IFDEntry.hpp"
#include "tiff/StripReader.hpp"

using namespace pni::utils;

namespace pni{
namespace io{

    /*! 
    \ingroup io_classes
    \brief TIFF file reader

    TIFFReader is an implementation of the Reader class for reading TIFF
    image files. Actually only uncompressed TIFF images are supported. 
    The copy constructor and the copy assignment operator are deleted to prevent
    copy construction of this object. 
    */
    class TIFFReader:public ImageReader {
        private:
            bool _little_endian;  //!< true if data is stored as little endian
            std::vector<tiff::IFD> _ifds; //!< IFD list
          
            //=====================private methods=============================
            /*! \brief check binary encoding

            This private method checks if the image is encoded as TIFF or not.
            The method makes no assumption about the position of the stream
            pointer. It moves it automatically to the correction position and
            reads the data from there. Afterwards the stream will be reset to
            the position where it originally was.
            True is returned when the TIFF file contains little endian encoded
            data and false otherwise.
            \return true file data is encoded as little endian
            */
            static bool _is_little_endian(std::ifstream &stream);

            //-----------------------------------------------------------------
            /*! \brief check if image is TIFF

            Checks if the stream belongs to a TIFF image. If the file is not a
            TIFF file an exception will be thrown. No assumption is made about
            the position of the stream. The methods adjusts the stream to the
            proper positions and resets it to its original position once
            finished.
            \throw FileError if stream is not a TIFF file
            */
            static void _check_if_tiff(std::ifstream &stream);

            //------------------------------------------------------------------
            /*! \brief read IFD offset

            Method obtains the offset for an IFD from the actual stream
            position.
            \return IFD offset
            */
            static Int32 _read_ifd_offset(std::ifstream &stream);

            //-----------------------------------------------------------------
            /*! \brief read IFD size

            Reads the number of IFD entries from the actual stream position
            \return number of IFD entries
            */
            static size_t _read_ifd_size(std::ifstream &stream);

            //-----------------------------------------------------------------
            /*! \brief get bits per sample

            Returns a vector whose length corresponds to the number of channels
            in the image. Each element holds the number of bits used to store
            the data for the corresponding channel.
            \param stream image file stream
            \param ifd IFD of the image
            \return vector with pixels per channel
            */
            static std::vector<size_t> 
                _get_bits_per_sample(std::ifstream &stream,const tiff::IFD &ifd);

            //-----------------------------------------------------------------
            /*! \brief get sample format

            The sample format decides how to interpret the bits stored for each
            channel. Depending on its value the channel data will be interpreted
            as unsigned integer, signed integer, or IEEE floating point number.
            \param stream image file stream
            \param ifd IFD of the image in the file
            \return vector with sample formats for each channel
            */
            static std::vector<size_t> 
                _get_sample_format(std::ifstream &stream,const tiff::IFD &ifd);

            //-----------------------------------------------------------------
            /*! \brief determine channel data type

            Static method to deduce the type of an image channel from the sample
            format and the number of bits used for the channel data. If the type
            could not be deduced an exception will be thrown.
            \throws TypeError if the type cannot be deduced from the data
            \param bps number of bits per sample
            \param sf sample format
            \return TypeID of the corresponding type
            */
            static TypeID _get_type_id(size_t bps,size_t sf);
           
            //-----------------------------------------------------------------
            /*! \brief read IDF data from the file

            Read all the IDF data from the file and store them in the _idfs
            private member variable.
            */
            void _read_ifds(); 

            //----------------------------------------------------------------
            /*! \brief read data from the file
            

            */
            template<typename CTYPE> 
                void _read_data(size_t i,size_t c,CTYPE &data);
        public:
            //==========constructors and destructor========================
            //! default constructor
            TIFFReader();

            //! move constructor
            TIFFReader(TIFFReader &&r);

            //! standard constructor
            explicit TIFFReader(const String &fname);

            //! copy constructor is deleted 
            TIFFReader(const TIFFReader &) = delete;
            //! destructor
            ~TIFFReader();

            //==================assignment operators=======================
            //! move assignment operator
            TIFFReader &operator=(TIFFReader &&r);

            //! copy assignment operator is deleted
            TIFFReader &operator=(const TIFFReader &r) = delete;

            //=====================class methods===========================
            /*! \brief get number of images

            Return the number of images stored in the image file.
            \return number of images
            */
            virtual size_t nimages() const;

            //-----------------------------------------------------------------
            /*! \brief get ImageInfo 

            Return an instance of ImageInfo for image i stored in the file.
            \return instance of ImageInfo
            */
            virtual ImageInfo info(size_t i) const;

            //-----------------------------------------------------------------
            virtual void open();

            //-----------------------------------------------------------------
            virtual void close();

            //-----------------------------------------------------------------
            /*! \brief read image data

            Template method to read image data from the file. The returns an
            instance of the the template Array<T,BT> and does all the
            configuration and memory allocation work for this object.
            \throws MemoryAllocationError if array allocation fails
            \param i index of the image in the file
            \param c index of the image channel to read
            \return instance of an array template
            */
            template<typename CTYPE> CTYPE image(size_t i,size_t c=0) 
            {
                ImageInfo info = this->info(i);
                CTYPE data;
                try { data = CTYPE(info.npixels()); }
                catch(...)
                {
                    throw MemoryAllocationError(BOOST_CURRENT_FUNCTION,
                            "Allocation of image data container failed!");
                }

                //here we read the data
                this->_read_data(i,c,data);
                return data;
            }

            //----------------------------------------------------------------- 
            /*! \brief read image data

            Reads the image data from the file and stores it in a user supplied
            array object. The method checks if the arrays shape and allocation
            state fits the requirements of the image. The advantage of this
            method is that memory allocation must be done only once before this
            method is called. This increases performance dramatically in
            particular if many images of equal size should be read.
            \throws SizeMissmatchError if the size of the container does not
            match the number of pixels stored in the image
            \param data instance of CTYPE where data will be stored
            \param i index of the image in the file
            \param c index of the image channel to read
            */
            template<typename CTYPE> 
                void image(CTYPE &data,size_t i,size_t c=0) 
            {
                ImageInfo info = this->info(i);
                if(data.size() != info.npixels())
                {
                    SizeMissmatchError error;
                    error.issuer(BOOST_CURRENT_FUNCTION);
                    std::stringstream ss;
                    ss<<"Container size ("<<data.size()<<") does not match";
                    ss<<"number of pixels ("<<info.npixels()<<")!";
                    error.description(ss.str());
                }

                //read data
                _read_data(i,c,data);
            }
           
            //! output operator of an TIFFReader object
            friend std::ostream &operator<<(std::ostream &o,const TIFFReader
                    &r);

    };

    template<typename CTYPE> 
        void TIFFReader::_read_data(size_t i,size_t c,CTYPE &data)
    {
        //obtain the proper IFD
        tiff::IFD &ifd = this->_ifds.at(i);
        std::ifstream &stream = this->_get_stream();

        //assume here that the image is stored using strips
        tiff::StripReader reader(tiff::StripReader::create(stream,ifd,this->info(i)));
        std::cout<<reader<<std::endl;

        reader.read(c,stream,data);
        
    }
//end of namespace
}
}

#endif /* TIFFREADER_HPP_ */
