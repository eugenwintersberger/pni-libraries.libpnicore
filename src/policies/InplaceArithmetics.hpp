/*
 * SimpleArithmetics.hpp
 *
 *  Created on: Aug 31, 2011
 *      Author: eugen
 */

#ifndef INPLACEARITHMETICS_HPP_
#define INPLACEARITHMETICS_HPP_

#include <limits>

#include "../Exceptions.hpp"
#include "TypeInfo.hpp"

namespace pni{
namespace utils{

//! \cond no_doc
//Inplace arithmetics of typed objects - the object can only be a left-value
class InplaceArithmetics{
public:
	//object with a scalar
	template<typename ATYPE> 
        static void add_inplace(ATYPE &a,typename ATYPE::value_type b)
    {
        
    }
    template<typename ATYPE,typename BTYPE> 
        static void add_inplace(ATYPE &a,const BTYPE &b)
    {
    }

};

// \endcond



//end namespace
}
}

#endif /* INPLACEARITHMETICS_HPP_ */
