//!
//! (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//! Created on: Jan 14, 2013
//!     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//!

#include <pni/core/type_erasures/value.hpp>
#include <pni/core/types/none.hpp>


namespace pni{
namespace core{

    //-------------------------------------------------------------------------
    void value::_throw_not_allocated_error(const exception_record &r)
    {
        throw memory_not_allocated_error(r, "Instance of value holds no data!");
    }

    //-------------------------------------------------------------------------
    // Implementation of constructors
    //-------------------------------------------------------------------------
    value::value():
        _ptr(new value_holder<none>(none()))
    {}

    //-------------------------------------------------------------------------
    value::value(const value &o)
        :_ptr(o._ptr ? o._ptr->clone() : new value_holder<none>(none())) 
    {}
   
    //------------------------------------------------------------------------
    value::value(value &&o)
        :_ptr(std::move(o._ptr)) 
    {
        o = value();
    }

    //-------------------------------------------------------------------------
    // Implementation of assignment operators
    //-------------------------------------------------------------------------

    //-------------------------------------------------------------------------
    value &value::operator=(const value &o)
    {
        if(this == &o) return *this;

        //we have to clone here as we cannot copy a unique pointer
        _ptr = std::unique_ptr<value_holder_interface>(o._ptr->clone());

        return *this;
    }
    
    //-------------------------------------------------------------------------
    value &value::operator=(value &&o)
    {
        if(this == &o) return *this;
        std::swap(_ptr,o._ptr);
        return *this;
    }
    
    //-------------------------------------------------------------------------
    type_id_t value::type_id() const
    {
        return _ptr->type_id();
    }

    //-------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &stream,const value &v)
    {
        return v._ptr->write(stream);
    }
    
    //-------------------------------------------------------------------------
    std::istream &operator>>(std::istream &stream,value &v)
    {
        return v._ptr->read(stream);
    }

    //-------------------------------------------------------------------------
    bool operator==(const value &a,const value &b)
    {
        return a._ptr->compare(*b._ptr);
    }

    //-------------------------------------------------------------------------
    bool operator!=(const value &a,const value &b)
    {
        return !(a==b);
    }

    //-------------------------------------------------------------------------
    type_id_t type_id(const value &v)
    {
        return v.type_id();
    }
//end of namespace
}
}
