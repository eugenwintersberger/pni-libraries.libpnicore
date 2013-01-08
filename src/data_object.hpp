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

#include "Types.hpp"
#include "Array.hpp"

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
                    virtual const void *ptr() const = 0;

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
                    std::ostream &write(std::ostream &os) const;

                    //---------------------------------------------------------
                    /*!
                    \brief read data

                    Read data from a standard C++ stream.
                    \param is reference to input stream
                    \return reference to input stream
                    */
                    std::istream &read(std::istream &is);

            };

            //-----------------------------------------------------------------
            //holder template - implementing the interface
            template<typename OT> 
            class data_object_holder:public data_object_interface
            {
                public:
                    OT _object;
                public:
                    //construct by copying o
                    Holder(const T &o):_object(o) {}
                    //construct by moving o
                    Holder(T &&o):_object(std::move(o)) {}
                    //copy constructor
                    Holder(const Holder<T> &o):_object(o._object) {}
                    //move constructor
                    Holder(Holder<T> &&o):_object(std::move(o._object)) {}

                    //implements the virtual member function
                    virtual double value() const
                    {
                        return double(_object.value());
                    }

                    T clone() const
                    {
                        return T(_object);
                    }
            };

            std::unique_ptr<Interface> _ptr; //pointer to holder
        public:
            //---------------------------------------------------------------------
            //construction by copying o
            template<typename T,
                     typename  = typename std::enable_if<
                                       !std::is_same<data_object,typename
                                       std::remove_reference<T>::type >::value 
                                       >::type
                    > 
            data_object(const T &o):
                _ptr(new Holder<T>(o))
            {
                std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
            }

            //---------------------------------------------------------------------
            //construction by moving o
            template<typename T,
                     typename = typename std::enable_if<
                                       !std::is_same<data_object,typename
                                       std::remove_reference<T>::type >::value 
                                       >::type
                    > 
            data_object(T &&o):
                _ptr(new Holder<typename std::remove_cv<
                                typename std::remove_reference<T>::type>::type>
                                (std::forward<T>(o)))
            {
                std::cout<<BOOST_CURRENT_FUNCTION<<std::endl; 
            }


            //---------------------------------------------------------------------
            //copy constructor
            data_object(const data_object &e):_ptr(e._ptr)
            {
                std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
            }

            //---------------------------------------------------------------------
            //move constructor
            data_object(data_object &&e):_ptr(std::move(e._ptr))
            {
                std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
            }



            //delegate
            double value() const { return _ptr->value(); }

    };

    std::ostream &operator<<(std::ostream &stream,const Erasure &e)
    {
        return stream<<e.value();
    }

//end of namespace
}
}


        
