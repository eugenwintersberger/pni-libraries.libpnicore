/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 *  Created on: Oct 24, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include "../Types.hpp"

#include<chrono>
#include<iostream>

namespace pni{
namespace core{

    /*!
    \brief unit map

    This template maps the name type of a chrono clock representing a time unit
    on a string value.
    \tparam DTYPE chrono duration time
    */
    template<typename DTYPE> struct DurationUnitMap;

#define DURATIONUNITMAP(durationtype,unit_string)\
        template<> struct DurationUnitMap<durationtype>\
        {\
            static const String unit;\
        };\
        const String DurationUnitMap<durationtype>::unit = String(unit_string)

    //! \cond NO_API_DOC
    DURATIONUNITMAP(std::chrono::nanoseconds,"ns");
    DURATIONUNITMAP(std::chrono::microseconds,"us");
    DURATIONUNITMAP(std::chrono::milliseconds,"ms");
    DURATIONUNITMAP(std::chrono::seconds,"s");
    DURATIONUNITMAP(std::chrono::minutes,"min");
    DURATIONUNITMAP(std::chrono::hours,"h");
    //! \endcond NO_API_DOC

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
            //=====================static members===============================
            static const String name;
            //=======================public types===============================
            //! default constructor
            ChronoTimer(): _start(),_stop() {}

            //===========================public member functions================
            //! start the timer
            void start() { _start = CLKT::now(); }

            //------------------------------------------------------------------
            //! stop the timer
            void stop()  { _stop  = CLKT::now(); }

            //------------------------------------------------------------------
            //! get the duration as double
            Float64 duration() const
            {
                return Float64(std::chrono::duration_cast<DTYPE>(_stop-_start).count());
            }

            //------------------------------------------------------------------
            //! get the unit of the timer
            String unit() const 
            {
                return String(DurationUnitMap<DTYPE>::unit);           
            }
    };

    //setup the static name of the timer
    template<typename CLKT,typename DTYPE>
    const String ChronoTimer<CLKT,DTYPE>::name = String("ChronoTimer");

//end of namespace
}
}
