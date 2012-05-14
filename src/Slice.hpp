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
 * Declaration of the Slice type
 *
 * Created on: May 14, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef __SLICE_HPP__
#define __SLICE_HPP__

#include <iostream>
#include <utility>

namespace pni{
namespace utils{

    class Slice
    {
        private:
            size_t _first;  //!< first index in the slice
            size_t _last;   //!< last index in the slice
            size_t _stride; //!< distance between indices
        public:
            //==============constructors and destructor========================
            //! no default constructor
            Slice() = delete;

            //! standard constructor
            Slice(size_t first,size_t last,size_t stride=1);

            //! construction from a initializer list
            Slice(const std::initializer_list<size_t> &l);

            //! destructor
            ~Slice(){}

            //===============assignment operators==============================
            Slice &operator=(const Slice &s);

            //=================public member methods===========================
            /*! \brief return the first element

            \return first element of slice
            */
            size_t first() const { return _first; }

            /*! \brief return last element 

            \return last element of slice
            */
            size_t last() const { return _last; }

            /*! \brief return stride

            \return stride of the slice
            */
            size_t stride() const { return _stride; }
    }; 

    /*! \brief compute slice size

    Computes the number of elements spanned by a slice. 
    \param s slice object 
    \return number of spanned elements
    */
    size_t size(const Slice &s);



//end of namespace
}
}


#endif
