#ifndef __BENCHMARK_HPP__
#define __BENCHMARK_HPP__


#include "BenchmarkResult.hpp"
#include<list>
#include<functional>

class Benchmark
{
    private:
        //! list with benchmark results
        std::list<BenchmarkResult> _results;

    public:
        //======================public types===================================
        typedef std::list<BenchmarkResult>::iterator iterator;
        typedef std::list<BenchmarkResult>::const_iterator const_iterator;
        typedef std::function<void()> function_t;

        //====================constructors and destructor=======================
        //! default constructor
        Benchmark():_results(0) {}

        //! destructor
        virtual ~Benchmark(){}

        //! perform all runs
        template<typename TIMERT> void run(size_t n,function_t &func);

        //! get iterator to first element
        iterator begin() { return _results.begin(); }

        //! get iterator to last+1 element
        iterator end() { return _results.end(); }

        //! get const iterator to first element
        const_iterator begin() const { return _results.begin(); }

        //! get const iterator to last+1 element
        const_iterator end() const { return _results.end(); }

        //! get size
        size_t size() const { return _results.size(); }
};

template<typename TIMERT> void Benchmark::run(size_t n,function_t &func)
{
    for(size_t i=0;i<n;i++)
    {
        TIMERT timer;

        //run the write cycle
        timer.start();
        func();
        timer.stop();

        //getting the result
        BenchmarkResult result(timer.duration(),timer.unit());
        _results.push_back(result);
    }

}

BenchmarkResult average(const Benchmark &bm)
{
    Float64 time = 0.;

    for(auto result: bm)
        time += result.time();

    time /= Float64(bm.size());

    return BenchmarkResult(time,bm.begin()->unit());
}


#endif
