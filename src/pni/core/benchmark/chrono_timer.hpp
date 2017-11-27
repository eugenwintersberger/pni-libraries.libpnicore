//
// (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpniio.
//
// libpniio is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpniio is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
//
// ============================================================================
//
//  Created on: Oct 24, 2012
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/types.hpp>

#include<chrono>
#include<iostream>

namespace pni{
namespace core{

    //!
    //! \ingroup benchmark_classes
    //! \brief unit map
    //!
    //! This template maps the name type of a chrono clock representing a 
    //! time unit on a string value.
    //!
    //! \tparam DTYPE chrono duration time
    //!
    template<typename DTYPE> struct duration_unit_map;

#define DURATIONUNITMAP(durationtype)\
        template<> struct duration_unit_map<durationtype>\
        {\
            static const string unit;\
        }

#define DURATIONUNITMAPINIT(durationtype,unit_string)\
        const string duration_unit_map<durationtype>::unit = string(unit_string)



    //! \cond NO_API_DOC
    DURATIONUNITMAP(std::chrono::nanoseconds);
    DURATIONUNITMAP(std::chrono::microseconds);
    DURATIONUNITMAP(std::chrono::milliseconds);
    DURATIONUNITMAP(std::chrono::seconds);
    DURATIONUNITMAP(std::chrono::minutes);
    DURATIONUNITMAP(std::chrono::hours);
    //! \endcond NO_API_DOC

    //!
    //! \ingroup benchmark_classes
    //! \brief timer class using chrono
    //!
    //! This timer class is using the chrono framework of the C++ standard. 
    //! To create a timer instance using the high_resolution_clock one 
    //! could use the following code to obtain a result in nanoseconds
    /*!
    \code
    #include<pni/core/benchmark/chrono_timer.hpp>
    
    ....
    chrono_timer<std::chrono::high_resolution_clock,
                std::chrono::nanoseconds> timer;
    
    //start the timer
    timer.start();
    
    ......
    //stop the timer
    timer.stop();
    
    std::cout<<timer.duration()<<" ("<<timer.unit()<<")"<<std::endl;
    
    \endcode
    !*/
    //! \tparam CLKT clock type
    //! \tparam DTYPE duration type
    //!
    template<
             typename CLKT,
             typename DTYPE
            > 
    class chrono_timer
    {
        private:
            typename CLKT::time_point _start; //!< start time
            typename CLKT::time_point _stop;  //!< end time

        public:
            //=====================static members===============================
            //! name of the timer
            static const string name;
            //=======================public types===============================
            //! default constructor
            chrono_timer(): _start(),_stop() {}

            //===========================public member functions================
            //! start the timer
            void start() { _start = CLKT::now(); }

            //------------------------------------------------------------------
            //! stop the timer
            void stop()  { _stop  = CLKT::now(); }

            //------------------------------------------------------------------
            //! get the duration as double
            float64 duration() const
            {
                return float64(std::chrono::duration_cast<DTYPE>(_stop-_start).count());
            }

            //------------------------------------------------------------------
            //! get the unit of the timer
            string unit() const 
            {
                return string(duration_unit_map<DTYPE>::unit);           
            }
    };

    //setup the static name of the timer
    template<typename CLKT,typename DTYPE>
    const string chrono_timer<CLKT,DTYPE>::name = string("chrono_timer");

//end of namespace
}
}
