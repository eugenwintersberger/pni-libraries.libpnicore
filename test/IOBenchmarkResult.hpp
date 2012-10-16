#ifndef __IOBENCHMARKRESULT_HPP__
#define __IOBENCHMARKRESULT_HPP__

#include<iostream>
#include "Types.hpp"

using namespace pni::utils;

class IOBenchmarkResult 
{
    private:
        //! time required for reading data
        Float64 _read_time;  
        //! time required for writting data
        Float64 _write_time;
    public:
        //! default constructor
        IOBenchmarkResult():
            _read_time(0.),
            _write_time(0.)
        {}

        /*!
        \brief constructor

        \param rtime reading time
        \param wtime writing time
        */
        IOBenchmarkResult(Float64 rtime,Float64 wtime):
            _read_time(rtime),
            _write_time(wtime)
        {}

        //! get read time
        Float64 read_time() const { return _read_time; }
        //! set read_time
        void read_time(Float64 t) { _read_time = t; }

        //! get write time
        Float64 write_time() const { return _write_time; }
        //! set write time
        void write_time(Float64 t) { _write_time = t; }

};

//! output operator for benchmark result
std::ostream &operator<<(std::ostream &o,const IOBenchmarkResult &r);


#endif
