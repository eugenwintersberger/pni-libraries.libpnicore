/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 *  Created on: Jan 21, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

struct data_generator
{
    template<typename ITTARGET,typename ITARG,typename GENERATOR>
    static void fill(ITTARGET &begin,ITTARGET &end,const ITARG &arg,
                       const GENERATOR &gen);

    template<typename ITTARGET,typename GENERATOR>
    static void fill(ITTARGET &&begin,ITTARGET &&end,GENERATOR &&gen);
};

template<typename ITTARGET,typename ITARG,typename GENERATOR>
void data_generator::fill(ITTARGET &begin,ITTARGET &end,
                               const ITARG &arg,const GENERATOR &gen)
{
    for(auto iter=begin;iter!=end;++iter)
        *iter = gen(*arg++);
}

template<typename ITTARGET,typename GENERATOR>
void data_generator::fill(ITTARGET &&begin,ITTARGET &&end,
                               GENERATOR &&gen)
{
    for(auto iter = begin;iter!=end;++iter)
        *iter = gen();
}
