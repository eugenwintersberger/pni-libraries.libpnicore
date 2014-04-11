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
// ============================================================================
//
// Created on: Jan 11, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once
#include<iostream>
#include<memory>

#include "../error/exceptions.hpp"
#include "../types/types.hpp"
#include "../arrays.hpp"
#include "value_holder.hpp"

namespace pni{
namespace core{

    //!
    //! \ingroup type_erasure_classes
    //!\brief type erasure for POD data
    //!
    //! This is a very simple type erasure for POD data. Only those data types
    //! defined in Types.hpp in the pni core library cane be used along with 
    //! this type erasure (a proper TypeID value must be available for a data 
    //! types).  No additional requirements are made on a data type.  
    //! Creating an instane is quite simple, just use
    //!
    //! \code
    //! float64 v1 = 100.243;
    //! value v = v1;
    //! \endcode
    //! or
    //! \code
    //! value v = float64(1023); 
    //! \endcode
    //! An arbitrary type can be assigned at runtime
    //! \code
    //! value v;
    //! .... code omitted ...
    //! v = 1245.2340;
    //! \endcode
    //! In this case the original value whill be overwritten. To obtain its 
    //! original value use the as<> template member function of the value 
    //! class
    //! \code
    //! value v = float32(1243.4029);
    //! float32 a = v.as<float32>();
    //! \endcode
    //! if the type passed as a template parameter to as<> does not match the 
    //! type of the data wrapped by the value class a TypeError exception will 
    //! be thrown. 
    //!
    //! The value class provides input and output operators to read and write 
    //! to an instance from streams. 
    //! \code
    //! value v = ....;
    //! std::cin>>v;
    //! std::cout<<v;
    //! \endcode
    //! Other streams are of coarse supported. It is important to note that an
    //! uninitialized instance of v will throw an exception if one tries to 
    //! access data for reading. Thus a static method is provided by the class 
    //! to create a new instance of value for a particular data type
    //! \code
    //! value v = value::create<float32>();
    //! \endcode
    //!
    class value
    {
        private:
            //!
            //! \brief throw exception
            //!
            //! Static helper method that throws a MemoryNotAllcatedError if 
            //! the type erasure holds no data and data access is requested by 
            //! the user.
            //!
            //! \throw memory_not_allocated
            //! \param r exception record where the error occured.
            //!
            static void _throw_not_allocated_error(const exception_record &r);

            //! pointer holding the value stored
            std::unique_ptr<value_holder_interface> _ptr;
        public:
            //================constructors and destructor======================
            //! default constructor
            value():_ptr(nullptr) {}
          
            //-----------------------------------------------------------------
            //! template constructor from value
            template<typename T> value(T v):_ptr(new value_holder<T>(v)){}

            //-----------------------------------------------------------------
            //! copy constructor
            value(const value &o):_ptr(o._ptr ? o._ptr->clone() : nullptr) {}

            //-----------------------------------------------------------------
            //! move constructor
            value(value &&o):_ptr(std::move(o._ptr)) {}

            //-----------------------------------------------------------------
            //!
            //! \brief static creation method
            //!
            //! If an instance of value should be created without copying an
            //! existing variable or a temporary object no memory will be 
            //! allocated and thus every access to the data would lead to a
            //! memory_not_allocated exception. This static method allows to
            //! create a default object of a particular type. 
            //! \code
            //! value v = value::create<float128>();
            //! \endcode
            //! \tparam T type for which to create the value object
            //! \return instance of value for type T
            //!
            template<typename T> static value create() { return value(T()); }

            //==================assignment operators===========================
            //! 
            //! \brief copy assignment from value
            //!
            //! Assign a new value to class value. 
            //! \code
            //! value v = value::create<float32>();
            //! 
            //! v = uint16(12);
            //! \endcode
            //! The assignment copies the new value to an appropriate 
            //! instance of value_holder. This means that the type changes. 
            //! 
            //! \param v reference to the new value
            //! \return instance of value
            //!
            template<typename VT> value &operator=(const VT &v);

            //-----------------------------------------------------------------
            //! copy assignment
            value &operator=(const value &o);

            //-----------------------------------------------------------------
            //! move assignment operator
            value &operator=(value &&o);

            //-----------------------------------------------------------------
            //!
            //! \brief get the stored value
            //!
            //! Return the stored value as type T. If the value instance has 
            //! not been initialized before an exception is thrown. In 
            //! addition, if the data type passed as a template parameter 
            //! does not fit the type used to store the data an exception 
            //! will be thrown.
            //!
            //! \throws memory_not_allocate_error if value is uninitialized
            //! \throws type_error if T does not match the original data type
            //! \return value of type T 
            //!
            template<typename T> T as() const;

            //-----------------------------------------------------------------
            //!
            //! \brief get type id
            //!
            //! Returns the ID of the stored data type. 
            //! 
            //! \throws memory_not_allocated_error if value is not initialized
            //! \return type ID.
            //!
            type_id_t type_id() const;

            //-----------------------------------------------------------------
            friend std::ostream &operator<<(std::ostream &stream,
                                            const value &v);

            //----------------------------------------------------------------
            friend std::istream &operator>>(std::istream &stream,
                                            value &v);
    };

    //=====================implementation of template member functions=========
    template<typename T> T value::as() const
    {
        if(!_ptr) _throw_not_allocated_error(EXCEPTION_RECORD);

        if(type_id() == type_id_map<T>::type_id)
        {
            return dynamic_cast<value_holder<T>*>(_ptr.get())->as();
        }
        throw type_error(EXCEPTION_RECORD,
                "incompatible type - cannot return value");

        return T(0); //just to make the compiler happy
    }

    //-------------------------------------------------------------------------
    template<typename VT> value &value::operator=(const VT &v)
    {
        _ptr = std::unique_ptr<value_holder_interface>(
                new value_holder<VT>(v));

        return *this;
    }

    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_erasure_classes
    //! \brief stream output operator
    //!
    //! Writes the content of value to the output stream. An exception is 
    //! thrown if the value is not initialized. 
    //! 
    //! \throws memory_allocation_error if value is not initialized 
    //! \param stream output stream
    //! \param v reference to value
    //! \return reference to output stream
    //!
    std::ostream &operator<<(std::ostream &stream,const value &v);

    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_erasure_classes
    //! \brief stream input operator
    //!
    //! Read data from an input stream to the value. It is important to note 
    //! that the value must be initialized otherwise an exception will be 
    //! thrown. 
    //! \code
    //! value v = value::create<uint32>();
    //! std::cin>>v;
    //! \endcode
    //!
    //! \throw memory_not_allocated_error if value not initialized 
    //! \param stream input stream
    //! \param v value where to store data
    //! \return reference to input stream
    //!
    std::istream &operator>>(std::istream &stream,value &v);

    //-------------------------------------------------------------------------
    //! 
    //! \ingroup type_erasure_classes
    //! \brief get type ID
    //! 
    //! Overload of type_id to obtain the type ID of the element stored in the 
    //! type erasure.
    //! 
    //! \param rv reference to value 
    //! \return type ID of the erased type
    //!
    type_id_t type_id(const value &rv);

//end of namespace
}
}

