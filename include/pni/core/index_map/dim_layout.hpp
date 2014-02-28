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

#include <vector>
#include <array>
#include "../container_utils.hpp"
#include "dynamic_dim_layout.hpp"
#include "static_dim_layout.hpp"
#include "dim_algorithms.hpp"

namespace pni{
namespace core{
   
    //!
    //! \ingroup dim_layout_classes
    //! \brief default layout 
    //! 
    //! This is the default layout type. It is fully dynamic and can thus be 
    //! configured at runtime. 
    typedef dynamic_dim_layout<std::vector<size_t>> default_dim_layout;

    //!
    //! \ingroup dim_layout_classe
    //! \brief dimension layout of static rank
    //! 
    //! This dimension layout has a compile time rank. It should be used in all
    //! cases where the  number of dimensions is known at compile time. 
    //! \tparam RANK number of dimensions
    template<size_t RANK>
    using fixed_rank_dim_layout = dynamic_dim_layout<std::array<size_t,RANK> >;


//end of namespace
}
}
