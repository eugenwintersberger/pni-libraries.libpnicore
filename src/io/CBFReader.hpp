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
#include "../DataObject.hpp"

#include "ImageReader.hpp"
#include "DectrisCBFReader.hpp"
#include "CBFTypes.hpp"



namespace pni{
    namespace utils{


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
                CBFDetectorVendor _detector_vendor;     //!< string holding the detector vendor ID
                std::vector<ImageInfo> _image_info; //!< info structure for data
                std::streampos _data_offset; 
                CBFCompressionType _compression_type;    //!< compression type
                void _parse_file();
                
            public:
                //=================constructors and destructor==================
                //! default constructor
                CBFReader();
                //! standard constructor

                //! The name of the CBFFile is passed as a String object.
                CBFReader(const String &fname);
                //! destructor
                virtual ~CBFReader();

                //---------------------------------------------------------------
                //delete copy constructor
                CBFReader(const CBFReader &r) = delete;

                //====================assignment operators=======================
                //! move assignment
                CBFReader &operator=(CBFReader &&r);

                //delete copy assignment
                CBFReader &operator=(const CBFReader &r) = delete;
                
                
                virtual size_t nimages() const 
                { 
                    return _image_info.size(); 
                }
                
                virtual std::vector<ImageInfo> info() const 
                {
                    return std::move(_image_info);
                }
                
                template<typename T,template<typename> class BT> 
                    Array<T,BT> image(size_t i=0) 
                {
                    EXCEPTION_SETUP("template<typename T,typename BT> "
                                     "Array<T,BT> image(size_t i=0) const");

                    ImageInfo info = _image_info[i];
                    Shape shape(2);
                    shape.dim(0,info.nx());
                    shape.dim(1,info.ny());

                    Array<T,BT> array(shape);
                    
                    image(i,array);

                    return array;
                }
                
                template<typename T,template<typename> class BT> 
                    void image(size_t i,Array<T,BT> &array) 
                {
                    EXCEPTION_SETUP("template<typename T, template<typename> "
                            "class BT> void image(size_t i=0,Array<T,BT>"
                            "&array) const");
                    
                    ImageInfo inf = _image_info[i];
                    ImageChannelInfo channel = inf.get_channel(0);

                    if(_detector_vendor == CBFDetectorVendor::DECTRIS)
                    {
                        if(channel.type_id() == TypeID::INT16)
                            DectrisCBFReader::read_data_byte_offset<Int16>(
                                    _get_stream(),inf,array);
                        if(channel.type_id() == TypeID::INT32)
                            DectrisCBFReader::read_data_byte_offset<Int32>(
                                _get_stream(),inf,array);
                        else
                        {
                            EXCEPTION_INIT(FileError,"No data reader for "
                                    "this data type!");
                        }

                    }
                    else
                    {
                        EXCEPTION_INIT(FileError,"Unknown detector vendor!");
                        EXCEPTION_THROW();
                    }

                }

        };

    //end of namespace
    }
}

#endif /* CBFREADER_HPP_ */
