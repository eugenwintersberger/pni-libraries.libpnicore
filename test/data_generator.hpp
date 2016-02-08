//
// (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//************************************************************************
//
//  Created on: Jan 21, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <sstream>
#include <pni/core/types.hpp>
#include <boost/lexical_cast.hpp>

#ifdef NOCPPRAND
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/mersenne_twister.hpp>
#else
#include <random>
#endif

using namespace pni::core;

//=============we need different distributions for integer and float============
template<typename T,bool is_int> struct distribution_map;

//------------distribution for integral types-----------------------------------
template<typename T> struct distribution_map<T,true>
{
    typedef std::uniform_int_distribution<T> distribution_type;
};

#ifdef MSVC
template<> struct distribution_map<uint8, true>
{
	typedef std::uniform_int_distribution<uint16> distribution_type;
};

template<> struct distribution_map<int8, true>
{
	typedef std::uniform_int_distribution<int16> distribution_type;
};
#endif

//------------------distribution for floating point types-----------------------
template<typename T> struct distribution_map<T,false>
{
    typedef std::uniform_real_distribution<T> distribution_type;
};

//=================the default generator=======================================
template<typename T> class random_generator
{
    private:
        std::mt19937_64 _engine;
		typedef distribution_map<T, pni::core::type_info<T>::is_integer> map_t;
        typename map_t::distribution_type _distribution;

    public:
        random_generator(T a,T b):
            _engine(std::random_device()()),
            _distribution(a,b)
        {}

        random_generator():
            _engine(std::random_device()()),
            _distribution(0.2*pni::core::type_info<T>::min(),
				          0.2*pni::core::type_info<T>::max())
        {}

        T operator()()
        {
            return _distribution(_engine);
        }
};

#ifdef MSVC
template<> class random_generator<uint8>
{
    private:        
        random_generator<uint16> _generator;

	public:
		random_generator(uint8 a,uint8 b):
			_generator(uint16(a),uint16(b))
		{}

		random_generator():
			_generator(0,255)
		{}

		uint8 operator()()
		{
			return uint8(_generator());
		}
};

template<> class random_generator<int8>
{
private:
	random_generator<int16> _generator;

public:
	random_generator(int8 a, int8 b) :
		_generator(int16(a), int16(b))
	{}

	random_generator() :
		_generator(-127,127)
	{}

	int8 operator()()
	{
		return int8(_generator());
	}
};
#endif
//--------------------------------------			----
template<typename T> class random_generator<std::complex<T>>
{
    private:
        typedef pni::core::type_info<T> tinfo_type;
        random_generator<T> _real_generator;
       	random_generator<T> _imag_generator;
    public:
        random_generator(T a,T b):
            _real_generator(a,b),
            _imag_generator(a,b)
        {}

        random_generator():
            _real_generator(),
            _imag_generator()
        {}
        
        std::complex<T> operator()()
        {
            return std::complex<T>(_real_generator(),
                                   _imag_generator());
        }
};

//-----------------------------------------------------------------------------
template<> class random_generator<bool_t>
{
    private:
        random_generator<unsigned short> _generator;
    public:

        random_generator();

        bool_t operator()();
};

//-----------------------------------------------------------------------------
//!
//! \brief generating random strings
//! 
//! This random number generator
template<> class random_generator<string>
{
    private:
        static const std::vector<char> _char_vector ;
        random_generator<size_t> _line_size_generator;
        random_generator<size_t> _char_index_generator;
    public:
        random_generator(size_t nchars);

        random_generator();

        string operator()();
};


//-----------------------------------------------------------------------------
//!
//! \brief binary random generator
//!
//! Generates random binary values. These values are unsigned integers between
//! 0 and 255. Due to its simple nature the generator has no customizable 
//! constructor.
//! 
template<> class random_generator<binary>
{
    private:
        random_generator<uint8> _generator;
    public:
        random_generator():
            _generator(0,255)
        {}

        binary operator()()
        {
            return binary(_generator());
        }
};
    
