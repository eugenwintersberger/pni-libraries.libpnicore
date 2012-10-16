#include "IOBenchmarkResult.hpp"

std::ostream &operator<<(std::ostream &o,const IOBenchmarkResult &r)
{
    o<<r.read_time()<<"\t"<<r.write_time();
    return o;
}
