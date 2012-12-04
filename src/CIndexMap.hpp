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

#ifndef __CINDEXMAP_HPP__
#define __CINDEXMAP_HPP__

#include "IndexMapBase.hpp"

namespace pni{
namespace utils{

    /*! 
    \ingroup index_mapping_classes
    \brief C-order index map

    Maps multidimensional indices to linear offsets and vicer verse in C-order.
    This type can be used in any array or shape object to compute offsets and
    indices. The static method provided are entirely generic and assume only a
    containers that supports reverse iterators. This includes all STL container
    types.
    */
    class CIndexMap : public IndexMapBase
    {
        private:
            //! buffer with strides between dimensions
            DBuffer<size_t> _strides;         

            //================private methods==================================
            //! compute dimension strides
            void _compute_strides();
           
            //-----------------------------------------------------------------
            /*!
            \brief compute offset

            Compute the contribution of index d in the multindex to the total
            linear offset of an element. This function is called recursively 
            until no more indices are left.
            \tparam ITYPES index types
            \param d dimension of the index
            \param i actual index
            \param indices residual indices.
            \return linear offset.
            */
            template<typename ...ITYPES>
            size_t _get_offset(size_t d,size_t i,ITYPES ...indices) const
            {
                return i*_strides[d]+_get_offset(d+1,indices...); 
            }

            //-----------------------------------------------------------------
            /*!
            \brief compute offset

            Break condition for the last index in a multiindex variadic offset
            call. 
            \param d last dimension
            \param i last index
            \return linear offset
            */
            size_t _get_offset(size_t d,size_t i) const
            {
                return i*_strides[d];
            }
        public:
            //================constructors and destructor======================
            //! default constructor
            CIndexMap():IndexMapBase(),_strides() {}

            //-----------------------------------------------------------------
            //!initializer list constructor
            explicit CIndexMap(const std::initializer_list<size_t> &il):
                IndexMapBase(il),
                _strides(il.size())
            {
                _compute_strides();
            }

            //-----------------------------------------------------------------
            //! constrution from contianer
            template<template<typename...> class CTYPE,typename ...OTS> 
                explicit CIndexMap(const CTYPE<OTS...> &c):
                IndexMapBase(c),
                _strides(c.size())
            {
                _compute_strides();
            }

            //-----------------------------------------------------------------
            //! move constructor
            CIndexMap(CIndexMap &&m):
                IndexMapBase(std::move(m)),
                _strides(std::move(m._strides))
            {}

            //-----------------------------------------------------------------
            //! copy constructor
            CIndexMap(const CIndexMap &m):
                IndexMapBase(m),
                _strides(m._strides)
            {}

            //-----------------------------------------------------------------
            //! destructor
            ~CIndexMap() {}

            //===================assignment operators==========================
            //! copy assignment operator
            CIndexMap &operator=(const CIndexMap &m)
            {
                if(this == &m) return *this;
                IndexMapBase::operator=(m);
                _strides = m._strides;
                return *this;
            }

            //-----------------------------------------------------------------
            //! move assignment operator
            CIndexMap &operator=(CIndexMap &&m)
            {
                if(this == &m) return *this;
                IndexMapBase::operator=(std::move(m));
                _strides = std::move(m._strides);
                return *this;
            }

            //===============public methods====================================
            /*!
            \brief set new shape

            Sets a new shape or can be used if the object was constructed with
            the default constructor.
            \tparam CTYPE container type of the shape 
            \param s container with new shape
            */
            template<typename CTYPE> void shape(const CTYPE &s)
            {
                IndexMapBase::shape(s);
                _strides = DBuffer<size_t>(s.size());
                _compute_strides();
            }

            //need this to prevent the compiler from hiding all the original
            //functions from the base class.
            using IndexMapBase::shape;

            //-----------------------------------------------------------------
            /*!
            \brief compute offset from argument list

            Computes the linear offset of multidimensional data from a 
            multi-index passed as argument list ot the function.
            \code
            CIndexMap imap{3,4,5,8};
            size_t offset = imap.offset(1,2,0,3);
            \endcode
            This function does no index nor rank checking. This is simply due to
            performance issues. 
            \tparam ITYPES index types
            \param indices element indices
            \return offset value
            */
            template<typename ...ITYPES> 
                size_t offset(ITYPES ...indices) const
            {
                return _get_offset(0,indices...);
            }

            //-----------------------------------------------------------------
            /*!
            \brief compute offset from a container

            Computes the linear offset of multidimensional data from indices 
            stored in a container. 
            \code
            CIndexMap imap{3,4,5,8};
            std::vector<size_t> index{1,2,0,3};
            size_t offset = imap.offset(index);
            \endcode

            \throws ShapeMissmatchError if the size of the index and the shape
            container do not match
            \throws IndexError if one of the indices exceeds the number of 
            elements along its dimension
            \tparam CTYPE type of the index container
            \param c container with index data
            \return linear offset
            */
            template<template<typename...> class CTYPE,typename ...OTYPES> 
                size_t offset(const CTYPE<OTYPES...> &c) const;
           
            //-----------------------------------------------------------------
            /*!
            \brief compute an index from a given offset

            Compute the multidimensional index for a given offset and shape. 
            \code
            CIndexMap imap{3,4,5,8};
            auto index = imap.template index<std::vector<size_t> >(8);
            \endcode
            The container holding the index is allocated by the method so no
            additional work must be done by the user. 
            \tparam ITYPE container type for the index
            \param offset linear offset
            \return index for offset
            */
            template<typename ITYPE> ITYPE index(size_t offset) const;

            //-----------------------------------------------------------------
            /*!
            \brief compute index from a given offset

            Compute the mulditimensional index for a given offset value. 
            This method takes the container for the index as a third argument thus
            avoiding that it must be allocated every time the method is called. 
            \code
            CIndexMap imap{3,4,5,8};
            std::vector<size_t> index(4);
            imap.index(8,index);
            \endcode
            \throws ShapeMissmatchError if the size of the index container is not
            coinciding with that of the shape 
            \throws SizeMissmatchError if the offset exceeds the total size of the
            array represented by shape
            \tparam ITYPE container type for index
            \param offset the linear offset
            \param index container holding the resulting index
            */
            template<typename ITYPE> 
                void index(size_t offset,ITYPE &index) const;
        
        };


        //-------------------------------------------------------------------------
        template<template<typename...> class CTYPE,typename ...OTYPES> 
            size_t CIndexMap::offset(const CTYPE<OTYPES...> &index) const
        {

            if(index.size() != rank())
            {
                std::stringstream ss;
                ss<<"Rank of index ("<<index.size()<<") does not match ";
                ss<<"map rank ("<<rank()<<")!";
                throw ShapeMissmatchError(EXCEPTION_RECORD,ss.str());
            }

            size_t offset = 0;
            auto siter = _strides.begin();
            auto miter = shape().begin();
            for(auto iiter=index.begin();iiter!=index.end();iiter++,siter++,miter++)
            {
                check_index((*iiter),(*miter),EXCEPTION_RECORD);
                offset += (*iiter)*(*siter);
            }

            return offset;
        }

        //-------------------------------------------------------------------------
        template<typename ITYPE> ITYPE CIndexMap::index(size_t offset) const
        {
            ITYPE index(shape().size());
            try { this->index(offset,index);}
            EXCEPTION_FORWARD(SizeMissmatchError);

            return index;
        }


        //-------------------------------------------------------------------------
        template<typename ITYPE>
            void CIndexMap::index(size_t offset,ITYPE &index) const
        {
            if(offset>=size())
            {
                std::stringstream ss;
                ss<<"Offset ("<<offset<<") exceeds linear size ("<<size()<<")!";
                throw SizeMissmatchError(EXCEPTION_RECORD,ss.str());
            }

            size_t t;
            size_t i=0;
            for(auto iiter=index.begin();iiter!=index.end();iiter++,i++)
            {
                t = offset%_strides[i];
                *iiter = (offset-t)/_strides[i];
                offset = t;
            }

        }


//end of namespace
}
}

#endif
