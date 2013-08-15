/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: May 30, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <pni/core/benchmark/benchmark_runner.hpp>

namespace pni{
namespace core{

    //--------------------------------------------------------------------------
    benchmark_result average(const benchmark_runner &bm)
    {
        float64 time = 0.;

#ifdef NOFOREACH
        for(auto iter = bm.begin();iter!=bm.end();++iter)
        {
            auto &result = *iter;
#else
        for(auto result: bm)
        {
#endif
            time += result.time();
        }

        time /= float64(bm.size());

        return benchmark_result(time,bm.begin()->unit());

    }

    //-------------------------------------------------------------------------
    benchmark_result standard_deviation(const benchmark_runner &bm)
    {
        float64 av = average(bm).time(); //compute the average value
        float64 error_sum = 0.;

        for(auto iter = bm.begin();iter!=bm.end();++iter)
        {
            error_sum += std::pow(iter->time()-av,2);
        }

        return benchmark_result(std::sqrt((1./(bm.size()-1))*error_sum),
                                bm.begin()->unit());
    }

//end of namespace
}
}
