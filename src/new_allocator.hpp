/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 * Definition of the NewAllocator class
 *
 * Created on: May 4, 2012
 *     Author: Eugen Wintersberger
 *
 */

#pragma once

#include <iostream>
#include <sstream>
#include "exceptions.hpp"

namespace pni{
namespace core{

    /*! \ingroup buffer_classes
    \brief allocator class using new

    This allocator class uses the new operator to allocate and the delete
    operator to free memory. 
    \code
    //allocate memory for 100 Float64 values
    float64 *ptr = new_allocator::allocate<float64>(100);

    //free the pointer
    new_allocator::free(ptr);
    \endcode 
    */
    class new_allocator
    {
        public:
            /*! \brief allocate memory

            Static template method to allocate memory for n elements of size T.
            An exception will be thrown if allocation fails.
            \throw memory_allocation_error if allocation fails
            \tparam T data type for which memory should be allocated 
            \param n number of elements for which memory should be allocated
            \return pointer to the allocated memory region
            */
            template<typename T> static T *allocate(size_t n)
            {
                T *ptr = nullptr;

                try
                {
                    ptr = new T[n];
                }
                catch(...)
                {
                    std::stringstream ss;
                    ss<<"Allocation of "<<sizeof(T)*n<<" Bytes of memory";
                    ss<<" failed!";
                    throw memory_allocation_error(EXCEPTION_RECORD,ss.str());
                }

                return ptr;

            }

            //-----------------------------------------------------------------
            /*! \brief free memory

            Free memory allocated by this allocator class. 
            \tparam T base type of the pointer
            \param ptr pointer to the allocated memory
            */
            template<typename T> static void free(T *ptr)
            {
                if(ptr) delete [] ptr;
            }
    };

//end of namespace
}
}

