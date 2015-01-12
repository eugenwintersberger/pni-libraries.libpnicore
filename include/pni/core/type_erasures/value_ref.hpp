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
#include "value_holder.hpp"
#include "utils.hpp"

namespace pni{
namespace core{

    class value;

    //!
    //! \ingroup type_erasure_classes
    //! \brief type erasure for references to POD data
    //!
    //!
    class value_ref
    {
        private:
            //! internal pointer type used to hold the reference instance
            typedef std::unique_ptr<value_holder_interface> pointer_type;

            //----------------------------------------------------------------
            //!
            //! \brief throw exception
            //!
            //! Static helper method that throws a memory_not_allocated_error 
            //! if the type erasure holds no data and data access is 
            //! requested by the user.
            //! 
            //! \throw memory_not_allocated_error
            //! \param r exception record where the error occurred.
            //!
            void _check_pointer(const exception_record &r) const;

            //----------------------------------------------------------------
            //!
            //! \brief check type
            //!
            //! Throws type_error exception if the passed type id does not match
            //! the references original type. 
            //!
            //! \throw type_error 
            //! \param tid type id to check
            //! \param r exception record of the code position 
            //!
            void _check_type(type_id_t tid,const exception_record &r) const;
            

            //----------------------------------------------------------------
            //! 
            //! \brief return value
            //!
            //! Return the value of the variable the reference refers to. 
            //! T denotes the data type requested by the  user. S denotes 
            //! the type of the variable the reference points to.
            //! 
            //! \throws type_error if the conversion is not possible
            //! \throws range_error if the value 
            //! \tparam T target type
            //! \tparam S source type
            //! \return value as T
            //!
            template<
                     typename T,
                     typename S 
                    > 
            T _get_value() const 
            {
                typedef strategy<T,S>   strategy_type;

                return strategy_type::convert(get_holder_ptr<ref_type<S>>(_ptr)->as()); 
            }

            //----------------------------------------------------------------
            //!
            //! \brief set value
            //! 
            //! Sets the value of the variable the reference points to. 
            //!
            //! \throws type_error if the conversion is not possible
            //! \throws range_error if the passed value does not fit in the
            //! target type
            //! \tparam S type of the variable
            //! \tparam T type of the value the user passed
            //! \param T 

            template<
                     typename S,
                     typename T 
                    >
            void _set_value(const T &v)
            {
                typedef strategy<S,T> strategy_type;

                get_holder_ptr<ref_type<S>>(_ptr)->as().get() = strategy_type::convert(v);
            }

            //! pointer holding the value stored
            pointer_type _ptr;
        public:
            //================constructors and destructor======================
            //!
            //! \brief default constructor
            //! 
            value_ref();
          
            //-----------------------------------------------------------------
            //! 
            //! \brief template constructor from value
            //!
            //! Constructs a reference to a variable of type T. 
            //! \code
            //! float32 x = 100.;
            //! value_ref v(std::ref(x));
            //! \endcode
            //!
            //! \tparam T type of the value to which the reference shall be created
            //! \param v reference to the value
            //!
            template<typename T>
            explicit value_ref(std::reference_wrapper<T> v):
                _ptr(new value_holder<std::reference_wrapper<T> >(v))
            {}

            //-----------------------------------------------------------------
            //!
            //! \brief copy constructor
            //!
            value_ref(const value_ref &o);

            //==================assignment operators===========================
            //! 
            //! \brief assign value to the variable
            //!
            //! Assign a value of type T to the target of the reference. 
            //! If T differs from the original type of the target the data will 
            //! be converted. 
            //! 
            //! \throws memory_not_allocated_error if the reference is not 
            //! initialized 
            //! \throws type_error if conversion is not possible 
            //! \throws range_error if the value does not fit into the target
            //! type.
            //!
            //! \param v reference to the new value
            //! \return instance of value
            //!
            template<typename T> value_ref &operator=(const T &v);

            //----------------------------------------------------------------
            //!
            //! \brief assignment from a value
            //!
            //! In this case the value stored in v will be assigned to the
            //! variable refered to by this instance of value_ref.
            //! If the data types do not match a type conversion takes place 
            //! if necessary.
            //!
            //! \throws memory_not_allocated if the reference is not initialized
            //! \throws type_error if the type of v and the reference to not
            //! match
            //! \throws range_error if the value of v does not fit in the type 
            //! of the variable referenced by this instance of value_ref.
            //! \param v value instance
            //!
            value_ref &operator=(const value &v);

            //-----------------------------------------------------------------
            //! copy assignment
            // we should remove this - makes not really sense. We can 
            // always destroy the reference and create a new one (could we?)
            value_ref &operator=(const value_ref &o);

            //-----------------------------------------------------------------
            //!
            //! \brief conversion operator
            //! 
            //! This operator is used to convert a reference to a value 
            //! type erasure. 
            //! 
            operator value () const;

            //-----------------------------------------------------------------
            //!
            //! \brief get the referenced value
            //!
            //! Returns the value of the variable the value_ref instance 
            //! points to. If the type requested by the user via the template
            //! parameter T is different from the type of the variable value_ref
            //! points to the data will be converted if possible. 
            //! If the conversion fails or is not possible an exception will 
            //! be thrown. 
            //! 
            //! \throws memory_not_allocated_error if value is uninitialized
            //! \throws type_error if data cannot be converted to T
            //! \throws range_error if data does not fit into the range of T 
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
            //! output stream operator
            friend std::ostream &operator<<(std::ostream &stream,
                                            const value_ref &v);
            //-----------------------------------------------------------------
            //! input stream operator
            friend std::istream &operator>>(std::istream &stream,
                                            value_ref &v);

            //----------------------------------------------------------------
            //!
            //! \brief value comparison
            //!
            //! Compares the two values stored by the 
            friend bool operator==(const value_ref &a,const value_ref &b);

            //----------------------------------------------------------------
            friend bool operator!=(const value_ref &a,const value_ref &b);
    };

    //======================implementation of template members=================
    template<typename T> T value_ref::as() const
    {
        //check if the reference points to something
        _check_pointer(EXCEPTION_RECORD);

        type_id_t tid = type_id();
        switch(tid)
        {
            case type_id_t::UINT8:      return _get_value<T,uint8>();
            case type_id_t::INT8:       return _get_value<T,int8>();
            case type_id_t::UINT16:     return _get_value<T,uint16>();
            case type_id_t::INT16:      return _get_value<T,int16>();
            case type_id_t::UINT32:     return _get_value<T,uint32>();
            case type_id_t::INT32:      return _get_value<T,int32>();
            case type_id_t::UINT64:     return _get_value<T,uint64>();
            case type_id_t::INT64:      return _get_value<T,int64>();
            case type_id_t::FLOAT32:    return _get_value<T,float32>();
            case type_id_t::FLOAT64:    return _get_value<T,float64>();
            case type_id_t::FLOAT128:   return _get_value<T,float128>();
            case type_id_t::COMPLEX32:  return _get_value<T,complex32>();
            case type_id_t::COMPLEX64:  return _get_value<T,complex64>();
            case type_id_t::COMPLEX128: return _get_value<T,complex128>();
            case type_id_t::BINARY:     return _get_value<T,binary>();
            case type_id_t::STRING:     return _get_value<T,string>();
            case type_id_t::BOOL:       return _get_value<T,bool_t>();
            default:
                throw type_error(EXCEPTION_RECORD,
                        "The reference points to an object of unkown type!");
        }
        
    }
           
    //-------------------------------------------------------------------------
    template<typename T> value_ref &value_ref::operator=(const T &v)
    {
        typedef value_holder<std::reference_wrapper<T> > holder_type;

        _check_pointer(EXCEPTION_RECORD);
        
        type_id_t tid = type_id();

        switch(tid)
        {
            case type_id_t::UINT8:      _set_value<uint8>(v);      break;
            case type_id_t::INT8:       _set_value<int8>(v);       break;
            case type_id_t::UINT16:     _set_value<uint16>(v);     break;
            case type_id_t::INT16:      _set_value<int16>(v);      break;
            case type_id_t::UINT32:     _set_value<uint32>(v);     break;
            case type_id_t::INT32:      _set_value<int32>(v);      break;
            case type_id_t::UINT64:     _set_value<uint64>(v);     break;
            case type_id_t::INT64:      _set_value<int64>(v);      break;
            case type_id_t::FLOAT32:    _set_value<float32>(v);    break;
            case type_id_t::FLOAT64:    _set_value<float64>(v);    break;
            case type_id_t::FLOAT128:   _set_value<float128>(v);   break;
            case type_id_t::COMPLEX32:  _set_value<complex32>(v);  break;
            case type_id_t::COMPLEX64:  _set_value<complex64>(v);  break;
            case type_id_t::COMPLEX128: _set_value<complex128>(v); break;
            case type_id_t::BINARY:     _set_value<binary>(v);     break;
            case type_id_t::STRING:     _set_value<string>(v);     break;
            case type_id_t::BOOL:       _set_value<bool_t>(v);     break;
            default:
                throw type_error(EXCEPTION_RECORD,
                        "The reference points to an object of unknown type!");
        }

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
    //! \throws memory_not_allocated_error if value is not initialized 
    //! \param stream output stream
    //! \param v reference to value
    //! \return reference to output stream
    //!
    std::ostream &operator<<(std::ostream &stream,const value_ref &v);

    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_erasure_classes
    //! \brief stream input operator
    //!
    //! Read data from an input stream to the value. It is important to 
    //! note that the value must be initialized otherwise an exception will 
    //! be thrown. 
    //! \code
    //! value v = value::create<uint32>();
    //! std::cin>>v;
    //! \endcode
    //!
    //! \throw memroy_not_allocated_error if value not initialized 
    //! \param stream input stream
    //! \param v value where to store data
    //! \return reference to input stream
    //!
    std::istream &operator>>(std::istream &stream,value_ref &v);

    //------------------------------------------------------------------------
    bool operator!=(const value_ref &a,const value_ref &b);

    bool operator==(const value_ref &a,const value_ref &b);

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_erasure_classes
    //! \brief conversion function to value
    //!
    //! This function extracts the value stored in the variable referenced by 
    //! value_ref and stores it in a new instance of value. 
    //!
    //! \throws memory_not_allocated_error if the reference is not set
    //! \throws type_error if the type of the variable referenced by value_ref 
    //! is unknown
    //!
    //! \param v reference to value_ref
    //! \return instance of value with the content of value_ref
    //!
    value to_value(const value_ref &v);

//end of namespace
}
}

