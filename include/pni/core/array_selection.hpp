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
 * Created on: Jun 1, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <vector>
#include <algorithm>

#ifdef NOFOREACH
#include <boost/foreach.hpp>
#endif

#include "container_utils.hpp"
#include "exception_utils.hpp"
#include "slice.hpp"

namespace pni{
namespace core{


    /*! 
    \ingroup index_mapping_classes
    \brief selection from a multidimensional array

    The array_selection class is a utility class for selecting subranges of
    multidimensional arrays. The effective rank of such a selection can be
    smaller than that of the original array. Thus the number of indices used to
    address an element in a selection might be smaller than for the original
    array. 
    This class has to major purposes

    \li compute the original index of the array for a
    \li compute the original offset for a given offset


    This type represents the selection of elements from a multidimensional
    array and is primarily used by the ArrayView template. 
    Its primary purpose is to map selection indices to indices of the
    original array. This is required as a selection might does not have the same
    rank as the original array. Consider an array of shape (4,10,28) from which
    we select (1,10,28). The effective rank of this selection is 2 while that of
    the original array would be 3. Additionally, such a selection would have the
    effective rank (10,28) as the first index can be omitted. This allows to
    select data of a particular dimensionality from an array of arbitrary rank.
    The only assumption that must be made is that the rank of the original array
    is larger than that of the required selection. 
    Clearly, one wants to use a two dimensional index (i,j) to address an
    element in the selection. However, to get the data from the original array
    this must be modified to (1,i,j) which is the major purpose of this type.
    */
    template<typename INDEXT=std::vector<size_t>>
    class array_selection
    {
        private:
            typedef INDEXT index_t;

            //member variables describing the selection in the original array
            //all of these containers have the same size which is equal to the
            //rank of the original array
            //! shape of the selection in the original array
            index_t _oshape;             
            //! offset in the original array
            index_t _offset;
            //! stride in the original array
            index_t _stride;

        public:
            //===================constructors and destructor====================
            //! standard constructor
            template<template<typename ...> class CTYPE,typename ...OTS>
            explicit array_selection(const CTYPE<OTS...> &oshape,
                                     const CTYPE<OTS...> &ooffset,
                                     const CTYPE<OTS...> &ostride):
                _oshape(oshape.size()),
                _offset(ooffset.size()),
                _stride(ostride.size())
            {
                std::copy(oshape.begin(),oshape.end(),_oshape.begin());
                std::copy(ooffset.begin(),ooffset.end(),_offset.begin());
                std::copy(ostride.begin(),ostride.end(),_stride.begin());
            }

            //------------------------------------------------------------------
            explicit array_selection():
                _oshape(0),
                _offset(0),
                _stride(0)
            {}

            //-----------------------------------------------------------------
            explicit array_selection(index_t &&oshape,index_t &ooffset,
                                     index_t &&ostride):
                _oshape(std::move(oshape)),
                _offset(std::move(ooffset)),
                _stride(std::move(ostride))
            {
            }
            
            //-----------------------------------------------------------------
            explicit array_selection(const index_t &oshape,const index_t &ooffset,
                                     const index_t &ostride):
                _oshape(std::move(oshape)),
                _offset(std::move(ooffset)),
                _stride(std::move(ostride))
            {
            }

            //-----------------------------------------------------------------
            explicit array_selection(const array_selection &s):
                _oshape(s._oshape),
                _offset(s._offset),
                _stride(s._stride)
            { }

            //-----------------------------------------------------------------
            array_selection(array_selection &&s):
                _oshape(std::move(s._oshape)),
                _offset(std::move(s._offset)),
                _stride(std::move(s._stride))
            { }

            //-----------------------------------------------------------------
            array_selection &operator=(const array_selection &s)
            {
                if(this == &s) return *this;

                _oshape = s._oshape;
                _offset = s._offset;
                _stride = s._stride;

                return *this;
            }

            //-----------------------------------------------------------------
            array_selection &operator=(array_selection &&s)
            {
                if(this == &s) return *this;

                _oshape = std::move(s._oshape);
                _offset = std::move(s._offset);
                _stride = std::move(s._stride);

                return *this;
            }


            //-----------------------------------------------------------------
            //! static creation function
            template<typename CTYPE,
                     typename = typename std::enable_if<
                     std::is_same<typename CTYPE::value_type,pni::core::slice>::value
                     >::type
                    >
            static array_selection<INDEXT> create(const CTYPE &s)
            {
                typedef container_utils<INDEXT> cutils_type;
                auto shape = cutils_type::create(s.size());
                auto offset = cutils_type::create(s.size());
                auto stride = cutils_type::create(s.size());

#ifdef NOFOREACH
                BOOST_FOREACH(auto sl,s)
#else
                for(auto sl: s)
#endif
                {
                    offset[sl.first()];
                    stride[sl.stride()];
                    shape[pni::core::size(sl)];
                }

                return array_selection<INDEXT>(std::move(shape),
                                       std::move(offset),
                                       std::move(stride));
            }

           
            //=================inquery methods=================================
            /*! 
            \brief get effective rank

            Return the effective rank of the selection. If a single element is
            selected the element count along each of the dimensions of the
            selection will be 1. As a result the rank will be zero. 
            For scalar selections the rank is 0. 

            \return effective rank
            */
            size_t rank() const 
            { 
                return _oshape.size() - std::count(_oshape.begin(),_oshape.end(),1);
            }

            //-----------------------------------------------------------------
            /*!
            \brief get effective shape

            Return the effective shape of the selection in an arbitary
            container. If a single scalar element is selected the return value
            will be an empty container. 

            \tparam CTYPE container type
            \return instance of CTYPE with effective shape
            */
            template<typename CTYPE> CTYPE shape() const
            {
                CTYPE c(rank());
                //now we have to copy only those values from the original shape
                //that are not equal 1
                std::copy_if(_oshape.begin(),_oshape.end(),c.begin(),
                             [](size_t i){ return i!=1; });
                return c;
            }

            //----------------------------------------------------------------- 
            /*! 
            \brief get selection size

            Get the number of elements stored in the selection. If a single
            element is selected the size is 1. If the selection is not
            initialized the size is 0;

            \return number of elements
            */
            size_t size() const 
            { 
                if(_oshape.empty()) return 0; //not initialized 

                if(rank() == 0) return 1; //scalar element selected 

                //compute the size and return it
                return std::accumulate(_oshape.begin(),_oshape.end(),1,
                                     std::multiplies<typename index_t::value_type>());
            }

            //=========methods to retrieve full selection information==========
            /*!
            \brief get full shape reference

            Return a reference to the container holding the full shape of the
            selection. 
            \return reference to full shape
            */
            const index_t &full_shape() const { return _oshape; }

            //-----------------------------------------------------------------
            /*! 
            \brief get full shape 

            Return the full shape of the selection stored in an arbitrary
            container type.
            \tparam CTYPE container type
            \return instance of CTYPE with the full shape
            */
            template<typename CTYPE> CTYPE full_shape() const 
            {
                CTYPE c(_oshape.size());
                std::copy(_oshape.begin(),_oshape.end(),c.begin());
                return c;
            }

            //-----------------------------------------------------------------
            /*!
            \brief get reference to offset

            Return a reference to the offset container of the selection object.
            \return reference to offsets
            */
            const index_t &offset() const { return _offset; }

            //-----------------------------------------------------------------
            /*! 
            \brief get offset 

            Return the offset values of the selection in an arbitary container.
            \tparam CTYPE container type
            \return instance of CTYPE with offset values
            */
            template<typename CTYPE> CTYPE offset() const
            {
                CTYPE c(_offset.size());
                std::copy(_offset.begin(),_offset.end(),c.begin());
                return c;
            }

            //-----------------------------------------------------------------
            /*! 
            \brief get reference to stride

            Return a reference to the stride container of the selection.
            \return stride reference
            */
            const index_t &stride() const { return _stride; }

            //-----------------------------------------------------------------
            /*! 
            \brief get stride

            Return the stride of the selection stored in an arbitrary STL
            container type. 
            \tparam CTYPE container type
            \return instance of CTYPE with the stride values
            */
            template<typename CTYPE> CTYPE stride() const
            {
                CTYPE c(_stride.size());
                std::copy(_stride.begin(),_stride.end(),c.begin());
                return c;
            }

            //================get indices======================================
            /*! 
            \brief compute original index

            The functionality of this template method can be best explained
            using an example. 
            \code
            typedef std::vector<size_t> itype;

            //create a (1,25,128) selection from a 3D array at offset (1,1,1)
            //and with stride (1,1,1)
            array_selection s(itype{1,25,128},itype{1,1,1},itype{1,1,1});

            //selection index
            itype sindex{2,100};

            //if we want to access data from the original array we need to
            //convert this to a 3D index
            itype oindex(3);
            s.index(sindex,oindex);

            //now the vector oindex holds the values {1,2,100} which can be used
            //to obtain data form the original array.

            \endcode
            The method assumes that all index containers are of appropriate
            size. If this is not the case an exception will be thrown

            \throws size_mismatch_error if sindex does not match the rank of the
            selection or if oindex does not match the rank of the original array

            \tparam ITYPE container type for the indices
            \param sindex original index of the selection
            \param oindex new index with the rank of the original array
            */
            template<typename ITYPE,typename OITYPE> 
                void index(const ITYPE &sindex,OITYPE &oindex) const
            {
                //check size - maybe move this one level up
                //check_equal_size(_oshape,oindex,EXCEPTION_RECORD);
                //check_equal_size(_shape,sindex,EXCEPTION_RECORD);

                //first copy the offsets to the oindex 
                //std::copy(_offset.begin(),_offset.end(),oindex.begin());

                //now we have to add index*stride from the selection index too
                //the appropriate locations
                auto os_iter = _oshape.begin(); //iter. over original shape
                auto st_iter = _stride.begin(); //iter. over selection strides
                auto si_iter = sindex.begin();  //iter. over selection index
                auto of_iter = _offset.begin(); //iter. over the offset

                //loop over output index
                for(auto &oi: oindex)
                {
                    size_t index = *of_iter++;
                    //oi = *of_iter++;
                    if(*os_iter++ != 1) index += (*st_iter)*(*si_iter++);
                    ++st_iter;  //need to increment this guy in any case
                    oi = index;
                }
            }

            //-----------------------------------------------------------------
            /*! 
            \brief compute the original index

            This is virtually the same as index(const ITYPE &sindex,const ITYPE
            &oindex) except that one does not have to take care about allocating
            the container for the original index.
            \tparam ITYPE container type (determined by the argument)
            \tparam OITYPE container type for the original index
            \param sindex selection index
            \return instance of ITYPE with the index in the original array
            \sa template<typename ITYPE> index(const ITYPE &sindex,const ITYPE
            &oindex) const
            */
            template<typename ITYPE,typename OITYPE> 
            ITYPE index(const OITYPE &sindex) const
            {
                ITYPE oindex(_oshape.size());
                try{ index(sindex,oindex); }
                EXCEPTION_FORWARD(size_mismatch_error);

                return oindex;
            }
            //! output operator
            /*
            friend std::ostream &
                operator<< <>(std::ostream &o,const array_selection<INDEXT> &s);
                */
    };

    //--------------------------------------------------------------------------
    template<typename INDEXT>
    std::ostream &operator<<(std::ostream &o,const array_selection<INDEXT> &s)
    {
        o<<"original data:"<<std::endl;
        auto oshape = s.template full_shape();
        auto offset = s.offset();
        auto stride = s.stride();
        for(size_t i=0;i<s._oshape.size();i++)
        {
            o<<i<<":\t"<<oshape[i]<<"\t"<<offset[i]<<"\t"<<stride[i];
            o<<std::endl;
        }
        shape_t shape = s.template shape<shape_t>();
        o<<"effective shape: ( ";
#ifdef NOFOREACH
        BOOST_FOREACH(auto v,shape)
#else
        for(auto v: shape)
#endif
            o<<v<<" ";
        
        o<<")"<<std::endl;

        return o;
    }
//end of namespace
}
}
