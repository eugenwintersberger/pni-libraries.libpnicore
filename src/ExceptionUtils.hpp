/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniutils.
 *
 * libpniutils is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniutils is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with lipniutils.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * 
 * Exception related utility functions - declarations.
 *
 * Created on: May 23, 2012
 *     Author: Eugen Wintersberger
 *
 */
#ifndef __EXCEPTIONUTILS_HPP__
#define __EXCEPTIONUTILS_HPP__

#include <iostream>
#include <typeinfo>
#include <algorithm>

#include "Exceptions.hpp"

namespace pni{
namespace utils{

    //=====================Exception related helper functions==================
    /*!
    \ingroup error_classes
    \brief check if two objects have different size
    
    This utilty function can be used to check for the equality of the size of
    two objects. It is typically used to compare the size of a shape and a 
    buffer or any other container object. 
    If the sizes do not match an exception is thrown.
    \throws SizeMissmatchError if sizes do not match
    \param a first object
    \param b second object
    \param i signature of the function or method where the check has been
    performed
    */
    template<typename A,typename B> 
        void check_equal_size(const A &a,const B &b,const String &i)
    {
        if(a.size() != b.size())
        {
            std::stringstream ss;
            ss<<"Size of "<<typeid(A).name()<<" ("<<a.size()<<") ";
            ss<<"does not match size of "<<typeid(B).name()<<" (";
            ss<<b.size()<<")!";
            SizeMissmatchError error;
            error.issuer(i);
            error.description(ss.str());
            throw error;
        }
    }

    /*!
    \ingroup error_classes
    \brief check index 

    This utilty function can be used to check if an index exeeds a particular
    value.
    \throws IndexError if i exceeds imax
    \param index actual index
    \param maxindex maximum value
    \param i signature of the function or method where the check has been
    performed
    */
    void check_index(size_t index,size_t maxindex,const String &i);


    //-------------------------------------------------------------------------
    /*!
    \ingroup error_classes
    \brief check shape equality

    Checks if two Shape objects are equal and throws an exception if they are
    not.
    \tparam A container type for the first shape
    \tparam B container type for the second shape
    \throws ShapeMissmatchError if shapes do not match
    \param a first shape
    \param b second shape
    \param i signature of the function or method where the check was performed
    */
    template<typename A,typename B>
    void check_equal_shape(const A &a,const B &b,const String &i)
    {
        auto sa = a.template shape<std::vector<size_t> >();
        auto sb = b.template shape<std::vector<size_t> >();

        if((sa.size()!=sb.size()) ||
           (!std::equal(sa.begin(),sa.end(),sb.begin())))
        {
            //assemble error string
            std::stringstream ss;
            ss<<"Shapes ( ";
            for(auto v: sa) std::cout<<v<<" ";
            ss<<") and ( ";
            for(auto v: sb) std::cout<<v<<" ";
            ss<<") do not match";

            //construct exception
            ShapeMissmatchError error;
            error.issuer(i);
            error.description(ss.str());
            throw error;
        }
    }

    //-------------------------------------------------------------------------
    /*! 
    \ingroup error_classes
    \brief check allocation state

    Checks the allocation state of an allocateable object. If the object is not
    allocated an exception will be thrown.
    \throws MemoryNotAllocatedError if object not allocated
    \param o object to check
    \param i signature of the function or method where the check was performed
    */
    template<typename OTYPE> void
        check_allocation_state(const OTYPE &o,const String &i)
    {
        if(!o.size())
        {
            std::stringstream ss;
            ss<<"Instance of "<<typeid(OTYPE).name()<<" not allocated!";
            MemoryNotAllocatedError error;
            error.issuer(i);
            error.description(ss.str());
            throw error;
        }
    }

    //-------------------------------------------------------------------------
    /*! 
    \ingroup error_classes
    \brief check pointer state

    Checks if a pointer is nullptr or not and throws an exception if it is.
    \throws MemoryNotAllocatedError if pointer is a nullptr
    \param ptr pointer to check
    \param i issuer of the exception
    */
    template<typename T> 
        void check_ptr_state(const T *ptr,const String &i)
    {
        if(!ptr)
        {
            std::stringstream ss;
            ss<<"Pointer is nullptr!";
            MemoryNotAllocatedError error;
            error.issuer(i);
            error.description(ss.str());
            throw error;
        }
    }



//end of namespace
}
}
#endif
