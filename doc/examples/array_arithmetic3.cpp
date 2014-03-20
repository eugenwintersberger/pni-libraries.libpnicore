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
// Created on: Mar 18, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

//-----------------------------------------------------------------------------
// basic linear algebra
//-----------------------------------------------------------------------------
#include <iostream>
#include <algorithm>
#include <random>
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>

using namespace pni::core;

template<typename T,size_t N> using matrix_temp = static_array<T,N,N>;
template<typename T,size_t N> using vector_temp = static_array<T,N>;

template<typename T,size_t N>
std::ostream &operator<<(std::ostream &o,const matrix_temp<T,N> &m)
{
    for(size_t i = 0;i<3;++i)
    {
        o<<"| ";
        for(size_t j=0;j<3;++j) o<<m(i,j)<<" ";
        o<<"|"<<std::endl;
    }

    return o;
}

template<typename T,size_t N>
std::ostream &operator<<(std::ostream &o,const vector_temp<T,N> &v)
{
    for(auto x: v) o<<"| "<<x<<" |"<<std::endl;
    return o;
}

template<typename T,size_t N>
vector_temp<T,N> mv_mult(const matrix_temp<T,N> &m,const vector_temp<T,N> &v)
{
    vector_temp<T,N> result;

    size_t i = 0;
    for(auto &r: result)
    {
        const auto col = m(i++,slice(0,N));
        const auto dot = col*v;
        r = std::accumulate(dot.begin(),dot.end(),T(0));
    }

    return result;
}

template<typename T,size_t N>
vector_temp<T,N> mv_mult(const vector_temp<T,N> &v,const matrix_temp<T,N> &m)
{
    vector_temp<T,N> result;

    size_t i = 0;
    for(auto &r: result)
    {
        const auto row = m(slice(0,N),i++);
        const auto dot = row*v;
        r = std::accumulate(dot.begin(),dot.end(),T(0));
    }

    return result;
}

template<typename T,size_t N>
matrix_temp<T,N> mv_mult(const matrix_temp<T,N> &m1,const matrix_temp<T,N> &m2)
{
    matrix_temp<T,N> result;

    for(size_t i=0;i<N;++i)
    {
        for(size_t j=0;j<N;++j)
        {
            const auto row = m1(i,slice(0,N));
            const auto col = m2(slice(0,N),j);
            const auto dot = row*col;
            result(i,j) = std::accumulate(dot.begin(),dot.end(),T(0));
        }
    }
    return result;
}

typedef float64                    number_type;
typedef vector_temp<number_type,3> vector_type;
typedef matrix_temp<number_type,3> matrix_type;


int main(int argc,char **argv)
{
    vector_type v  = vector_type::create({3},{1,2,3});
    matrix_type m1 = matrix_type::create({3,3},{1,2,3,4,5,6,7,8,9});
    matrix_type m2 = matrix_type::create({3,3},{9,8,7,6,5,4,3,2,1});

    std::cout<<"m1 = "<<std::endl<<m1<<std::endl;
    std::cout<<"m2 = "<<std::endl<<m2<<std::endl;
    std::cout<<"v  = "<<std::endl<<v<<std::endl;
    std::cout<<"m1.v = "<<std::endl<<mv_mult(m1,v)<<std::endl;
    std::cout<<"v.m1 = "<<std::endl<<mv_mult(v,m1)<<std::endl;
    std::cout<<"m1.m2 = "<<std::endl<<mv_mult(m1,m2)<<std::endl;
                               
    return 0;
}

