//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpnicore.
//
// libpnicore is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpnicore is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
//
// ===========================================================================
//
// Created on: Jan 11, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/core/type_erasures/array.hpp>

namespace pni{
namespace core{

    //copy constructor
    array::array(const array &e):_ptr(e._ptr ? e._ptr->clone():nullptr)
    {
        //std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    }

    //-------------------------------------------------------------------------
    //move constructor
    array::array(array &&e):_ptr(std::move(e._ptr))
    {
        //std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    }

    //-------------------------------------------------------------------------
    //copy assignment operator
    array &array::operator=(const array &a)
    {
        if(&a == this) return *this;

        this->_ptr = std::unique_ptr<array_holder_interface>(a._ptr->clone());
        return *this;
    }

    //-------------------------------------------------------------------------
    //move assignment operator
    array &array::operator=(array &&a)
    {
        if(&a == this) return *this;

        this->_ptr = std::move(a._ptr);
        return *this;
    }

    //-------------------------------------------------------------------------
    type_id_t array::type_id() const
    { 
        if(_ptr)
            return _ptr->type_id(); 
        else
            array::_throw_not_allocated_error(EXCEPTION_RECORD);

        return type_id_t::NONE; //just to make the compiler happy
    }

    //-------------------------------------------------------------------------
    size_t array::rank() const 
    { 
        if(_ptr)
            return _ptr->rank(); 
        else
            array::_throw_not_allocated_error(EXCEPTION_RECORD);

        return 0; //just to make the compiler happy
    }
        
    //-------------------------------------------------------------------------
    shape_t array::shape() const 
    { 
        if(_ptr)
            return _ptr->shape(); 
        else
            array::_throw_not_allocated_error(EXCEPTION_RECORD);

        return shape_t(); //just to make the compiler happy
    }

    //-------------------------------------------------------------------------
    size_t array::size() const 
    { 
        if(_ptr) 
            return _ptr->size(); 
        else
            array::_throw_not_allocated_error(EXCEPTION_RECORD);

        return 0; //just to make the compiler happy
    }


    //-------------------------------------------------------------------------
    std::ostream &array::write(std::ostream &os) const 
    {
        if(_ptr)
            return _ptr->write(os);
        else
            array::_throw_not_allocated_error(EXCEPTION_RECORD);

        return os; //just to make the compiler happy
    }

    //-------------------------------------------------------------------------
    std::istream &array::read(std::istream &is) 
    {
        if(_ptr)
            return _ptr->read(is);
        else
            array::_throw_not_allocated_error(EXCEPTION_RECORD);

        return is; //just to make the compiler happy
    }

    //-------------------------------------------------------------------------
    value array::operator[](size_t i) const
    {
        if(_ptr)
            return ((const array_holder_interface&)(*_ptr))[i];
        else
            array::_throw_not_allocated_error(EXCEPTION_RECORD);

        return value::create<int16>(); //just to make the compiler happy
    }

    //-------------------------------------------------------------------------
    value array::at(size_t i) const
    {
        if(_ptr)
            return _ptr->at(i);
        else
            array::_throw_not_allocated_error(EXCEPTION_RECORD);

        return value::create<int16>(); //just to make the compiler happy
    }

    //-------------------------------------------------------------------------
    value_ref array::operator[](size_t i) 
    {
        if(_ptr)
            return (*_ptr)[i];
        else
            array::_throw_not_allocated_error(EXCEPTION_RECORD);

        return value_ref(); //just to make the compiler happy
    }

    //-------------------------------------------------------------------------
    value_ref array::at(size_t i)
    {
        if(_ptr)
            return _ptr->at(i);
        else
            array::_throw_not_allocated_error(EXCEPTION_RECORD);

        return value_ref(); //just to make the compiler happy
    }

    //-------------------------------------------------------------------------
    string array::type_name() const
    {
        if(_ptr)
            return _ptr->type_name();
        else
            array::_throw_not_allocated_error(EXCEPTION_RECORD);

        return ""; //just to make the compiler happy
    }

    //-------------------------------------------------------------------------
    const void *array::data() const
    {
        if(_ptr)
            return _ptr->ptr();
        else
            array::_throw_not_allocated_error(EXCEPTION_RECORD);

        return nullptr;
    }
    
    //-------------------------------------------------------------------------
    void *array::data() 
    {
        if(_ptr)
            return const_cast<void*>(_ptr->ptr());
        else
            array::_throw_not_allocated_error(EXCEPTION_RECORD);

        return nullptr;
    }
   
    //-------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &os,const array &o)
    {
        return o.write(os);
    }

    //-------------------------------------------------------------------------
    std::istream &operator>>(std::istream &is,array &o)
    {
        return o.read(is);
    }

    //-------------------------------------------------------------------------
    type_id_t type_id(const array &a)
    {
        return a.type_id();
    }
//end of namespace
}
}
