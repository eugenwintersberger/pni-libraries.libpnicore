/*
 * Implementation of class TIFFStripReader
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
 * Implementation of class TIFFStripReader.
 *
 * Created on: Jun 22, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#include "../../Exceptions.hpp"
#include "StripReader.hpp"

namespace pni {
namespace io {
namespace tiff {
    //======================implementation of constructors and destructor======
    //implementation of the default constructor
    StripReader::StripReader() 
    {
    }

    //-------------------------------------------------------------------------
    //implementation of the copy constructor
    StripReader::StripReader(const StripReader &o):
        _offsets(o._offsets),
        _byte_cnts(o._byte_cnts),
        _bits_per_channel(o._bits_per_channel),
        _channel_types(o._channel_types)
    { }

    //-------------------------------------------------------------------------
    //implementation of move constructor
    StripReader::StripReader(StripReader &&o):
        _offsets(std::move(o._offsets)),
        _byte_cnts(std::move(o._byte_cnts)),
        _bits_per_channel(std::move(o._bits_per_channel)),
        _channel_types(std::move(o._channel_types))
    { }

    //------------------------------------------------------------------------
    //implementation of the standard constructor
    StripReader::StripReader(const std::vector<size_t> &offsets,
                             const std::vector<size_t> &byte_counts,
                             const std::vector<size_t> &bits_per_channel,
                             const std::vector<TypeID> &channel_types):
        _offsets(offsets),
        _byte_cnts(byte_counts),
        _bits_per_channel(bits_per_channel),
        _channel_types(channel_types)
    { }

    //-------------------------------------------------------------------------
    //implementation of the destructor
    StripReader::~StripReader() 
    { }

    //=========================implementation of assignment operators==========
    //implementation of copy assignment
    StripReader &StripReader::operator=(const StripReader &o)
    {
        if(this == &o) return *this;

        _offsets = o._offsets;
        _byte_cnts = o._byte_cnts;
        _bits_per_channel = o._bits_per_channel;
        _channel_types = o._channel_types;
        return *this;
    }

    //-------------------------------------------------------------------------
    //implementation of move assignment
    StripReader &StripReader::operator=(StripReader &&o)
    {
        if(this == &o) return *this;

        _offsets = std::move(o._offsets);
        _byte_cnts = std::move(o._byte_cnts);
        _bits_per_channel = std::move(o._bits_per_channel);
        _channel_types = std::move(o._channel_types);
        return *this;
    }

    //======================implementation of public methods===================
    StripReader StripReader::create(std::ifstream &stream,const IFD &ifd,
                                    const ImageInfo &info)
    {
       return StripReader(ifd["StripOffsets"].value<size_t>(stream),
                          ifd["StripByteCounts"].value<size_t>(stream),
                          info.bits_per_channel(),
                          info.types_per_channel());
    }

    
    //output operator
    std::ostream &operator<<(std::ostream &o,const StripReader &r)
    {
        for(size_t i=0;i<r._bits_per_channel.size();i++)
        {
            o<<"channel "<<i<<" of type "<<r._channel_types[i];
            o<<" with "<<r._bits_per_channel[i]<<" bits"<<std::endl;
        }

        o<<"Total number of strip: "<<r._offsets.size()<<std::endl;
        for(size_t i=0;i<r._offsets.size();i++)
        {
            o<<"strip "<<i<<" at offset "<<r._offsets[i];
            o<<" of size "<<r._byte_cnts[i]<<std::endl;
        }
        return o;
    }



//end of namespace
}
}
}
