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

#include <typeinfo>
#include <pni/utils/Types.hpp>
#include <pni/utils/Array.hpp>
#include <pni/utils/service.hpp>

using namespace pni::utils;

template<typename ATYPE> class MultiIndexIOArray
{
    private:
        ATYPE _array;
        shape_t _shape;
        typename ATYPE::value_type _result;
    public:
        //==================construtors========================================
        MultiIndexIOArray(ATYPE &&array):
            _array(std::move(array)),
            _shape(_array.template shape<shape_t>())
        { }

        //================public member functions==============================
        void write_data()
        {
            typedef typename ATYPE::value_type value_t;
            value_t index(0);


            for(size_t i=0;i<_shape[0];++i)
                for(size_t j=0;j<_shape[1];++j)
                    _array(i,j) = index++;

        }

        //---------------------------------------------------------------------
        void read_data()
        {
            _result = typename ATYPE::value_type(0);

            for(size_t i=0;i<_shape[0];++i)
                for(size_t j=0;j<_shape[1];++j)
                    _result += _array(i,j);
        }


        //---------------------------------------------------------------------
        String name() const
        {
            return String("Multiindex (variadic) ")+demangle_cpp_name(typeid(ATYPE).name());
        }
            
};

