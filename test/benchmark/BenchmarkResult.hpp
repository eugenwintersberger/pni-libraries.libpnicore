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
 *  Created on: Oct 24, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <iostream>
#include <pni/utils/Types.hpp>

using namespace pni::utils;

/*!
\brief result of a single benchmark

The BenchmarResult class holds all the information that is obtained during a
single benchmark. 

For timing the new classes from the chrono namespace are used. This should give
bettet. 
*/
class BenchmarkResult 
{
    private:
        //! time required for reading data
        Float64 _time;  
        //! unit of time
        String _unit;
    public:
        //====================constructors and destructor======================
        //! default constructor
        BenchmarkResult():
            _time(0.),
            _unit("")
        {}

        //---------------------------------------------------------------------
        /*!
        \brief constructor

        \param time the time the function took to run
        \param unit the unit used to measure the time
        */
        BenchmarkResult(Float64 time,const String &unit):
            _time(time),
            _unit(unit)
        {}

        //==================public member functions============================
        //! get time
        Float64 time() const { return _time; }

        //---------------------------------------------------------------------
        //! get the unit
        String unit() const { return _unit; }

};

//! output operator for benchmark result
std::ostream &operator<<(std::ostream &o,const BenchmarkResult &r);
