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
//  Created on: Oct 22, 2015
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once
#include <boost/math/special_functions/sign.hpp>
#include <pni/core/types.hpp>
#include <cmath>

template<typename T> struct add_ranges
{
    T rhs_min() const { return 0.5*pni::core::type_info<T>::min(); }
    T rhs_max() const { return 0.5*pni::core::type_info<T>::max(); }

    T lhs_min() const { return rhs_min(); }
    T lhs_max() const { return rhs_max(); } 
};

template<typename T> struct add_ranges<std::complex<T>>
{
    T rhs_min() const { return 0.5*pni::core::type_info<T>::min(); }
    T rhs_max() const { return 0.5*pni::core::type_info<T>::max(); }

    T lhs_min() const { return rhs_min(); }
    T lhs_max() const { return rhs_max(); } 
};

template<typename T> struct mult_ranges
{
    T rhs_min() const 
    { 
        using namespace boost::math;
        T min = pni::core::type_info<T>::min();

        return sign(min)*std::sqrt(sign(min)*min); 
    }
    T rhs_max() const { return std::sqrt(pni::core::type_info<T>::max()); }

    T lhs_min() const { return rhs_min(); }
    T lhs_max() const { return rhs_max(); } 
};

template<typename T> struct mult_ranges<std::complex<T>>
{
    mult_ranges<T> base_range;
    T rhs_min() const { return 0.5*base_range.rhs_min(); }
    T rhs_max() const { return 0.5*base_range.rhs_max(); }

    T lhs_min() const { return 0.5*base_range.lhs_min(); }
    T lhs_max() const { return 0.5*base_range.lhs_max(); } 
};

template<typename T> struct div_ranges
{
    T rhs_min() const { return T(1); }
    T rhs_max() const { return 0.5*pni::core::type_info<T>::max(); }

    T lhs_min() const { return 0.8*pni::core::type_info<T>::min(); }
    T lhs_max() const { return 0.8*pni::core::type_info<T>::max(); } 
};

template<typename T> struct div_ranges<std::complex<T>>
{
    div_ranges<T> base_range;
    
    T rhs_min() const { return base_range.rhs_min(); }
    T rhs_max() const { return base_range.rhs_max(); }

    T lhs_min() const { return base_range.lhs_min(); }
    T lhs_max() const { return base_range.lhs_max(); } 
};

