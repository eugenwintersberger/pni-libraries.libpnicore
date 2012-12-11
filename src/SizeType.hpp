/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 * Created on: May 31, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

namespace pni{
namespace utils{

    /*! 
    \ingroup util_classes
    \brief type computes the array size

    The idea of this type is to compute the size of a static array or shape
    object. Indeed it computes the product of all the template parameters.
    \code
    std::cout<<SizeType<4,5,3>::size<<std::endl;
    \endcode
    will output 60 on the terminal.
    */
    template<size_t ...indices> class SizeType;

    /*! 
    \ingroup util_classes
    \brief specialization of SizeType

    The first real specialization of the SizeType template. 
    */
    template<size_t i,size_t ...indices> class SizeType<i,indices...>
    {
        public:
            //!< size
            static const size_t size = i*SizeType<indices...>::size;
    };

    //! type breaking the template recursion
    template<> class SizeType<>
    {
        public:
            static const size_t size = 1; //!< size
    };


//end of namespace
}
}
