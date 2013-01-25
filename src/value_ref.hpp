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
#pragma once
#include<iostream>
#include<memory>

#include "exceptions.hpp"
#include "types.hpp"
#include "arrays.hpp"
#include "type_id_map.hpp"
#include "value_holder.hpp"

namespace pni{
namespace core{

    /*!
    \brief type erasure for references POD data

    Unlike value this type erasure holds references to POD data created with
    std::ref. Like value the types managed by the erasure are those that are
    defined in Types.hpp and thus have a TypeID value associated with them. 
    Creating an instane is quite simple, just use
    \code
    Float64 v1 = 100.243;
    value_ref v = std::ref(v1);
    \endcode
    The idea is that it is now possible to manipulate either the original object
    or the value_ref instance. Consequently the behavior of the assignment
    operator is slightly different from that of the value class as will be shown
    in the next example
    \code
    Float32 v1 = 34;
    value_ref v = std::ref(v1); 
    //v holds now aaaa reference to v1 and thus has a value of 34

    //assigment of a simple value will change the value of value_ref as well as
    //of the original object v1
    v = 1245.2340; 

    //however we can assign a new reference with
    Complex32 x(1,2);
    v = std::ref(x);

    //now v points to x rather than to v1
    \endcode
   
    Accessing the content of an instance of value_ref is again similar to value
    \code
    Float32 v1 = 123.03;
    value_ref v = std::ref(v1);
    Float32 a = v.as<Float32>();
    \endcode
    if the type passed as a template parameter to as<> does not match the type
    of the data wrapped by the value class a TypeError exception will be thrown. 

    The value class provides input and output operators to read and write to an
    instance from streams. 
    \code
    value v = ....;
    std::cin>>v;
    std::cout<<v;
    \endcode
    Other streams are of coarse supported. It is important to note that an
    uninitialized instance of v will throw an exception if one tries to access
    data for reading. However as this class holds references ther is no such
    thing as a creation function to create an empty object. It is up to the
    programmer to do proper initialization. Furthermore it is the responsibility
    of the user to ensure that the lifetime of an object exceeds that of a
    reference pointing to it.
    */
    class value_ref
    {
        private:
            /*!
            \brief throw exception

            Static helper method that throws a MemoryNotAllcatedError if the
            type erasure holds no data and data access is requested by the user.
            \throw MemoryNotAllocatedError
            \param r exception record where the error occured.
            */
            static void _throw_not_allocated_error(const exception_record &r);

            //! pointer holding the value stored
            std::unique_ptr<value_holder_interface> _ptr;
        public:
            //================constructors and destructor======================
            //! default constructor
            value_ref():_ptr(nullptr) {}
          
            //-----------------------------------------------------------------
            //! template constructor from value
            template<typename T> value_ref(std::reference_wrapper<T> v):
                _ptr(new value_holder<std::reference_wrapper<T> >(v))
            {}

            //-----------------------------------------------------------------
            //! copy constructor
            value_ref(const value_ref &o)
            {
                if(o._ptr)
                    _ptr =
                        std::unique_ptr<value_holder_interface>(o._ptr->clone());
                else
                    _ptr = nullptr;
            }

            //-----------------------------------------------------------------
            //! move constructor
            value_ref(value_ref &&o):_ptr(std::move(o._ptr)) {}

            //==================assignment operators===========================
            /*! 
            \brief copy assignment from value

            Assign a new value to class value. 
            \code
            value v = value::create<Float32>();

            v = UInt16(12);
            \endcode
            The assignment copies the new value to an appropriate instance of
            value_holder. This means that the type changes. 
            \param v reference to the new value
            \return instance of value
            */
            template<typename T> value_ref &operator=(const T &v);

            //-----------------------------------------------------------------
            template<typename T> 
            value_ref &operator=(const std::reference_wrapper<T> &r);

            //-----------------------------------------------------------------
            //! copy assignment
            value_ref &operator=(const value_ref &o);

            //-----------------------------------------------------------------
            //! move assignment operator
            value_ref &operator=(value_ref &&o);

            //-----------------------------------------------------------------
            /*!
            \brief get the stored value

            Return the stored value as type T. If the value instance has not
            been initialized before an exception is thrown. In addition, if the
            data type passed as a template parameter does not fit the type used
            to store the data an exception will be thrown.
            \throws MemoryNotAllocatedError if value is uninitialized
            \throws TypeError if T does not match the original data type
            \return value of type T 
            */
            template<typename T> T as() const;

            //-----------------------------------------------------------------
            /*!
            \brief get type id

            Returns the ID of the stored data type. 
            \throws MemoryNotAllocatedError if value is not initialized
            \return type ID.
            */
            type_id_t type_id() const;

            friend std::ostream &operator<<(std::ostream &,const value_ref &);
            friend std::istream &operator>>(std::istream &,value_ref &);
    };

    //======================implementation of template members=================
    template<typename T> T value_ref::as() const
    {
        typedef value_holder<std::reference_wrapper<T> > holder_t;
       
        if(!_ptr) _throw_not_allocated_error(EXCEPTION_RECORD);

        if(type_id() == type_id_map<T>::type_id)
        {
            return dynamic_cast<holder_t*>(_ptr.get())->as();
        }
        throw type_error(EXCEPTION_RECORD,
                "incompatible type - cannot return value");

        return T(0); //just to make the compiler happy
    }
           
    //-------------------------------------------------------------------------
    template<typename T> 
    value_ref &value_ref::operator=(const std::reference_wrapper<T> &r)
    {
        _ptr = std::unique_ptr<value_holder_interface>(
                new value_holder<std::reference_wrapper<T> >(r));
        return *this;
    }
    
    //-------------------------------------------------------------------------
    template<typename T> value_ref &value_ref::operator=(const T &v)
    {
        typedef value_holder<std::reference_wrapper<T> > holder_t;

        if(!_ptr)
        {
            _throw_not_allocated_error(EXCEPTION_RECORD);
            return *this;
        }


        if(type_id() ==  type_id_map<T>::type_id)
        {
            dynamic_cast<holder_t*>(_ptr.get())->as().get() = v;
            return *this;
        }

        throw type_error(EXCEPTION_RECORD,
                "type does not match value_ref type");
        return *this;
    }

    //-------------------------------------------------------------------------
    /*!
    \brief stream output operator

    Writes the content of value to the output stream. An exception is thrown
    if the value is not initialized. 
    \throws MemoryNotAllocatedError if value is not initialized 
    \param stream output stream
    \param v reference to value
    \return reference to output stream
    */
    std::ostream &operator<<(std::ostream &stream,const value_ref &v);

    //-------------------------------------------------------------------------
    /*!
    \brief stream input operator

    Read data from an input stream to the value. It is important to note that
    the value must be initialized otherwise an exception will be thrown. 
    \code
    value v = value::create<UInt32>();
    std::cin>>v;
    \endcode

    \throw MemoryNotAllocatedError if value not initialized 
    \param stream input stream
    \param v value where to store data
    \return reference to input stream
    */
    std::istream &operator>>(std::istream &stream,value_ref &v);

//end of namespace
}
}

