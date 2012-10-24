#ifndef __CHRONOTIMER_HPP__
#define __CHRONOTIMER_HPP__

#include<pni/utils/Types.hpp>

#include<chrono>
#include<iostream>

using namespace pni::utils;

template<typename DTYPE> struct DurationUnitMap;

template<> struct DurationUnitMap<std::nanoseconds>
{
    static const char unit[]="ns";
};

template<> struct DurationUnitMap<std::microseconds>
{
    static const char unit[]="us";
};

template<> struct DurationUnitMap<std::milliseconds>
{
    static const char unit[]="ms";
};

template<> struct DurationUnitMap<std::seconds>
{
    static const char unit[]="s";
};

template<> struct DurationUnitMap<std::minutes>
{
    static const char unit[]="min";
};

template<> struct DurationUnitMap<std::hours>
{
    static const char unit[]="h";
};

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

#endif
