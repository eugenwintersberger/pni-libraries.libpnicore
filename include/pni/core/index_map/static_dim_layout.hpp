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
    //! \brief static dimension layout 
    //! 
    //! This is a static dimension layout. It is rather limited in comparison to
    //! dynamic_dim_layout. Its offset and stride values are always 0 and 1
    //! respectively. This class does not provide any custom constructor as
    //! everything that can be configured is already done at compile time.
    //! 
    //! \tparam DIMS number of elements along each dimension
    template<size_t ...DIMS> class static_dim_layout
    {
        public:
            //! storage type 
            typedef std::array<size_t,sizeof...(DIMS)> storage_type;
            //! value type
            typedef size_t value_type;
        private:
            //! static container with count data
            constexpr static storage_type _counts = {DIMS...};
        public:

            //-----------------------------------------------------------------
            //!
            //! \brief get counts
            //! 
            //! Return a reference to the container with count values. 
            //! 
            //! \return reference to count values
            const storage_type &counts() const noexcept { return _counts; }

            //-----------------------------------------------------------------
            //!
            //! \brief get offset values
            //! 
            //! Return a new storage_type instance with the offset values. 
            //! 
            //! \return offset values
            storage_type offset() const noexcept 
            {
                return storage_type().fill(value_type(0));
            }

            //-----------------------------------------------------------------
            //!
            //! \brief get stride values
            //! 
            //! Return a new storage_type instance with the stride values. 
            //!
            //! \return stride values
            storage_type stride() const  noexcept
            {
                return storage_type().fill(value_type(1));
            }

    };

    template<size_t ...DIMS> 
    constexpr typename static_dim_layout<DIMS...>::storage_type
    static_dim_layout<DIMS...>::_counts;

//end of namespace
}}
