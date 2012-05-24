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
 * Static array template.
 *
 * Created on: 24.05.2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef __STATICARRAY_HPP__
#define __STATICARRAY_HPP__

#include "Types.hpp"
#include "Shape.hpp"
#include "StaticBuffer.hpp"

namespace pni{
namespace utils{

    template<typename T,size_t N> class StaticArray
    {
        private:
            StaticBuffer<T,N> _data' 
            Shape _shape; //!< array shape
        public:
            //================public types=====================================
            typedef T value_type;
            typedef std::shared_ptr<StaticArray<T,N> > shared_ptr;
            typedef std::unique_ptr<StaticArray<T,N> > unique_ptr;
            typedef StaticBuffer<T,N>::iterator iterator;
            typedef StaticBuffer<T,N>::const_iterator const_iterator;

            //=================constructors and destructor=====================
            //! default constructor
            StaticArray():_data(),_shape() {}

            //! copy constructor
            StaticArray(const StaticArray(


            //! default constructor


    };

//end of namespace
}
}

#endif
