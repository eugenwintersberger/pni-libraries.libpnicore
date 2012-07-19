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
 * Created on: Jul 12, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef __INDEXMAP_HPP__
#define __INDEXMAP_HPP__

namespace pni{
namespace utils{

    /*! 
    \ingroup util_classes
    \brief C-order index map

    Maps multidimensional indices to linear offsets and vicer verse in C-order.
    This type can be used in any array or shape object to compute offsets and
    indices. The static method provided are entirely generic and assume only a
    containers that supports reverse iterators. This includes all STL container
    types.
    */
    struct CIndexMap
    {
        public:
        /*!
        \brief compute offset from argument list

        Computes the linear offset of multidimensional data from a multi-index
        passed as argument list ot the function.
        \code
        std::vector<size_t> shape{3,4,5,6};
        size_t offset = CIndexMap::offset(shape,1,2,0,3);
        \endcode
        \tparam STYPE container type for the shape
        \tparam ITYPES index types
        \param s container with the shape
        \param i first index 
        \param indices other indices
        \throws ShapeMissmatchError if number of indices and size of shape do
        not match
        \throws IndexError if one of the indices exceeds the number of elements
        along its dimension
        \return offset value
        */
        template<typename STYPE,typename ...ITYPES> 
            static size_t offset(const STYPE &s,size_t i,ITYPES ...indices);

        /*!
        \brief compute offset from a container

        Computes the linear offset of multidimensional data from indices stored
        in a container. 
        \code
        std::vector<size_t> shape{3,4,5,6};
        std::vector<size_t> index{1,2,0,3};
        size_t offset = CIndexMap::offset(shape,index);
        \endcode

        \throws ShapeMissmatchError if the size of the index and the shape
        container do not match
        \throws IndexError if one of the indices exceeds the number of elements
        along its dimension
        \tparam STYPE type of the shape container
        \tparam CTYPE type of the index container
        \param s container with shape data
        \param c container with index data
        \return linear offset
        */
        template<typename STYPE,typename CTYPE> 
            static size_t offset(const STYPE &s,const CTYPE &c);
        
        /*!
        \brief compute an index from a given offset

        Compute the multidimensional index for a given offset and shape. 
        \code
        std::vector<size_t> shape{3,4,5,6};
        auto index = CIndexMap::index<std::vector<size_t> >(shape,8);
        \endcode
        The container holding the index is allocated by the method so no
        additional work must be done by the user. 
        \tparam ITYPE container type for the index
        \tparam STYPE container type for the shape
        \param s container with shape data
        \param offset linear offset
        \return index for offset
        */
        template<typename ITYPE,typename STYPE> 
            static ITYPE index(const STYPE &s,size_t offset);

        /*!
        \brief compute index from a given offset

        Compute the mulditimensional index for a given offset value. 
        This method takes the container for the index as a third argument thus
        avoiding that it must be allocated every time the method is called. 
        \code
        std::vector<size_t> shape{3,4,5,6};
        std::vector<size_t> index(4);
        CIndexMap::index<std::vector<size_t> >(shape,8,index);
        \endcode
        \throws ShapeMissmatchError if the size of the index container is not
        coinciding with that of the shape 
        \throws SizeMissmatchError if the offset exceeds the total size of the
        array represented by shape
        \tparam STYPE container type for shape
        \tparam ITYPE container type for index
        \param s shape 
        \param offset the linear offset
        \param index container holding the resulting index
        */
        template<typename STYPE,typename ITYPE>
            static void index(const STYPE &s,size_t offset,ITYPE &index);
    };

    //-------------------------------------------------------------------------
    template<typename STYPE,typename ...ITYPES>
        size_t CIndexMap::offset(const STYPE &s,size_t i,ITYPES ...indices)
    {
        std::vector<size_t> index{i,size_t(indices)...};

        return offset(s,index);
    }

    //-------------------------------------------------------------------------
    template<typename STYPE,typename CTYPE>
        size_t CIndexMap::offset(const STYPE &shape,const CTYPE &index)
    {
        size_t dstride = 1,offset = 0;
        for(auto siter=shape.rbegin(),iiter=index.rbegin();
                siter!=shape.rend();
                ++siter,++iiter)
        {
            offset += *iiter*dstride;
            dstride *= *siter;
        }

        return offset;
    }

    //-------------------------------------------------------------------------
    template<typename ITYPE,typename STYPE>
        ITYPE CIndexMap::index(const STYPE &shape,size_t offset)
    {
        ITYPE index(shape.size());
        CIndexMap::index(shape,offset,index);
        return index;
    }

    //-------------------------------------------------------------------------
    template<typename STYPE,typename ITYPE>
        void CIndexMap::index(const STYPE &s,size_t offset,ITYPE &index)
    {
        STYPE dstrides(s.size());
        //compute dimension strides
        STYPE &shape = const_cast<STYPE &>(s);
        size_t ds = 1;
        for(auto siter = shape.rbegin(),dsiter=dstrides.rbegin();
                siter!=shape.rend();
                ++siter,++dsiter)
        {
            *dsiter = ds;
            ds *= *siter;
        }
      
        //compute the 
        size_t t;
        for(auto iiter=index.begin(),diter=dstrides.begin();
                iiter!=index.end();
                ++iiter,++diter)
        {
            t = offset%(*diter);
            *iiter = (offset-t)/(*diter);
            offset = t;
        }

    }


//end of namespace
}
}

#endif
