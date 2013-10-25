/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 * Created on: Oct 25, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once
#include "index_map.hpp"
#include "static_index_map.hpp"
#include "index_policy.hpp"
#include "c_index_policy_imp.hpp"

namespace pni{
namespace core{
    //define a C index policy
    typedef index_policy<c_index_policy_imp> c_index_policy;

    //this header file defines some default index maps
    template<size_t... DIMS> using static_cindex_map = static_index_map<c_index_policy,DIMS...>;

    //define the default dynamic C-index map
    typedef index_map<std::vector<size_t>,c_index_policy> cindex_map;

//end of namespace
}
}
