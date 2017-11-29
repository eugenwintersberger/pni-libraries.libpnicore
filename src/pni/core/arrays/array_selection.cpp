//!
//! (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//!
//! This file is part of libpnicore.
//!
//! libpnicore is free software: you can redistribute it and/or modify
//! it under the terms of the GNU General Public License as published by
//! the Free Software Foundation, either version 2 of the License, or
//! (at your option) any later version.
//!
//! libpnicore is distributed in the hope that it will be useful,
//! but WITHOUT ANY WARRANTY; without even the implied warranty of
//! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//! GNU General Public License for more details.
//!
//! You should have received a copy of the GNU General Public License
//! along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
//! 
//! ===========================================================================
//!
//! Created on: Jun 1, 2012
//!     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//!

#include <pni/core/arrays/array_selection.hpp>

namespace pni{
namespace core{
    //======================implementation of general purpose methods===========
    std::ostream &operator<<(std::ostream &o,const array_selection &s)
    {
        o<<"original data:"<<std::endl;
        auto oshape = s.full_shape();
        auto offset = s.offset();
        auto stride = s.stride();
        for(size_t i=0;i<oshape.size();i++)
        {
            o<<i<<":\t"<<oshape[i]<<"\t"<<offset[i]<<"\t"<<stride[i];
            o<<std::endl;
        }
        shape_t shape = s.shape<shape_t>();
        o<<"effective shape: ( ";
        for(auto v: shape) o<<v<<" ";
        
        o<<")"<<std::endl;

        return o;
    }

    //-------------------------------------------------------------------------
    size_t rank(const array_selection &s)
    {
        return s.rank();
    }
    
    //-------------------------------------------------------------------------
    size_t size(const array_selection &s)
    {
        return s.size();
    }
//end of namespace
}
}
