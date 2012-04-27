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
 * ImageChannelInfo class definition
 *
 * Created on: Apr 23, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#ifndef __IMAGECHANNELINFO_HPP__
#define __IMAGECHANLELINFO_HPP__

#include "../Types.hpp"

using namespace pni::utils;

namespace pni{
namespace io{
    /*!
    \ingroup io_classes
    \brief image channel information class

    ImageChannelInfo holds information specific to a particular image channel. 
    */
    class ImageChannelInfo{
        private:
            TypeID _tid;  //!< ID of the datatype used for this channel
            size_t _bits; //!< number of bits per channel
        public:
            /*! \brief standard constructor

            \param id Typd id for the channel
            */
            ImageChannelInfo(const TypeID &id,size_t bits):
                _tid(id),
                _bits(bits)
            {}

            /*! \brief get type ID

            Returns the TypeID for the channel described by this object.
            \return type ID 
            */
            TypeID type_id() const { return _tid; }

            /*! \brief get bits 

            Return the number of bits used to store this channels data
            \return number of bits
            */
            size_t bits() const { return _bits; }

    };

//end of namespace
}
}

#endif
