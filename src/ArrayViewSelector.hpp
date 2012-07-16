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
 * Declaration of the ArrayView template
 *
 * Created on: Jul 12, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef __ARRAYVIEWSELECTOR_HPP__
#define __ARRAYVIEWSELECTOR_HPP__

#include "ArrayView.hpp"


namespace pni {
namespace utils {

    template<typename ATYPE,typename ...ITYPES> struct ArrayViewSelector;

    template<typename ATYPE,size_t i,typename ...ITYPES> struct
        ArrayViewSlector<ATYPE,i,ITYPES...>
    {
        typedef typename ArrayViewSelector<ATYPE,ITYPES...>::viewtype viewtype;
    };

    template<typename ATYPE,Slice s,typename ...ITYPES> struct
        ArrayViewSelector<ATYPE,s,ITYPES...>
    {
        typedef ArrayView<ATYPE> viewtype;
    };

    template<typename ATYPE,size_t i> struct ArrayViewSelector<ATYPE,i>
    {
        typedef typename ATYPE::value_type &viewtype;
    };

//end of namespace
}
}

#endif
