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
 * Definition of the IndexMap class. This class provides methods for easily
 * compute indices from multidimensional arrays.
 *
 * Created on: March 9, 2012
 *     Author: Eugen Wintersberger
 *
 */


#ifndef __INDEXMAP_HPP__
#define __INDEXMAP_HPP__

#include "Buffer.hpp"

namespace pni{
    namespace utils{

            /*! \brief compute multidimensional indices.

            */
            class IndexMap{
                private:
                    Buffer<ssize_t> _offset;
                    Buffer<ssize_t> _stride;
                    Buffer<ssize_t> _count;

                    template<typename T,typename ...Ts>
                        size_t __offset(size_t d,T i1,Ts... is){

                        size_t o = 1;
                        for(size_t i=d+1;i<rank();i++) 
                            o*=_count[i]*_stride[i];

                        return o*i1*_stride[d]+__offset(d+1,is...);

                    }

                    template<typename T> size_t __offset(size_t d,T i)
                    {
                        return i*_stride[rank()-1];

                    }


                public:
                    //========constructors and destructor======================
                    //! default constructor
                    IndexMap();

                    //! copy constructor
                    IndexMap(const IndexMap &o);

                    //! move constructor
                    IndexMap(IndexMap &&o);

                    /*! standard constructor

                    Construct IndexMap from a particular rank.
                    \throws MemoryAllocationError if memory allocation fails
                    */
                    IndexMap(size_t rank);

                    /*! standard constructor

                    Construct IndexMap object from buffer objects. 
                    \throws SizeMissmatchError if buffer sizes are not equal
                    */
                    IndexMap(const Buffer<ssize_t> &o,const Buffer<ssize_t> &s,
                             const Buffer<ssize_t> &c);

                    //! destructor
                    ~IndexMap();

                    //============assignment operators=========================
                    //! copy constructor
                    IndexMap &operator=(const IndexMap &o);

                    //! move constructor
                    IndexMap &operator=(IndexMap &&o);

                    //! \brief return IndexMap rank

                    //! Returns the number of dimensions of the IndexMap.
                    //! \return number of dimensions
                    size_t rank() const
                    {
                        return _count.size();
                    }

                    
                    //=======access methods for the buffers===================
                    /*! \brief set offset for dimension i

                    Set the offset for dimension i to o. If i exceeds the rank
                    of the IndexMap an exception will be thrown.
                    \throws IndexError if i exceeds IndexMap rank
                    \throws MemoryAccessError if offset buffer not allocated
                    \param i dimension index
                    \param o offset value for dimension
                    */
                    void offset(size_t i,ssize_t o);

                    /*! \brief get offset for dimension i

                    Get the offset value for dimension i. If i exceeds the rank
                    of the IndexMap an exception will be thrown.
                    \throws IndexError if i exceeds IndexMap rank
                    \throws MemoryAccessError if offset buffer not allocated
                    \param i dimension index
                    \return offset value for dimension i
                    */
                    ssize_t offset(size_t i) const;

                    /*! \brief set offset values from buffer

                    Set offset values from an existing buffer object. This
                    allows also the usage of initializer lists. 
                    The size of the buffer must be equal to the rank of the 
                    IndexMap.
                    \throws SizeMissmatchError if buffer size is not equal to
                    the IndexMap rank
                    \param b buffer from which to read data
                    */
                    void offset(const Buffer<ssize_t> &b);

                    /*! \brief get offset buffer

                    Return a constant reference to the buffer with the offset
                    value. 
                    \return const. refernce tto the offset buffer
                    */
                    const Buffer<ssize_t> &offset() const;


                    /*! \brief set stride for dimension i

                    Set the stride for dimension i to o. If i exceeds the rank
                    of the IndexMap an exception will be thrown.
                    \throws IndexError if i exceeds IndexMap rank
                    \throws MemoryAccessError if stride buffer not allocated
                    \param i dimension index
                    \param s stride value for dimension
                    */
                    void stride(size_t i,ssize_t s);

                    /*! \brief get stride for dimension i

                    Get the stride value for dimension i. If i exceeds the rank
                    of the IndexMap an exception will be thrown.
                    \throws IndexError if i exceeds IndexMap rank
                    \throws MemoryAccessError if stride buffer not allocated
                    \param i dimension index
                    \return stride value for dimension i
                    */
                    ssize_t stride(size_t i) const;

                    /*! \brief set stride values from buffer

                    Set stride values from an existing buffer object. This
                    allows also the usage of initializer lists. 
                    The size of the buffer must be equal to the rank of the 
                    IndexMap.
                    \throws SizeMissmatchError if buffer size is not equal to
                    the IndexMap rank
                    \param b buffer from which to read data
                    */
                    void stride(const Buffer<ssize_t> &b);

                    /*! \brief get stride buffer

                    Return a constant reference to the buffer with the stride
                    value. 
                    \return const. refernce tto the stride buffer
                    */
                    const Buffer<ssize_t> &stride() const;
                    
                    /*! \brief set count for dimension i

                    Set the count for dimension i to o. If i exceeds the rank
                    of the IndexMap an exception will be thrown.
                    \throws IndexError if i exceeds IndexMap rank
                    \throws MemoryAccessError if count buffer not allocated
                    \param i dimension index
                    \param c count value for dimension
                    */
                    void count(size_t i,ssize_t c);

                    /*! \brief get count for dimension i

                    Get the count value for dimension i. If i exceeds the rank
                    of the IndexMap an exception will be thrown.
                    \throws IndexError if i exceeds IndexMap rank
                    \throws MemoryAccessError if count buffer not allocated
                    \param i dimension index
                    \return count value for dimension i
                    */
                    ssize_t count(size_t i) const;

                    /*! \brief set count values from buffer

                    Set count values from an existing buffer object. This
                    allows also the usage of initializer lists. 
                    The size of the buffer must be equal to the rank of the 
                    IndexMap.
                    \throws SizeMissmatchError if buffer size is not equal to
                    the IndexMap rank
                    \param b buffer from which to read data
                    */
                    void count(const Buffer<ssize_t> &b);

                    /*! \brief get count buffer

                    Return a constant reference to the buffer with the count
                    value. 
                    \return const. refernce tto the count buffer
                    */
                    const Buffer<ssize_t> &count() const;


                    //===========index related methods=========================
                    template<typename ...ITypes> 
                        size_t offset(ITypes ...indices)
                    {
                        if((sizeof...(ITypes))!=rank()){
                            //throw an exception here
                        }
                        
                        size_t offset = __offset(0,indices...);
                        return offset;
                    }

                    //Buffer<size_t> index(size_t offset);

            };

    //end of namespace
    }
}

#endif
