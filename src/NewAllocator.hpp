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
 * along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * 
 * Definition of the NewAllocator class
 *
 * Created on: May 4, 2012
 *     Author: Eugen Wintersberger
 *
 */

#ifndef __NEWALLOCATOR_HPP__
#define __NEWALLOCATOR_HPP__

#include <iostream>
#include <sstream>
#include "Exceptions.hpp"

namespace pni{
namespace utils{

    /*! \ingroup buffer_classes
    \brief allocator class using new

    This allocator class uses the new operator to allocate new memory and the
    delete operator for freeing memory.
    */
    class NewAllocator
    {
        public:
            /*! \brief allocate memory

            Static template method to allocate memory for n elements of size T.
            An exception will be thrown if allocation fails.
            \throw MemoryAllocationError if allocation fails
            \param n number of elements for which memory should be allocated
            \return pointer to the allocated memory region
            */
            template<typename T> static T *allocate(size_t n)
            {
                EXCEPTION_SETUP("template<typename T> static T *"
                                "NewAllocator::allocate(size_t n)");

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
                    EXCEPTION_INIT(MemoryAllocationError,ss.str());
                    EXCEPTION_THROW();
                }

                return ptr;

            }

            /*! \brief free memory

            Free memory allocated by this allocator class. 
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
#endif

