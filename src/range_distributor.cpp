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
 *
 *  Created on: Mar 7, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "range_distributor.hpp"

namespace pni{
namespace core{

    range_distributor::range_distributor(size_t n,size_t s)
        :_ranges(n)
    {
        size_t nres = s%n;
        size_t ni = (s-nres)/n;

        size_t start=0,stop=0;
       // std::cout<<a.size()<<std::endl;
        for(size_t i = 0;i<n;++i)
        {
            if(i==0) start = 0;
            else start = stop;

            stop = start+ni;
            if(nres)
            {
                stop++;
                nres--;
            }
            _ranges[i] = {start,stop};
        }
    }

}
}
