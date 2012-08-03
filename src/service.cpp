#include "service.hpp"

namespace pni{
namespace utils{

    String demangle_cpp_name(const char *n)
    {
#if USE_GNU_DEMANGLING
        char *rname;
        std::size_t len;
        int stat;
        rname = abi::__cxa_demangle(n,NULL,&len,&stat);

        if(rname!=NULL)
        {
            String out(rname);
            std::free(rname);
            return out;
        }

        return String("Cannot Demangle name of symbol ")+String(n);
#else
        return String(n);
#endif
    }

//end of namespace
}
}
