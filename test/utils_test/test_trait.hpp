//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// ===========================================================================
//
//  Created on: Oct 14, 2015
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/core/utilities/container_utils.hpp>
#include <vector>
#include "../data_generator.hpp"


template<typename T> struct test_trait
{
    typedef container_utils<T>           utils_type;
    typedef typename T::value_type       value_type;
    typedef std::vector<value_type>      ref_type; 
    typedef random_generator<value_type> generator_type;
};
