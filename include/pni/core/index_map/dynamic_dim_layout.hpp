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
    //!
    //! \ingroup dim_layout_classes
    //! \brief dynamic memory layout 
    //!
    //! This class describes the memory layout of an array. Once created the
    //! layout cannot be altered. For resizing an array a new layout must be
    //! created. However, the layout can be defined at runtime.
    //! 
    //! \tparam STORAGET storage type to hold the data
    //! 
    template<typename STORAGET> class dynamic_dim_layout
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
            //! \brief default constructor
            //!
            explicit dynamic_dim_layout(): _counts(),_stride(),_offset() {}

            //!
            //! \brief constructor
            //! Construct the memory layout from arbitrary containers. 
            //! 
            //! \tparam CTYPE container type for input data
            //! \param counts container with count values
            //! \param stride container with stride values
            //! \param offset container with offset values
            template<typename CTYPE> 
            explicit dynamic_dim_layout(const CTYPE &counts,
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
            explicit dynamic_dim_layout(storage_type &&counts,
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

//end of namespace
}
}
