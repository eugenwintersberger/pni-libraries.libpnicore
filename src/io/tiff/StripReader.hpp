/*
 * Declaration of class TIFFStripReader
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
 * Declaration of class TIFFStripReader.
 *
 * Created on: Jun 22, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#ifndef TIFFSTRIPREADER_HPP_
#define TIFFSTRIPREADER_HPP_

#include <iostream>
#include <fstream>
#include <vector>

#include "IFD.hpp"
#include "../ImageInfo.hpp"

#include "../../Types.hpp"

using namespace pni::utils;

namespace pni {
namespace io {
namespace tiff {

    //! \ingroup io_classes
    //! \brief reader for strip data in a TIFF file
    class StripReader {
    private:
        std::vector<size_t> _offsets;   //!< array with the file offsets of the strips
        std::vector<size_t> _byte_cnts; //!< array with byte counts for each strip
        std::vector<size_t> _bits_per_channel; //!< number of bits per channel
        std::vector<TypeID> _channel_types; //!< type ids of channel data

        template<typename CTYPE,typename T,template<typename> class BT> 
            void _read_interlace(size_t c,std::ifstream &stream,
                                 Array<T,BT> &array) const;

    public:
        //====================constructors and destructor======================
        //! default constructor
        StripReader();
        //! copy constructor
        StripReader(const StripReader &r);
        //! move constructor
        StripReader(StripReader &&r);
        /*! 
        \brief standard constructor

        Standard constructor for this class. 
        \param offsets vector with strip offsets
        \param byte_counts vector with byte counts for every strip
        \param bits_per_channel vector with number of pits per channel
        \param channel_types vector with TypeIDs for each channel
        */
        StripReader(const std::vector<size_t> &offsets,
                    const std::vector<size_t> &byte_counts,
                    const std::vector<size_t> &bits_per_channel,
                    const std::vector<TypeID> &channel_types);

        //! destructor
        ~StripReader();

        //====================assignemnt operators=============================
        //! copy assignment operator
        StripReader &operator=(const StripReader &r);

        //! move assignment operator
        StripReader &operator=(StripReader &&r);

        //===========static public member functions============================
        static StripReader create(std::ifstream &stream,const IFD &ifd,
                                  const ImageInfo &info);

        //=====================public member methods===========================


        //! template to read image data of various type
        template<typename ATYPE> void read(size_t c,std::ifstream &stream,ATYPE &array) {
            EXCEPTION_SETUP("template<typename ATYPE> void read(size_t c,"
                            "std::ifstream &stream,ATYPE &array)");

            //first we need to determine the datatype of the

            if(this->_channel_types[c] == TypeID::UINT8)
                this->_read_interlace<UInt8>(c,stream,array);
            else if(this->_channel_types[c] == TypeID::INT8)
                this->_read_interlace<Int8>(c,stream,array);
            else if(this->_channel_types[c] == TypeID::UINT16)
                this->_read_interlace<UInt16>(c,stream,array);
            else if(this->_channel_types[c] == TypeID::INT16)
                this->_read_interlace<Int16>(c,stream,array);
            else if(this->_channel_types[c] == TypeID::UINT32)
                this->_read_interlace<UInt32>(c,stream,array);
            else if(this->_channel_types[c] == TypeID::INT32)
                this->_read_interlace<Int32>(c,stream,array);
            else if(this->_channel_types[c] == TypeID::UINT64)
                this->_read_interlace<UInt64>(c,stream,array);
            else if(this->_channel_types[c] == TypeID::INT64)
                this->_read_interlace<Int64>(c,stream,array);
            else if(this->_channel_types[c] == TypeID::FLOAT32)
                this->_read_interlace<Float32>(c,stream,array);
            else if(this->_channel_types[c] == TypeID::FLOAT64)
                this->_read_interlace<Float64>(c,stream,array);
            else
            {
                EXCEPTION_INIT(TypeError,"StripReader cannot handle "
                                         "channel type!");
                EXCEPTION_THROW();
            }

            
        }
    };

    template<typename CTYPE,typename T,template<typename> class BT> void StripReader::
        _read_interlace(size_t channel,std::ifstream &stream,Array<T,BT> &array)
        const
    {
        //we can assume here that the buffer is already properly allocated
        size_t pix_cnt = 0;         //pixel counter
        Buffer<char> read_buffer;   //buffer where to read data to
        size_t tot_bits_per_pix = std::accumulate(this->_bits_per_channel.begin(),
                                                  this->_bits_per_channel.end(),0);

        
        //loop over all strips
        for(size_t strip=0;strip<this->_offsets.size();strip++)
        {
            //set stream to strip starting position
            stream.seekg(this->_offsets[strip],std::ios::beg);

            //allocate buffer memory
            read_buffer.allocate(this->_byte_cnts[strip]);

            //read the buffer
            stream.read(read_buffer.ptr(),read_buffer.size());

            //now as we have all the strip data in the memory we need to select
            //the proper channel data from it
            //determine the number of pixels in the strip
            size_t npix = 8*this->_byte_cnts[strip]/tot_bits_per_pix;
            //loop over all pixels
            char *ptr = read_buffer.ptr();
            for(size_t i=0;i<npix;i++)
            {
                //loop over all channels
                for(size_t c=0;c<this->_bits_per_channel.size();c++)
                {
                    //extract data from the stream
                    if(c==channel) array[pix_cnt] =  (T)((CTYPE)(*ptr));
                    //continue with the pointer
                    ptr += this->_bits_per_channel[c]/8;
                }

                //increment the pixel counter
                pix_cnt++;
            }
        }


    }


//end of namespace
}
}
}

#endif /* TIFFSTRIPREADER_HPP_ */
