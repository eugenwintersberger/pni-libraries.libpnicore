#ifndef __OPTRAITS_HPP__
#define __OPTRAITS_HPP__

#include "../Scalar.hpp"

namespace pni{
namespace utils{

    template<typename OT> struct OpTrait
    {
        typedef OT const& ref_type; 
    };

    template<typename T> struct OpTrait<Scalar<T> >
    {
        typedef Scalar<T> ref_type;
    };
//end of namespace
}
}


#endif
