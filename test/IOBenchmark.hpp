#ifndef __IOBENCHMARK_HPP__
#define __IOBENCHMARK_HPP__


#include "IOBenchmarkResult.hpp"
#include<list>

class IOBenchmark
{
    private:
        //! list with benchmark results
        std::list<IOBenchmarkResult> _results;

    public:
        //======================public types===================================
        typedef std::list<IOBenchmarkResult>::iterator iterator;
        typedef std::list<IOBenchmarkResult>::const_iterator const_iterator;

        //====================constructors and destructor=======================
        //! default constructor
        IOBenchmark():_results(0) {}

        //! destructor
        virtual ~IOBenchmark(){}

        //! perform all runs
        virtual void run(size_t n);

        //! run a single read cycle
        virtual void read_cycle() = 0;

        //! run a single write cycle
        virtual void write_cycle() = 0;

        //! get iterator to first element
        iterator begin() { return _results.begin(); }

        //! get iterator to last+1 element
        iterator end() { return _results.end(); }

        //! get const iterator to first element
        const_iterator begin() const { return _results.begin(); }

        //! get const iterator to last+1 element
        const_iterator end() const { return _results.end(); }
};


#endif
