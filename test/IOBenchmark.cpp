#include "IOBenchmark.hpp"
#include <ctime>

void IOBenchmark::run(size_t n)
{
    clock_t start,stop;

    for(size_t i=0;i<n;i++)
    {
        IOBenchmarkResult result;

        //run the write cycle
        start = clock();
        write_cycle();
        stop = clock();
        result.write_time((Float64)(stop-start)/CLOCKS_PER_SEC);

        //run the read cycle
        start = clock();
        read_cycle();
        stop = clock();
        result.read_time((Float64)(stop-start)/CLOCKS_PER_SEC);

        _results.push_back(result);
    }

}
