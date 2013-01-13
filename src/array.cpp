/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpnicore.
 *
 * libpnicore is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpnicore is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Created on: Jan 11, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "array.hpp"

namespace pni{
namespace core{

    //copy constructor
    array::array(const array &e):_ptr(e._ptr->clone())
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
    TypeID array::type_id() const
    { 
        if(_ptr)
            return _ptr->type_id(); 
        else
            array::_throw_not_allocated_error(EXCEPTION_RECORD);

        return TypeID::NONE; //just to make the compiler happy
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
            return (*_ptr)[i];
        else
            array::_throw_not_allocated_error(EXCEPTION_RECORD);

        return value::create<Int16>(); //just to make the compiler happy
    }

    //-------------------------------------------------------------------------
    String array::type_name() const
    {
        if(_ptr)
            return _ptr->type_name();
        else
            array::_throw_not_allocated_error(EXCEPTION_RECORD);

        return ""; //just to make the compiler happy
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

//end of namespace
}
}
