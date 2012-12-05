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

#include <pni/utils/Types.hpp>

#include<chrono>
#include<iostream>

using namespace pni::utils;

template<typename DTYPE> struct DurationUnitMap;

template<> struct DurationUnitMap<std::chrono::nanoseconds>
{
    static const String unit;
};

const String DurationUnitMap<std::chrono::nanoseconds>::unit = String("ns");

template<> struct DurationUnitMap<std::chrono::microseconds>
{
    static const String unit;
};

const String DurationUnitMap<std::chrono::microseconds>::unit = String("us");

template<> struct DurationUnitMap<std::chrono::milliseconds>
{
    static const String unit;
};

const String DurationUnitMap<std::chrono::milliseconds>::unit=String("ms");

template<> struct DurationUnitMap<std::chrono::seconds>
{
    static const String unit;
};

const String DurationUnitMap<std::chrono::seconds>::unit = String("s");

template<> struct DurationUnitMap<std::chrono::minutes>
{
    static const String unit;
};

const String DurationUnitMap<std::chrono::minutes>::unit = String("min");

template<> struct DurationUnitMap<std::chrono::hours>
{
    static const String unit;
};

const String DurationUnitMap<std::chrono::hours>::unit = String("h");

/*!
\brief timer class using chrono

This timer class is using the chrono framework of the C++ standard. 
To create a timer instance using the high_resolution_clock one could use 
the following code to obtain a result in nanoseconds
\code
#include<chrono>

....
ChronoTimer<std::chrono::high_resolution_clock,
            std::chrono::nanoseconds> timer;

//start the timer
timer.start();

......
//stop the timer
timer.stop();

std::cout<<timer.duration()<<" ("<<timer.unit()<<")"<<std::endl;

\endcode

\tparam CLKT clock type
\tparam DTYPE duration type
*/
template<typename CLKT,typename DTYPE> class ChronoTimer
{
    private:
        typename CLKT::time_point _start; //!< start time
        typename CLKT::time_point _stop;  //!< end time

    public:
        //=====================static members==================================
        static const String name;
        //=======================public types==================================
        //! default constructor
        ChronoTimer(): _start(),_stop() {}

        //===========================public member functions===================
        //! start the timer
        void start() { _start = CLKT::now(); }

        //---------------------------------------------------------------------
        //! stop the timer
        void stop()  { _stop  = CLKT::now(); }

        //---------------------------------------------------------------------
        //! get the duration as double
        Float64 duration() const
        {
            return Float64(std::chrono::duration_cast<DTYPE>(_stop-_start).count());
        }

        //---------------------------------------------------------------------
        //! get the unit of the timer
        String unit() const 
        {
            return String(DurationUnitMap<DTYPE>::unit);           
        }
};

template<typename CLKT,typename DTYPE>
const String ChronoTimer<CLKT,DTYPE>::name = String("ChronoTimer");
