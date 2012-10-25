#ifndef __CLOCKTIMER_HPP__
#define __CLOCKTIMER_HPP__

#include "../../src/Types.hpp"

#include<iostream>
#include<ctime>

using namespace pni::utils;

class ClockTimer
{
    private:
        clock_t _start;
        clock_t _stop;

    public:
        //======================static members=================================
        static const String name; 
        //=======================constructors==================================
        ClockTimer():_start(0),_stop(0) {}

        //========================public member functions======================
        void start() { _start = clock(); }

        void stop() { _stop = clock(); }

        Float64 duration() const
        {
            return ((double)(_stop-_start))/CLOCKS_PER_SEC;
        }


        String unit() const
        {
            return String("s");
        }
};

const String ClockTimer::name = String("ClockTimer");


#endif
