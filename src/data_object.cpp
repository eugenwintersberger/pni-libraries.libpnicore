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
 * Created on: Jan 10, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "data_object.hpp"

namespace pni{
namespace core{

    //copy constructor
    data_object::data_object(const data_object &e):_ptr(e._ptr->clone())
    {
        //std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    }

    //-------------------------------------------------------------------------
    //move constructor
    data_object::data_object(data_object &&e):_ptr(std::move(e._ptr))
    {
        //std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    }

    //-------------------------------------------------------------------------
    TypeID data_object::type_id() const
    { 
        if(_ptr)
            return _ptr->type_id(); 
        else
            data_object::_throw_not_allocated_error(EXCEPTION_RECORD);

        return TypeID::NONE; //just to make the compiler happy
    }

    //-------------------------------------------------------------------------
    size_t data_object::rank() const 
    { 
        if(_ptr)
            return _ptr->rank(); 
        else
            data_object::_throw_not_allocated_error(EXCEPTION_RECORD);

        return 0; //just to make the compiler happy
    }
        
    //-------------------------------------------------------------------------
    shape_t data_object::shape() const 
    { 
        if(_ptr)
            return _ptr->shape(); 
        else
            data_object::_throw_not_allocated_error(EXCEPTION_RECORD);

        return shape_t(); //just to make the compiler happy
    }

    //-------------------------------------------------------------------------
    size_t data_object::size() const 
    { 
        if(_ptr) 
            return _ptr->size(); 
        else
            data_object::_throw_not_allocated_error(EXCEPTION_RECORD);

        return 0; //just to make the compiler happy
    }

    //-------------------------------------------------------------------------
    std::ostream &data_object::write(std::ostream &os) const 
    {
        if(_ptr)
            return _ptr->write(os);
        else
            data_object::_throw_not_allocated_error(EXCEPTION_RECORD);

        return os; //just to make the compiler happy
    }

    //-------------------------------------------------------------------------
    std::istream &data_object::read(std::istream &is) 
    {
        if(_ptr)
            return _ptr->read(is);
        else
            data_object::_throw_not_allocated_error(EXCEPTION_RECORD);

        return is; //just to make the compiler happy
    }

    //-------------------------------------------------------------------------
    data_value data_object::get(size_t i) const
    {
        if(_ptr)
            return _ptr->get(i);
        else
            data_object::_throw_not_allocated_error(EXCEPTION_RECORD);

        return nullptr; //just ot make the compiler happy
    }

    //-------------------------------------------------------------------------
    data_value data_object::operator[](size_t i) const
    {
        try
        {
            return get(i);
        }
        catch(MemoryNotAllocatedError &error)
        {
            error.append(EXCEPTION_RECORD);
            throw error;
        }
    }

    //-------------------------------------------------------------------------
    String data_object::type_name() const
    {
        if(_ptr)
            return _ptr->type_name();
        else
            data_object::_throw_not_allocated_error(EXCEPTION_RECORD);

        return ""; //just to make the compiler happy
    }
   
    //-------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &os,const data_object &o)
    {
        return o.write(os);
    }

    //-------------------------------------------------------------------------
    std::istream &operator>>(std::istream &is,data_object &o)
    {
        return o.read(is);
    }
//end of namespace
}
}
