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
#include <pni/core/type_erasures/value.hpp>

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
    value_ref &value_ref::operator=(const value &v)
    {
        type_id_t tid = v.type_id();
        _check_type(tid,EXCEPTION_RECORD);

        if(tid == type_id_t::UINT8)
            *this = v.as<uint8>();
        else if(tid == type_id_t::INT8)
            *this = v.as<int8>();
        else if(tid == type_id_t::UINT16)
            *this = v.as<uint16>();
        else if(tid == type_id_t::INT16)
            *this = v.as<int16>();
        else if(tid == type_id_t::UINT32)
            *this = v.as<uint32>();
        else if(tid == type_id_t::INT32)
            *this = v.as<int32>();
        else if(tid == type_id_t::UINT64)
            *this = v.as<uint64>();
        else if(tid == type_id_t::INT64)
            *this = v.as<int64>();
        else if(tid == type_id_t::FLOAT32)
            *this = v.as<float32>();
        else if(tid == type_id_t::FLOAT64)
            *this = v.as<float64>();
        else if(tid == type_id_t::FLOAT128)
            *this = v.as<float128>();
        else if(tid == type_id_t::COMPLEX32)
            *this = v.as<complex32>();
        else if(tid == type_id_t::COMPLEX64)
            *this = v.as<complex64>();
        else if(tid == type_id_t::COMPLEX128)
            *this = v.as<complex128>();
        else if(tid == type_id_t::STRING)
            *this = v.as<string>();
        else if(tid == type_id_t::BOOL)
            *this = v.as<bool_t>();
        else
            throw type_error(EXCEPTION_RECORD, "Unkown type!");

        return *this;
    }

    //-------------------------------------------------------------------------
    value_ref::operator value() const
    {
        return to_value(*this);
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

    //------------------------------------------------------------------------
    value to_value(const value_ref &v)
    {
        type_id_t tid = v.type_id();

        if(tid == type_id_t::UINT8)
            return value(v.as<uint8>());
        else if(tid == type_id_t::INT8)
            return value(v.as<int8>());
        else if(tid == type_id_t::UINT16)
            return value(v.as<uint16>());
        else if(tid == type_id_t::INT16)
            return value(v.as<int16>());
        else if(tid == type_id_t::UINT32)
            return value(v.as<uint32>());
        else if(tid == type_id_t::INT32)
            return value(v.as<int32>());
        else if(tid == type_id_t::UINT64)
            return value(v.as<uint64>());
        else if(tid == type_id_t::INT64)
            return value(v.as<int64>());
        else if(tid == type_id_t::FLOAT32)
            return value(v.as<float32>());
        else if(tid == type_id_t::FLOAT64)
            return value(v.as<float64>());
        else if(tid == type_id_t::FLOAT128)
            return value(v.as<float128>());
        else if(tid == type_id_t::COMPLEX32)
            return value(v.as<complex32>());
        else if(tid == type_id_t::COMPLEX64)
            return value(v.as<complex64>());
        else if(tid == type_id_t::COMPLEX128) 
            return value(v.as<complex128>());
        else if(tid == type_id_t::STRING)
            return value(v.as<string>());
        else if(tid == type_id_t::BOOL)
            return value(v.as<bool_t>());
        else 
            throw type_error(EXCEPTION_RECORD,
                    "Value is of unkown type!");

    }

//end of namespace
}
}
