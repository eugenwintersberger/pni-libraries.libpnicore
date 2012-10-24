#include "BenchmarkResult.hpp"

std::ostream &operator<<(std::ostream &o,const BenchmarkResult &r)
{
    o<<r.time()<<"\t("<<r.unit()<<")";
    return o;
}
