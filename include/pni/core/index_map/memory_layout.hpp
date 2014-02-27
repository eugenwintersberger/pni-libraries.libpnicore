//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Feb 27, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include "../container_utils.hpp"

namespace pni{
namespace core{

    //=========================================================================
    //
    // Algorithms used on memory layout objects 
    // 
    //=========================================================================

    //! 
    //! \ingroup index_mapping_classes 
    //! \brief total elements 
    //!
    //! Returns the total number of elements that the layout spans. 
    //!
    template<typename MEMLT> size_t span(const MEMLT &layout)
    {

    }

    //-------------------------------------------------------------------------
    //!
    //! \ingroup index_mapping_classes
    //! \brief number of elements
    //!
    //! Returns the total number of elements that can be addressed with this
    //! memory layout.
    //! This can simply be done by multiplying all the count values provided by
    //! the layout instance.
    /*!
     \f[  size = \prod_{i=1}^{r}c_i \f]
    */ 
    //! \tparam MEMLT memory layout type
    //! \param layout const reference to the layout instance
    //! \return number of reachable elements
    //! 
    template<typename MEMLT> size_t size(const MEMLT &layout)
    {
        return std::accumulate(layout.counts().begin(),
                               layout.counts().end(),
                               size_t(1),
                               std::multiplies<size_t>()); 
    }
   
    //-------------------------------------------------------------------------
    //!
    //! \ingroup index_mapping_classes
    //! \brief number of dimensions
    //! 
    //! Get the number of dimensions of a memory layout. 
    //!
    //! \tparam MEMLT memory layout type
    //! \param layout const reference to the layout instance
    //! \return number of dimensions
    //! 
    template<typename MEMLT> size_t rank(const MEMLT &layout)
    {
        return layout.counts().size();
    }

    //-------------------------------------------------------------------------
    //!
    //! \ingroup index_mapping_classes
    //! \brief check if compact
    //!
    //! Returns true if the memory layout is compact. This means that all stride
    //! values are 1.
    //! 
    //!
    template<typename MEMLT> bool is_compact(const MEMLT &layout)
    {
        typedef typename MEMLT::value_type value_type;

        return std::all_of(layout.stride().begin(),
                           layout.stride().end(),
                           [](const value_type &x){ return x==value_type(1);});
    }

    //-------------------------------------------------------------------------
    //!
    //! \ingroup index_mapping_classes
    //! \brief get effective rank 
    //!
    //! Returns the number of dimensions for which the count value is not one.
    //! Dimensions with a count value of one have typically no effect. 
    //!
    //! \tparam MEMLT memory layout type
    //! \param layout const reference to the layout instance
    //! \return number of dimensions with count value != 1
    //!
    template<typename MEMLT> bool effective_rank(const MEMLT &layout)
    {
        typedef typename MEMLT::value_type value_type;
        return std::count_if(layout.counts().begin(),
                             layout.counts().end(),
                             [](const value_type &x)
                             { return x!=value_type(1);});
    }

    //-------------------------------------------------------------------------
    //!
    //! \ingroup index_mapping_classes
    //! \brief expand index 
    //! 
    //! In some cases an it is usefull to use a compressed index tuple where the
    //! number of indices is equal to the effective rank (makes code more
    //! readable). However, for alter calculations the full index is required. 
    //! This function expands an index to this full index set. 
    //! 
    //! 
    template<typename MEMLT,
             typename EFFIT,
             typename FULLIT>
    void expand_index(const MEMLT &layout,const EFFIT &eindex,FULLIT &findex)
    {

    }


    //=========================================================================
    //!
    //! \ingroup index_mapping_classes
    //! \brief dynamic memory layout 
    //!
    //! This class describes the memory layout of an array. Once created the
    //! layout cannot be altered. For resizing an array a new layout must be
    //! created.
    //! 
    //! \tparam STORAGET storage type to hold the data
    //! 
    template<typename STORAGET> class mem_layout
    {
        public:
            //! container type for layout information
            typedef STORAGET storage_type;

            //! value type of the container
            typedef typename STORAGET::value_type value_type;
        private:
            typedef container_utils<STORAGET> cutils_type;
            //! number of elements along each dimension
            storage_type _counts; 

            //! stride along each dimension
            storage_type _stride;

            //! offset along each dimension
            storage_type _offset;

        public:
            //!
            //! \brief constructor
            //! Construct the memory layout from arbitrary containers. 
            //! 
            //! \tparam CTYPE container type for input data
            //! \param counts container with count values
            //! \param stride container with stride values
            //! \param offset container with offset values
            template<typename CTYPE> 
            explicit mem_layout(const CTYPE &counts,
                                const CTYPE &stride,
                                const CTYPE &offset):
                _counts(cutils_type::create(counts.size())),
                _stride(cutils_type::create(stride.size())),
                _offset(cutils_type::create(offset.size()))
            {
                std::copy(counts.begin(),counts.end(),_counts.begin());
                std::copy(stride.begin(),stride.end(),_stride.begin());
                std::copy(offset.begin(),offset.end(),_offset.begin());
            }

            //-----------------------------------------------------------------
            //!
            //! \brief move construct from params
            //! 
            //! Use this constructor for move construction from parameters. 
            //!
            //! \param counts rvalue for counts
            //! \param stride rvalue for strides
            //! \param offset rvalue for offsets
            explicit mem_layout(storage_type &&counts,
                                storage_type &&stride,
                                storage_type &&offset):
                _counts(std::forward<storage_type>(counts)),
                _stride(std::forward<storage_type>(stride)),
                _offset(std::forward<storage_type>(offset))
            {}

            //-----------------------------------------------------------------
            //!
            //! \brief get counts
            //!
            //! Returns a reference to the counts container. 
            //! \return counts container
            const storage_type &counts() const noexcept 
            { 
                return _counts; 
            }

            //-----------------------------------------------------------------
            //!
            //! \brief get stride
            //! 
            //! Return a reference to the stride container. 
            //! \return stride container
            const storage_type &stride() const noexcept 
            { 
                return _stride; 
            }

            //-----------------------------------------------------------------
            //!
            //! \brief get offset 
            //!
            //! Return a reference to the offset container. 
            //! \return offset container reference
            const storage_type &offset() const noexcept 
            { 
                return _offset; 
            }



    };

    //=========================================================================
    template<size_t N,ITYPES ...DIMS> class static_mem_layout
    {

    };





//end of namespace
}
}
