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
 * Created on: Jan 08, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once
#include<iostream>
#include<memory>

#include "Exceptions.hpp"
#include "Types.hpp"
#include "Array.hpp"
#include "data_value.hpp"

namespace pni{
namespace core{

    /*!
    \brief type erasure for data objects

    This is a type erasure for virtually all objects in pnicore that hold data.
    It provides a very simple interface to access this data.
    */
    class data_object //the type erasure
    {
        private:

            //-----------------------------------------------------------------
            /*!
            \brief interface class

            Internal class that defines the interface of the holder class
            */
            class data_object_interface  
            {
                public:
                    /*!
                    \brief return type id 

                    Return the type ID of the held object.
                    \return type id
                    */
                    virtual TypeID type_id() const = 0;
                    
                    //---------------------------------------------------------
                    /*!
                    \brief get poiter

                    Provide a const pointer of type void to the data stored in
                    the original object.
                    \return const pointer to void
                    */
                    //not yet implemented
                    //virtual const void *ptr() const = 0;

                    //---------------------------------------------------------
                    /*!
                    \brief get rank

                    Return the rank of the data stored. If the rank is 0 the
                    data is a scalar. In all other cases we assume the data to
                    be a multidimensional array.
                    \return rank (number of dimensions)
                    */
                    virtual size_t rank() const = 0;

                    //---------------------------------------------------------
                    /*!
                    \brief get shape

                    Return the shape of the data. This is the number of
                    elements along each dimension. In the case of a scalar the
                    shape is empty (size() == 0).
                    \return shape of data
                    */
                    virtual shape_t shape() const = 0;

                    //---------------------------------------------------------
                    /*!
                    \brief get size

                    Return the size of the original data. This is the number of
                    elements of a particular type (determined by the type id). 
                    \return size
                    */
                    virtual size_t size() const = 0;

                    //---------------------------------------------------------
                    /*!
                    \brief write data 

                    Write data to a standard  C++ stream.
                    \param os reference to output stream
                    \return reference to output stream
                    */
                    virtual std::ostream &write(std::ostream &os) const = 0;

                    //---------------------------------------------------------
                    /*!
                    \brief read data

                    Read data from a standard C++ stream.
                    \param is reference to input stream
                    \return reference to input stream
                    */
                    virtual std::istream &read(std::istream &is) = 0;

                    //---------------------------------------------------------
                    /*!
                    \brief clone yourself

                    This member function clones the wrapped object. This is
                    particullary important when the resulting type earsure shall
                    be copied.
                    \return pointer to new interface instance
                    */
                    virtual data_object_interface *clone() const = 0;


                    //---------------------------------------------------------
                    /*!
                    \brief read value

                    Function reads a value from the wrapped object and stores it
                    to the memory address determined by *value. The function
                    assumes that there is enough memory available
                    \param i element index
                    \param value pointer to memory location
                    */
                    virtual data_value get(size_t i) = 0;

                    //---------------------------------------------------------
                    /*!
                    \brief write value

                    Write a value from address *value to position i in the
                    wrapped object. The data stored at *value will be casted to
                    the internal data type of the wrapped object. 
                    \param i element index
                    \param value memory location from where to read data
                    */
                    virtual void set(size_t i,const data_value &value) = 0;

            };

            //-----------------------------------------------------------------
            //holder template - implementing the interface
            template<typename OT> 
            class data_object_holder:public data_object_interface
            {
                public:
                    OT _object; //!< the original object 
                public:
                    //=============constructors and destructor=================
                    //construct by copying o
                    data_object_holder(const OT &o):_object(o) {}

                    //---------------------------------------------------------
                    //construct by moving o
                    data_object_holder(OT &&o):_object(std::move(o)) {}

                    //---------------------------------------------------------
                    //copy constructor
                    data_object_holder(const data_object_holder<OT> &o):
                        _object(o._object) 
                    {}

                    //---------------------------------------------------------
                    //move constructor
                    data_object_holder(data_object_holder<OT> &&o):
                        _object(std::move(o._object)) 
                    {}

                    virtual data_object_interface *clone() const 
                    {
                        return new data_object_holder<OT>(_object);
                    }

                    //===============public member functions===================
                    virtual TypeID type_id() const{ return OT::type_id; }
                    
                    //---------------------------------------------------------
                    virtual size_t rank() const { return _object.rank(); }

                    //---------------------------------------------------------
                    virtual shape_t shape() const 
                    {
                        return _object.template shape<shape_t>();
                    }

                    //---------------------------------------------------------
                    virtual size_t size() const { return _object.size(); }

                    //---------------------------------------------------------
                    virtual data_value get(size_t i)
                    {
                        return data_value(*(_object.begin()+i)); 
                    }

                    //---------------------------------------------------------
                    virtual void set(size_t i,const data_value &value)
                    {
                        *(_object.begin()+i) = value.template as<typename OT::value_type>();
                    }

                    //---------------------------------------------------------
                    virtual std::ostream &write(std::ostream &os) const 
                    {
                        os<<_object;

                        return os;
                    }

                    //---------------------------------------------------------
                    virtual std::istream &read(std::istream &is) 
                    {
                        is>>_object; 

                        return is;
                    }

            };
            
            static void _throw_not_allocated_error(const ExceptionRecord &r)
            {
                throw MemoryNotAllocatedError(r,
                        "Instance of data_object holds no data!");
            }

            std::unique_ptr<data_object_interface> _ptr; //pointer to holder
        public:
            //===================constructors and destructor===================
            /*!
            \brief copy original object

            This constructor creates a type erasure by copying the original data
            to the internal object.
            \tparam T type of the object. 
            \param o const reference to the original object
            */
            template<typename T,
                     //this template expression is necessary to avoid that this
                     //constructor is callend when data_object itself is to be
                     //copied (see below for the correct copy constructor)
                     typename  = typename std::enable_if<
                                       !std::is_same<data_object,typename
                                       std::remove_reference<T>::type >::value 
                                       >::type
                    > 
            data_object(const T &o):
                _ptr(new data_object_holder<T>(o))
            {
                //std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
            }

            //------------------------------------------------------------------
            /*!
            \brief move original object

            Constructor moves the original object.
            \tparam T original type
            \param o rvalue reference to the original object
            */
            template<typename T,
                     //this template expression is necessary to avoid that this
                     //constructor is used when a data_object by itself is to be
                     //moved (seel below for the correct move constructor)
                     typename = typename std::enable_if<
                                       !std::is_same<data_object,typename
                                       std::remove_reference<T>::type >::value 
                                       >::type
                    > 
            data_object(T &&o):
                _ptr(new data_object_holder<typename std::remove_cv<
                                typename std::remove_reference<T>::type>::type>
                                (std::forward<T>(o)))
            {
                //std::cout<<BOOST_CURRENT_FUNCTION<<std::endl; 
            }


            //------------------------------------------------------------------
            //copy constructor
            data_object(const data_object &e):_ptr(e._ptr->clone())
            {
                //std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
            }

            //------------------------------------------------------------------
            //move constructor
            data_object(data_object &&e):_ptr(std::move(e._ptr))
            {
                //std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
            }


            //=====================public member functions=====================
            TypeID type_id() const
            { 
                if(_ptr)
                    return _ptr->type_id(); 
                else
                    data_object::_throw_not_allocated_error(EXCEPTION_RECORD);

                return TypeID::NONE; //just to make the compiler happy
            }
            
            //-----------------------------------------------------------------
            size_t rank() const 
            { 
                if(_ptr)
                    return _ptr->rank(); 
                else
                    data_object::_throw_not_allocated_error(EXCEPTION_RECORD);

                return 0; //just to make the compiler happy
            }

            //-----------------------------------------------------------------
            shape_t shape() const 
            { 
                if(_ptr)
                    return _ptr->shape(); 
                else
                    data_object::_throw_not_allocated_error(EXCEPTION_RECORD);

                return shape_t(); //just to make the compiler happy
            }

            //-----------------------------------------------------------------
            size_t size() const 
            { 
                if(_ptr) 
                    return _ptr->size(); 
                else
                    data_object::_throw_not_allocated_error(EXCEPTION_RECORD);

                return 0; //just to make the compiler happy
            }

            //-----------------------------------------------------------------
            std::ostream &write(std::ostream &os) const 
            {
                if(_ptr)
                    return _ptr->write(os);
                else
                    data_object::_throw_not_allocated_error(EXCEPTION_RECORD);

                return os; //just to make the compiler happy
            }

            //-----------------------------------------------------------------
            std::istream &read(std::istream &is) 
            {
                if(_ptr)
                    return _ptr->read(is);
                else
                    data_object::_throw_not_allocated_error(EXCEPTION_RECORD);

                return is; //just to make the compiler happy
            }

            //-----------------------------------------------------------------
            data_value get(size_t i) const
            {
                if(_ptr)
                    return _ptr->get(i);
                else
                    data_object::_throw_not_allocated_error(EXCEPTION_RECORD);
            }

            //-----------------------------------------------------------------
            template<typename T> void set(size_t i,T v)
            {
                if(_ptr)
                    _ptr->set(i,data_value(v));
                else
                    data_object::_throw_not_allocated_error(EXCEPTION_RECORD);
            }

            //-----------------------------------------------------------------
            data_value operator[](size_t i) const
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
    };

    std::ostream &operator<<(std::ostream &os,const data_object &o)
    {
        return o.write(os);
    }

    std::istream &operator>>(std::istream &is,data_object &o)
    {
        return o.read(is);
    }


//end of namespace
}
}


        
