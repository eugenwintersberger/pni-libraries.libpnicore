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

namespace pni{
namespace utils{

    template<typename T,size_t N> class StaticArray
    {
        private:
            T _data[N]; //!< static array data
            Shape _shape; //!< array shape
        public:
            //================public types=====================================
            typedef T value_type 
            //! default constructor
            StaticArray():_shape() {}

            //! default constructor


    };

//end of namespace
}
}

#endif
