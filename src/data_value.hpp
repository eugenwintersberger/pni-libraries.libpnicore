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
 * Created on: Jan 09, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once
#include<iostream>
#include<memory>

#include "Exceptions.hpp"
#include "Types.hpp"
#include "Array.hpp"
#include "TypeIDMap.hpp"

namespace pni{
namespace core{

    /*!
    \brief type erasure for POD data

    This is a very simple type erasure for POD data. Only those data types
    defined in Types.hpp in the pni core library cane be used along with this
    type erasure (a proper TypeID value must be available for a data types). 
    No additional requirements are made on a data type.  
    \code
    Float64 value = 100.243;
    data_value dv = value;
    \encode

    */
    class data_value
    {
        private:
            /*!
            \brief abstract interface for data holder

            Internal class defining the abstract interface for a data value
            holder. 
            */
            class data_value_interface
            {
                public:
                    //---------------------------------------------------------
                    //! get type id
                    virtual TypeID type_id() const = 0;

                    //---------------------------------------------------------
                    /*!
                    \brief read from memory

                    Get data from a memory location determined by mem. 
                    \param mem pointer to memory location
                    */
                    virtual void set(const void *mem) = 0;

                    //---------------------------------------------------------
                    /*!
                    \brief write to memory

                    Write the value stored by the holder to the memory location
                    determined by *mem.
                    \param mem pointer to memory where to store data
                    */
                    virtual void get(void *mem) const  = 0;

                    //---------------------------------------------------------
                    /*!
                    \brief clone 

                    Clone the actual holder object. 
                    \return pointer to new holder instance 
                    */
                    virtual data_value_interface *clone() const = 0;

            };

            template<typename T> 
                class data_value_holder : public data_value_interface
            {
                private:
                    T _value; //!< the data value
                public:
                    //---------------------------------------------------------
                    //! default constructor
                    data_value_holder():_value(T(0)) {}

                    //---------------------------------------------------------
                    //! value constructor
                    data_value_holder(T v):_value(v) {}


                    //===============public inerface implementation============
                    virtual TypeID type_id() const 
                    {
                        return TypeIDMap<T>::type_id;
                    }

                    //---------------------------------------------------------
                    virtual void set(const void *mem) 
                    {
                        T *ptr = (T*)mem;
                        _value = *ptr;
                    }

                    //---------------------------------------------------------
                    virtual void get(void *mem) const
                    {
                        T *ptr = (T*)mem;
                        *ptr = _value;
                    }

                    //---------------------------------------------------------
                    virtual data_value_interface *clone() const
                    {
                        return new data_value_holder<T>(_value);
                    }
            };

            std::unique_ptr<data_value_interface> _ptr;
        public:
            //! default constructor
            data_value():_ptr(nullptr) {}
           
            //! template constructor from value
            template<typename T> 
            data_value(T v):_ptr(new data_value_holder<T>(v)){}
            //! copy constructor
            data_value(const data_value &o):_ptr(o._ptr->clone()) {}
            //! move constructor
            data_value(data_value &&o):_ptr(std::move(o._ptr)) {}
            //==================assignment operators===========================
            //! copy assignment from value
            template<typename VT> data_value &operator=(const VT &v)
            {
                _ptr = std::unique_ptr<data_value_interface>(
                        new data_value_holder<VT>(v));

                return *this;
            }

            //-----------------------------------------------------------------
            //! copy assignment
            data_value &operator=(const data_value &o)
            {
                if(this == &o) return *this;
                _ptr = std::unique_ptr<data_value_interface>(
                        o._ptr->clone());

                return *this;
            }

            //-----------------------------------------------------------------
            //! move assignment operator
            data_value &operator=(data_value &&o)
            {
                if(this == &o) return *this;
                _ptr = std::move(o._ptr);
                return *this;
            }

            //================public member methods============================
            template<typename VT> VT as() const
            {
                VT value;
                if(_ptr)
                    _ptr->get((void *)(&value));
                else
                    throw MemoryNotAllocatedError(EXCEPTION_RECORD,
                            "Instance of data_value holds no data!");

                return value;
            }
    };

//end of namespace
}
}

