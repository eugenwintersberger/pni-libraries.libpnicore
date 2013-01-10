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
    The construction is rather simple
    \code 
    data_object obj = DArray<Float32>(shape_t{104,200});
    \endcode
    In this example the object held by data_object will be constructed using
    move operation as the right hand side of the assignment operator is a
    temporary. Alternatively, the object can be copied using something like this
    \code
    DArray<Float32> array(shape_t{104,200});
    data_object obj = array;
    \endcode
    in which case the copy constructor is used to copy the array's data. 

    Another important question is how to get the original object back. Several
    cast functions are defined for the data_object class. 
    


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

                    //---------------------------------------------------------
                    /*!
                    \brief get type name 

                    Return the mangled name of the original type wrapped by the
                    type erasure.
                    \return type name
                    */
                    virtual String type_name() const = 0;

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

                    //---------------------------------------------------------
                    virtual String type_name() const
                    {
                        return typeid(OT).name();
                    }

            };
           
            /*!
            \brief throw exception

            Static helper method that throws a MemoryNotAllcatedError if the
            type erasure holds no data and data access is requested by the user.
            \throw MemoryNotAllocatedError
            \param r exception record where the error occured.
            */
            static void _throw_not_allocated_error(const ExceptionRecord &r)
            {
                throw MemoryNotAllocatedError(r,
                        "Instance of data_object holds no data!");
            }

            template<typename VT> 
                friend VT *data_object_cast(data_object *o);
            template<typename VT> 
                friend const VT *data_object_cast(const data_object *o);

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
            data_object(const data_object &e);
            //------------------------------------------------------------------
            //move constructor
            data_object(data_object &&e);

            //=====================public member functions=====================
            TypeID type_id() const;
            
            //-----------------------------------------------------------------
            size_t rank() const;

            //-----------------------------------------------------------------
            shape_t shape() const;

            //-----------------------------------------------------------------
            size_t size() const; 

            //-----------------------------------------------------------------
            std::ostream &write(std::ostream &os) const;

            //-----------------------------------------------------------------
            std::istream &read(std::istream &is);

            //-----------------------------------------------------------------
            data_value get(size_t i) const;

            //-----------------------------------------------------------------
            template<typename T> void set(size_t i,T v)
            {
                if(_ptr)
                    _ptr->set(i,data_value(v));
                else
                    data_object::_throw_not_allocated_error(EXCEPTION_RECORD);
            }

            //-----------------------------------------------------------------
            data_value operator[](size_t i) const;

            //-----------------------------------------------------------------
            String type_name() const;
    };


    /*!
    \brief stream output

    Writes the content of a data_object to an output stream.
    \param os reference to output stream
    \param o instance of data_object
    \return reference to output stream
    */
    std::ostream &operator<<(std::ostream &os,const data_object &o);

    //-------------------------------------------------------------------------
    /*!
    \brief stream input

    Store data from stream to data_object.
    \param is reference to input stream
    \param o reference to data object
    \return reference to input stream
    */
    std::istream &operator>>(std::istream &is,data_object &o);

    //-------------------------------------------------------------------------
    /*!
    \brief cast pointer to data_object

    Template function that casts an instance of data_object to its original
    type. In this case a pointer to the original object is returned. 
    
    */
    template<typename VT> VT *data_object_cast(data_object *o)
    {
        if(o->type_name() == typeid(VT).name())
        {
            return &dynamic_cast<data_object::data_object_holder<VT>*>(o->_ptr.get())->_object;
        }

        return nullptr; 
    }

    //-------------------------------------------------------------------------
    /*!
    \brief cast const pointer to data_object

    */
    template<typename VT> const VT *data_object_cast(const data_object *o)
    {
        return data_object_cast<VT>(const_cast<data_object *>(o));
        
    }

    //-------------------------------------------------------------------------
    /*!
    \brief cast data_object instance

    */
    template<typename VT> VT data_object_cast(data_object &o)
    {
        return *data_object_cast<VT>(&o);
    }

    //-------------------------------------------------------------------------
    /*!
    \brief cast const data_object

    */
    template<typename VT> VT data_object_cast(const data_object &o)
    {
        return data_object_cast<VT>(const_cast<data_object&>(o));
    }


//end of namespace
}
}


        
