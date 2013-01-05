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
#include "../Types.hpp"

#include<iostream>
#include<ctime>

namespace pni{
namespace core{

    /*!
    \brief clock() timer

    This timer uses the standard clock() function provided by the C standard
    library. It should only be used if C++11 std::chrono services are not available.
    */
    class ClockTimer
    {
        private:
            clock_t _start; //!< start time
            clock_t _stop;  //!< stop time

        public:
            //======================static members=================================
            static const String name; 
            //=======================constructors==================================
            //! default constructor
            ClockTimer():_start(0),_stop(0) {}

            //========================public member functions======================
            /*!
            \brief set start value

            This member function calls clock() and thus sets the start value of the
            timer. 
            */
            void start() { _start = clock(); }

            //---------------------------------------------------------------------
            /*!
            \brief set stop value

            Member function calling clock() and setting the stop value of the timer.
            */
            void stop() { _stop = clock(); }

            //---------------------------------------------------------------------
            /*!
            \brief get duration

            Returns the difference between the start and the stop time of the timer
            in units of seconds. 
            \return time duration
            */
            Float64 duration() const
            {
                return ((double)(_stop-_start))/CLOCKS_PER_SEC;
            }

            //---------------------------------------------------------------------
            //! get time unit
            String unit() const
            {
                return String("s");
            }
    };

    //setup the static name of the timer
    const String ClockTimer::name = String("ClockTimer");

//end of namespace
}
}
