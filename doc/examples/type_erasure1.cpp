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
// ===========================================================================
//
// Created on: Mar 28, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

//-----------------------------------------------------------------------------
#include <iostream>
#include <pni/core/types.hpp>
#include <pni/core/type_erasures.hpp>

using namespace pni::core;

int main(int argc,char **argv)
{
    //construction from a number
    float64 number = 10.234;
    value v(number);
    std::cout<<v<<std::endl;

    //conversion 
    auto x = v.as<float64>();
    std::cout<<x<<std::endl;

    //create an empty value
    value v2 = value::create<float64>();
    v2 = number;
    std::cout<<v2<<std::endl;

    //create a value from a literal
    value v3(3.2123);
    std::cout<<v3<<" ("<<v3.type_id()<<")"<<std::endl;

    v3 = 13;
    std::cout<<v3<<" ("<<v3.type_id()<<")"<<std::endl;

    return 0;
}

