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
 *  Created on: Nov 30, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <pni/utils/Types.hpp>

using namespace pni::utils;

template<typename CTYPE> class LinearIOContainerIterator
{
    private:
        CTYPE _container;
        typename CTYPE::value_type _result;
    public:
        //==================construtors========================================
        LinearIOContainerIterator(CTYPE &&cont):_container(std::move(cont)) {}

        //================public member functions==============================
        void write_data()
        {
            typedef typename CTYPE::value_type value_t;
            value_t index(0);

            for(auto iter = _container.begin();iter!=_container.end();++iter) 
                *iter = index++;
        }

        //---------------------------------------------------------------------
        void read_data()
        {
            _result = typename CTYPE::value_type(0);

            for(auto iter = _container.begin();iter!=_container.end();++iter) 
                _result += *iter;
        }


        //---------------------------------------------------------------------
        String name() const
        {
            return String("Linear IO DBuffer template benchmark");
        }
            
};
