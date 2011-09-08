/*
 * TypeCompat.hpp
 *
 *  Created on: Sep 8, 2011
 *      Author: eugen
 */

#ifndef TYPECOMPAT_HPP_
#define TYPECOMPAT_HPP_

#include "PNITypes.hpp"

namespace pni{
namespace utils{


template<typename A,typename B> class TypeCompat{
public:
	static const bool isAssignable = true;
};

#define SET_TYPE_COMPATABILITY(A,B,ASS)\
	template<> class TypeCompat<A,B>{\
	public:\
		static const bool isAssignable = ASS;\
};

//you can never assign a Float or Complex to an integer

SET_TYPE_COMPATABILITY(Int8,Float32,false);
SET_TYPE_COMPATABILITY(Int8,Float64,false);
SET_TYPE_COMPATABILITY(Int8,Float128,false);
SET_TYPE_COMPATABILITY(Int8,Complex32,false);
SET_TYPE_COMPATABILITY(Int8,Complex64,false);
SET_TYPE_COMPATABILITY(Int8,Complex128,false);

SET_TYPE_COMPATABILITY(UInt8,Float32,false);
SET_TYPE_COMPATABILITY(UInt8,Float64,false);
SET_TYPE_COMPATABILITY(UInt8,Float128,false);
SET_TYPE_COMPATABILITY(UInt8,Complex32,false);
SET_TYPE_COMPATABILITY(UInt8,Complex64,false);
SET_TYPE_COMPATABILITY(UInt8,Complex128,false);

SET_TYPE_COMPATABILITY(Int16,Float32,false);
SET_TYPE_COMPATABILITY(Int16,Float64,false);
SET_TYPE_COMPATABILITY(Int16,Float128,false);
SET_TYPE_COMPATABILITY(Int16,Complex32,false);
SET_TYPE_COMPATABILITY(Int16,Complex64,false);
SET_TYPE_COMPATABILITY(Int16,Complex128,false);

SET_TYPE_COMPATABILITY(UInt16,Float32,false);
SET_TYPE_COMPATABILITY(UInt16,Float64,false);
SET_TYPE_COMPATABILITY(UInt16,Float128,false);
SET_TYPE_COMPATABILITY(UInt16,Complex32,false);
SET_TYPE_COMPATABILITY(UInt16,Complex64,false);
SET_TYPE_COMPATABILITY(UInt16,Complex128,false);

SET_TYPE_COMPATABILITY(Int32,Float32,false);
SET_TYPE_COMPATABILITY(Int32,Float64,false);
SET_TYPE_COMPATABILITY(Int32,Float128,false);
SET_TYPE_COMPATABILITY(Int32,Complex32,false);
SET_TYPE_COMPATABILITY(Int32,Complex64,false);
SET_TYPE_COMPATABILITY(Int32,Complex128,false);

SET_TYPE_COMPATABILITY(UInt32,Float32,false);
SET_TYPE_COMPATABILITY(UInt32,Float64,false);
SET_TYPE_COMPATABILITY(UInt32,Float128,false);
SET_TYPE_COMPATABILITY(UInt32,Complex32,false);
SET_TYPE_COMPATABILITY(UInt32,Complex64,false);
SET_TYPE_COMPATABILITY(UInt32,Complex128,false);

SET_TYPE_COMPATABILITY(Int64,Float32,false);
SET_TYPE_COMPATABILITY(Int64,Float64,false);
SET_TYPE_COMPATABILITY(Int64,Float128,false);
SET_TYPE_COMPATABILITY(Int64,Complex32,false);
SET_TYPE_COMPATABILITY(Int64,Complex64,false);
SET_TYPE_COMPATABILITY(Int64,Complex128,false);

SET_TYPE_COMPATABILITY(UInt64,Float32,false);
SET_TYPE_COMPATABILITY(UInt64,Float64,false);
SET_TYPE_COMPATABILITY(UInt64,Float128,false);
SET_TYPE_COMPATABILITY(UInt64,Complex32,false);
SET_TYPE_COMPATABILITY(UInt64,Complex64,false);
SET_TYPE_COMPATABILITY(UInt64,Complex128,false);

SET_TYPE_COMPATABILITY(Float32,Complex32,false);
SET_TYPE_COMPATABILITY(Float32,Complex64,false);
SET_TYPE_COMPATABILITY(Float32,Complex128,false);

SET_TYPE_COMPATABILITY(Float64,Complex32,false);
SET_TYPE_COMPATABILITY(Float64,Complex64,false);
SET_TYPE_COMPATABILITY(Float64,Complex128,false);

SET_TYPE_COMPATABILITY(Float128,Complex32,false);
SET_TYPE_COMPATABILITY(Float128,Complex64,false);
SET_TYPE_COMPATABILITY(Float128,Complex128,false);

//end of namespace
}
}


#endif /* TYPECOMPAT_HPP_ */
