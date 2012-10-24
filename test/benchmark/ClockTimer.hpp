#ifndef __CLOCKTIMER_HPP__
#define __CLOCKTIMER_HPP__

#include<iostream>
#include<ctime>

class ClockTimer
{
    private:
        clock_t _start;
        clock_t _stop;

    public:
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


#endif
