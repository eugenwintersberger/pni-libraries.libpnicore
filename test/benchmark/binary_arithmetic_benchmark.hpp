/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 *
 *  Created on: Feb 19, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

template<typename ATYPE> class binary_arithmetic_benchmark
{
    public:
        binary_arithmetic_benchmark(ATYPE &a) {}

        void add(ATYPE &c,const ATYPE &a,const ATYPE &b)
        {
            c = a + b;
        }

        void sub(ATYPE &c,const ATYPE &a,const ATYPE &b)
        {
            c = a - b;
        }


        void mult(ATYPE &c,const ATYPE &a,const ATYPE &b)
        {
            c = a * b;
        }

        void div(ATYPE &c,const ATYPE &a,const ATYPE &b)
        {
            c= a/b;
        }

};
