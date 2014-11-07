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

#include <pni/core/type_erasures/value_ref.hpp>

namespace pni{
namespace core{

    //-------------------------------------------------------------------------
    // Implementation of private member functions
    //-------------------------------------------------------------------------
    void value_ref::_check_pointer(const exception_record &r) const
    {
        if(!_ptr)
            throw memory_not_allocated_error(r,
                    "Instance of value_ref holds no data!");
    }

    //------------------------------------------------------------------------
    void value_ref::_check_type(type_id_t tid,const exception_record &r) const
    {
        if(type_id() != tid)
            throw type_error(r,"incompatible type - cannot return value");
    }

    //-------------------------------------------------------------------------
    // Implementation of constructors
    //-------------------------------------------------------------------------
    value_ref::value_ref():_ptr(nullptr)
    {}

    //-------------------------------------------------------------------------
    value_ref::value_ref(const value_ref &o)
        :_ptr(nullptr)
    {
        if(o._ptr) _ptr = pointer_type(o._ptr->clone());
    }

    //-------------------------------------------------------------------------
    // Implementation of assignment operators
    //-------------------------------------------------------------------------
    value_ref &value_ref::operator=(const value_ref &o)
    {
        if(this == &o) return *this;
        _ptr = pointer_type(o._ptr->clone());

        return *this;
    }

    //-------------------------------------------------------------------------
    // Implementation of member functions
    //-------------------------------------------------------------------------
    type_id_t value_ref::type_id() const
    {
        _check_pointer(EXCEPTION_RECORD);
        return _ptr->type_id();

    }

    //-------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &stream,const value_ref &v)
    {
        v._check_pointer(EXCEPTION_RECORD);
        return v._ptr->write(stream);
    }
   
    //-------------------------------------------------------------------------
    std::istream &operator>>(std::istream &stream,value_ref &v)
    {
        v._check_pointer(EXCEPTION_RECORD);
        return v._ptr->read(stream);
    }

    //------------------------------------------------------------------------
    bool operator==(const value_ref &a,const value_ref &b)
    {
        if(a._ptr && b._ptr)
            return a._ptr->compare(*b._ptr);

        return false;
    }

    //------------------------------------------------------------------------
    bool operator!=(const value_ref &a,const value_ref &b)
    {
        return !(a==b);
    }

//end of namespace
}
}
