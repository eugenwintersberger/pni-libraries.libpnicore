#ifndef __BENCHMARKRESULT_HPP__
#define __BENCHMARKRESULT_HPP__

#include<iostream>
#include "Types.hpp"

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


#endif
