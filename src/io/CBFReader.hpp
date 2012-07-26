/*
 * Declaration of class CBFReader
 *
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
 * CBFReader is the base class for readers for the CBF format and a descendant
 * of Reader (see Reader.hpp).
 *
 * Created on: Apr 19, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#ifndef CBFREADER_HPP_
#define CBFREADER_HPP_

#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdio>
#include<cstdlib>
#include<vector>

#include<boost/regex.hpp>

#include "../Types.hpp"

#include "ImageReader.hpp"
#include "cbf/DectrisReader.hpp"
#include "cbf/Types.hpp"

using namespace pni::utils;

namespace pni{
namespace io{


    /*! 
    \ingroup io_classes
    \brief base clase for CBF readers

    CBFReader is the base class for all readers of data stored in binary CIF format.
    Although CBF is standardized by the ICUR the guys from Dectris (the vendor of the Pilatus
    detector) use a kind of dialect which must be treated in a slightly different way.
    The field _header_convention in the class indicates whether or not the header is
    in standard CBF format or in the Dectris dialect.
    
    Reading a CBF file is a two step process:
    - the header is read and the information stored there kept in in a CIFBinaryHeader object
    - the binary data is read from the stream using a CBFBinStreamReader object
    The header information contains enough information to decide which binary reader to use
    and to construct the data objects which will hold the data read from the file.
    From such a point of view the header object can be consideres as a factory for the binary
    readers and the array objects holding the data.
    */
    class CBFReader: public ImageReader {
        private:
            //! string holding the detector vendor ID
            cbf::VendorID _detector_vendor;  
            //! info structure for data
            std::vector<ImageInfo> _image_info;  
            //! store data offset 
            std::streampos _data_offset;         
            //! compression type
            cbf::CompressionID _compression_type; 

            //-----------------------------------------------------------------
            /*! 
            \brief parse the file

            Parse the file and setup member variables of the class.
            */
            void _parse_file();
            
        public:
            //=================constructors and destructor==================
            //! default constructor
            CBFReader();

            //-----------------------------------------------------------------
            /*! 
            \brief construct reader object

            The name of the CBFFile is passed as a String object. During
            instantiation of class the file is parsed. Throws an exception if
            the flavor of the CBF file cannot be deduced from the header.
            \throw FileError if the CBF flavor cannot be deduced
            \param fname name of the file
            */
            CBFReader(const String &fname);

            //-----------------------------------------------------------------
            //! destructor
            virtual ~CBFReader();

            //-----------------------------------------------------------------
            //! the copy constructor is deleted
            CBFReader(const CBFReader &r) = delete;

            //====================assignment operators=======================
            //! move assignment
            CBFReader &operator=(CBFReader &&r);

            //! the copy assignment operator is deleted
            CBFReader &operator=(const CBFReader &r) = delete;

            //----------------------------------------------------------------
            virtual void close()
            {
                //close the stream
                DataReader::close();
                //reset data offset
                _data_offset = 0;
                //clear the _image_info vector
                _image_info.clear();
            }

            //-----------------------------------------------------------------
            virtual void open()
            {
                close();
                DataReader::open();
                _parse_file();
            }
           
            //-----------------------------------------------------------------
            virtual size_t nimages() const 
            { 
                return _image_info.size(); 
            }
           
            //-----------------------------------------------------------------
            virtual ImageInfo info(size_t i) const 
            {
                return _image_info[i];
            }

            //-------------------------------------------------------------
            /*!
            \brief read image

            \tparam CTYPE container type for storing data
            \throw MemoryAllocationError if container allocation failes
            \throw FileError in case of IO errors
            \param i image number to read
            \param c channel to read (default = 0)
            \return instance of CTYPE with image data
            */
            template<typename CTYPE> CTYPE image(size_t i,size_t c=0);
           
            //-------------------------------------------------------------
            /*!
            \brief read data from detector file

            Reads a single image from a detector file and stores it in an
            container of type CTYPE. Ths me
            \throws FileError if case of IO errors
            \tparam CTYPE container type holding the image data
            \tparam SizeMissmatchError if container and image size do not match

            */
            template<typename CTYPE> 
                void image(CTYPE &array,size_t i,size_t c=0);

    };

    //---------------------------------------------------------------------
    template<typename CTYPE> CTYPE CBFReader::image(size_t i,size_t c) 
    {
        ImageInfo info = _image_info[i];
        CTYPE data;
        try
        {
            data=CTYPE(info.npixels());
        }
        catch(...)
        {
            throw MemoryAllocationError(BOOST_CURRENT_FUNCTION,
                    "Allocation of container for image data failed!");
        }

        try
        {
            image(data,i,c);
        }
        catch(FileError &error)
        {
            //propagate exception
            error.append_issuer(BOOST_CURRENT_FUNCTION);
            throw error;
        }

        return data;
    }

    //---------------------------------------------------------------------
    template<typename CTYPE> 
        void CBFReader::image(CTYPE &data,size_t i,size_t c) 
    {
        //load image information and throw exception if image and container size
        //to not match
        ImageInfo inf = _image_info[i];
        if(data.size()!= inf.npixels())
        {
            SizeMissmatchError error;
            error.issuer(BOOST_CURRENT_FUNCTION);
            std::stringstream ss;
            ss<<"Container size ("<<data.size()<<") does not match image ";
            ss<<"size ("<<inf.npixels()<<")!";
            error.description(ss.str());
            throw error;
        }

        //load the channel information
        ImageChannelInfo channel = inf.get_channel(c);

        if(_detector_vendor == cbf::VendorID::DECTRIS)
        {
            if(channel.type_id() == TypeID::INT16)
                //read 16Bit signed data
                cbf::DectrisReader::read_data_byte_offset<Int16>(
                        _get_stream(),inf,data);
            if(channel.type_id() == TypeID::INT32)
                //read 32Bit signed data
                cbf::DectrisReader::read_data_byte_offset<Int32>(
                    _get_stream(),inf,data);
            else
            {
                FileError error(BOOST_CURRENT_FUNCTION,
                        "No data reader for this data type!");
                throw error;
            }

        }
        else
        {
            FileError error(BOOST_CURRENT_FUNCTION,"Unknown detector vendor!");
            throw error;
        }

    }
//end of namespace
}
}

#endif /* CBFREADER_HPP_ */
