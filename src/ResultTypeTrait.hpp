/*
 * AdditionResultType.hpp
 *
 *  Created on: Sep 5, 2011
 *      Author: eugen
 */

#ifndef RESULTTYPETRAIT_HPP_
#define RESULTTYPETRAIT_HPP_

namespace pni{
namespace utils{


template<typename A,typename B,
	 	 typename AddResType,typename SubResType,
	 	 typename MultResType,typename DivResType>
class ResultTypeTrait{
public:
	typedef typeof AddResType AddResultType;
	typedef typeof SubResType SubResultType;
	typedef typeof MultResType MultResultType;
	typedef typeof DivResType DivResultType;
};

#define ARITHMETICS_RESULT_TYPES(TA,TB,ART,SRT,MRT,DRT)\
	template<> class ResultTypeTrait<TA,TB,ART,SRT,MRT,DRT>{ \
	public: \
	typedef ART AddResultType; \
	typedef SRT SubResultType; \
	typedef MRT MultResultType; \
	typedef DRT DivResultType;\
}; \
	\
	template<> class ResultTypeTrait<TB,TA,ART,SRT,MRT,DRT>{\
	public:\
	typedef ART AddResultType;\
	typedef SRT SubResultType;\
	typedef MRT MultResultType;\
	typedef DRT DivResultType;\
};

//define results for integer integer operations
ARITHMETICS_RESULT_TYPES(Int8,Int8,Int16,Int16,Int16,Float32);
ARITHMETICS_RESULT_TYPES(Int8,UInt8,Int16,Int16,Int16,Float32);
ARITHMETICS_RESULT_TYPES(Int8,Int16,Int32,Int32,Int32,Float32);
ARITHMETICS_RESULT_TYPES(Int8,UInt16,Int32,Int32,Int32,Float32);
ARITHMETICS_RESULT_TYPES(Int8,Int32,Int64,Int64,Int64,Float64);
ARITHMETICS_RESULT_TYPES(Int8,UInt32,Int64,Int64,Int64,Float64);
ARITHMETICS_RESULT_TYPES(Int8,Int64,Int64,Int64,Int64,Float64);
ARITHMETICS_RESULT_TYPES(Int8,UInt64,Int64,Int64,Int64,Float64);

ARITHMETICS_RESULT_TYPES(UInt8,UInt8,UInt16,Int16,UInt16,Float32);
ARITHMETICS_RESULT_TYPES(UInt8,Int16,Int32,Int32,Int32,Float32);
ARITHMETICS_RESULT_TYPES(UInt8,UInt16,UInt32,Int32,UInt32,Float32);
ARITHMETICS_RESULT_TYPES(UInt8,Int32,Int64,Int64,Int64,Float32);
ARITHMETICS_RESULT_TYPES(UInt8,UInt32,UInt64,Int64,UInt64,Float32);
ARITHMETICS_RESULT_TYPES(UInt8,Int64,Int64,Int64,Int64,Float64);
ARITHMETICS_RESULT_TYPES(UInt8,UInt64,UInt64,Int64,UInt64,Float64);

ARITHMETICS_RESULT_TYPES(Int16,Int16,Int32,Int32,Int32,Float32);
ARITHMETICS_RESULT_TYPES(Int16,UInt16,Int32,Int32,Int32,Float32);
ARITHMETICS_RESULT_TYPES(Int16,Int32,Int64,Int64,Int64,Float32);
ARITHMETICS_RESULT_TYPES(Int16,UInt32,Int64,Int64,Int64,Float32);
ARITHMETICS_RESULT_TYPES(Int16,Int64,Int64,Int64,Int64,Float64);
ARITHMETICS_RESULT_TYPES(Int16,UInt64,Int64,Int64,Int64,Float64);

ARITHMETICS_RESULT_TYPES(UInt16,UInt16,UInt32,Int32,UInt32,Float32);
ARITHMETICS_RESULT_TYPES(UInt16,Int32,Int64,Int64,Int64,Float32);
ARITHMETICS_RESULT_TYPES(UInt16,UInt32,UInt64,Int64,UInt64,Float32);
ARITHMETICS_RESULT_TYPES(UInt16,Int64,Int64,Int64,Int64,Float64);
ARITHMETICS_RESULT_TYPES(UInt16,UInt64,UInt64,Int64,UInt64,Float64);

ARITHMETICS_RESULT_TYPES(Int32,Int32,Int64,Int64,Int64,Float64);
ARITHMETICS_RESULT_TYPES(Int32,UInt32,Int64,Int64,Int64,Float64);
ARITHMETICS_RESULT_TYPES(Int32,Int64,Int64,Int64,Int64,Float64);
ARITHMETICS_RESULT_TYPES(Int32,UInt64,Int64,Int64,Int64,Float64);

ARITHMETICS_RESULT_TYPES(UInt32,UInt32,UInt64,Int64,UInt64,Float64);
ARITHMETICS_RESULT_TYPES(UInt32,Int64,Int64,Int64,Int64,Float64);
ARITHMETICS_RESULT_TYPES(UInt32,UInt64,UInt64,Int64,UInt64,Float64);

ARITHMETICS_RESULT_TYPES(Int64,Int64,Int64,Int64,Int64,Float64);
ARITHMETICS_RESULT_TYPES(Int64,UInt64,Int64,Int64,Int64,Float64);

ARITHMETICS_RESULT_TYPES(UInt64,UInt64,UInt64,Int64,UInt64,Float64);


//result types for float-float operations
ARITHMETICS_RESULT_TYPES(Float32,Float32,Float32,Float32,Float32,Float32);
ARITHMETICS_RESULT_TYPES(Float32,Float64,Float64,Float64,Float64,Float64);
ARITHMETICS_RESULT_TYPES(Float32,Float128,Float128,Float128,Float128,Float128);

ARITHMETICS_RESULT_TYPES(Float64,Float64,Float64,Float64,Float64,Float64);
ARITHMETICS_RESULT_TYPES(Float64,Float128,Float128,Float128,Float128,Float128);

ARITHMETICS_RESULT_TYPES(Float128,Float128,Float128,Float128,Float128,Float128);

//result types for float-integer operations
ARITHMETICS_RESULT_TYPES(Float32,UInt8,Float32,Float32,Float32,Float32);
ARITHMETICS_RESULT_TYPES(Float32,Int8,Float32,Float32,Float32,Float32);
ARITHMETICS_RESULT_TYPES(Float32,UInt16,Float32,Float32,Float32,Float32);
ARITHMETICS_RESULT_TYPES(Float32,Int16,Float32,Float32,Float32,Float32);
ARITHMETICS_RESULT_TYPES(Float32,UInt32,Float32,Float32,Float32,Float32);
ARITHMETICS_RESULT_TYPES(Float32,Int32,Float32,Float32,Float32,Float32);
ARITHMETICS_RESULT_TYPES(Float32,UInt64,Float64,Float64,Float64,Float64);
ARITHMETICS_RESULT_TYPES(Float32,Int64,Float64,Float64,Float64,Float64);

ARITHMETICS_RESULT_TYPES(Float64,UInt8,Float64,Float64,Float64,Float64);
ARITHMETICS_RESULT_TYPES(Float64,Int8,Float64,Float64,Float64,Float64);
ARITHMETICS_RESULT_TYPES(Float64,UInt16,Float64,Float64,Float64,Float64);
ARITHMETICS_RESULT_TYPES(Float64,Int16,Float64,Float64,Float64,Float64);
ARITHMETICS_RESULT_TYPES(Float64,UInt32,Float64,Float64,Float64,Float64);
ARITHMETICS_RESULT_TYPES(Float64,Int32,Float64,Float64,Float64,Float64);
ARITHMETICS_RESULT_TYPES(Float64,UInt64,Float64,Float64,Float64,Float64);
ARITHMETICS_RESULT_TYPES(Float64,Int64,Float64,Float64,Float64,Float64);

ARITHMETICS_RESULT_TYPES(Float128,UInt8,Float128,Float128,Float128,Float128);
ARITHMETICS_RESULT_TYPES(Float128,Int8,Float128,Float128,Float128,Float128);
ARITHMETICS_RESULT_TYPES(Float128,UInt16,Float128,Float128,Float128,Float128);
ARITHMETICS_RESULT_TYPES(Float128,Int16,Float128,Float128,Float128,Float128);
ARITHMETICS_RESULT_TYPES(Float128,UInt32,Float128,Float128,Float128,Float128);
ARITHMETICS_RESULT_TYPES(Float128,Int32,Float128,Float128,Float128,Float128);
ARITHMETICS_RESULT_TYPES(Float128,UInt64,Float128,Float128,Float128,Float128);
ARITHMETICS_RESULT_TYPES(Float128,Int64,Float128,Float128,Float128,Float128);

//result types for complex-complex operations
ARITHMETICS_RESULT_TYPES(Complex32,Complex32,Complex32,Complex32,Complex32,Complex32);
ARITHMETICS_RESULT_TYPES(Complex32,Complex64,Complex64,Complex64,Complex64,Complex64);
ARITHMETICS_RESULT_TYPES(Complex32,Complex128,Complex128,Complex128,Complex128,Complex128);

ARITHMETICS_RESULT_TYPES(Complex64,Complex64,Complex64,Complex64,Complex64,Complex64);
ARITHMETICS_RESULT_TYPES(Complex64,Complex128,Complex128,Complex128,Complex128,Complex128);

ARITHMETICS_RESULT_TYPES(Complex128,Complex128,Complex128,Complex128,Complex128,Complex128);

//result complex-float operations
ARITHMETICS_RESULT_TYPES(Complex32,Float32,Complex32,Complex32,Complex32,Complex32);
ARITHMETICS_RESULT_TYPES(Complex32,Float64,Complex64,Complex64,Complex64,Complex64);
ARITHMETICS_RESULT_TYPES(Complex32,Float128,Complex128,Complex128,Complex128,Complex128);

ARITHMETICS_RESULT_TYPES(Complex64,Float32,Complex64,Complex64,Complex64,Complex64);
ARITHMETICS_RESULT_TYPES(Complex64,Float64,Complex64,Complex64,Complex64,Complex64);
ARITHMETICS_RESULT_TYPES(Complex64,Float128,Complex128,Complex128,Complex128,Complex128);

ARITHMETICS_RESULT_TYPES(Complex128,Float32,Complex128,Complex128,Complex128,Complex128);
ARITHMETICS_RESULT_TYPES(Complex128,Float64,Complex128,Complex128,Complex128,Complex128);
ARITHMETICS_RESULT_TYPES(Complex128,Float128,Complex128,Complex128,Complex128,Complex128);

//results for complex-integer operations
ARITHMETICS_RESULT_TYPES(Complex32,Int8,Complex32,Complex32,Complex32,Complex32);
ARITHMETICS_RESULT_TYPES(Complex32,UInt8,Complex32,Complex32,Complex32,Complex32);
ARITHMETICS_RESULT_TYPES(Complex32,Int16,Complex32,Complex32,Complex32,Complex32);
ARITHMETICS_RESULT_TYPES(Complex32,UInt16,Complex32,Complex32,Complex32,Complex32);
ARITHMETICS_RESULT_TYPES(Complex32,Int32,Complex32,Complex32,Complex32,Complex32);
ARITHMETICS_RESULT_TYPES(Complex32,UInt32,Complex32,Complex32,Complex32,Complex32);
ARITHMETICS_RESULT_TYPES(Complex32,Int64,Complex64,Complex64,Complex64,Complex64);
ARITHMETICS_RESULT_TYPES(Complex32,UInt64,Complex64,Complex64,Complex64,Complex64);

ARITHMETICS_RESULT_TYPES(Complex64,Int8,Complex64,Complex64,Complex64,Complex64);
ARITHMETICS_RESULT_TYPES(Complex64,UInt8,Complex64,Complex64,Complex64,Complex64);
ARITHMETICS_RESULT_TYPES(Complex64,Int16,Complex64,Complex64,Complex64,Complex64);
ARITHMETICS_RESULT_TYPES(Complex64,UInt16,Complex64,Complex64,Complex64,Complex64);
ARITHMETICS_RESULT_TYPES(Complex64,Int32,Complex64,Complex64,Complex64,Complex64);
ARITHMETICS_RESULT_TYPES(Complex64,UInt32,Complex64,Complex64,Complex64,Complex64);
ARITHMETICS_RESULT_TYPES(Complex64,Int64,Complex64,Complex64,Complex64,Complex64);
ARITHMETICS_RESULT_TYPES(Complex64,UInt64,Complex64,Complex64,Complex64,Complex64);

ARITHMETICS_RESULT_TYPES(Complex128,Int8,Complex128,Complex128,Complex128,Complex128);
ARITHMETICS_RESULT_TYPES(Complex128,UInt8,Complex128,Complex128,Complex128,Complex128);
ARITHMETICS_RESULT_TYPES(Complex128,Int16,Complex128,Complex128,Complex128,Complex128);
ARITHMETICS_RESULT_TYPES(Complex128,UInt16,Complex128,Complex128,Complex128,Complex128);
ARITHMETICS_RESULT_TYPES(Complex128,Int32,Complex128,Complex128,Complex128,Complex128);
ARITHMETICS_RESULT_TYPES(Complex128,UInt32,Complex128,Complex128,Complex128,Complex128);
ARITHMETICS_RESULT_TYPES(Complex128,Int64,Complex128,Complex128,Complex128,Complex128);
ARITHMETICS_RESULT_TYPES(Complex128,UInt64,Complex128,Complex128,Complex128,Complex128);

//end of namespace
}
}



#endif /* ADDITIONRESULTTYPE_HPP_ */
