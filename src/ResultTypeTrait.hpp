/*
 * Declaration of the template class ResultTypeTrait
 *
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniutils.
 *
 * libpniutils is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniutils is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * ResultTypeTrait determines the data type of the result of an arithmetic
 * operation depending on the types of the operands.
 *
 * Created on: Sep 5, 2011
 *     Author: Eugen Wintersberger
 *
 */


#ifndef RESULTTYPETRAIT_HPP_
#define RESULTTYPETRAIT_HPP_

namespace pni{
namespace utils{

//! \ingroup type_classes
//! \brief arithmetic result type trait

//! Template representing an arithmetic result type trait. Basically the
//! result type of an arithmetic operation is determined from its argument
//! argument types.
template<typename A,typename B>
class ResultTypeTrait{
public:
};

//! \ingroup type_classes
//! \brief single type trait macro

//! This macro is used to specialize a result type trait for the case that
//! the two arguments of the arithmetic operation are of equal type.
#define ARITHMETICS_RESULT_TYPES_SINGLE(TA,ART,SRT,MRT,DRT)\
	template<> class ResultTypeTrait<TA,TA>{\
	public:\
	typedef ART AddResultType;\
	typedef SRT SubResultType;\
	typedef MRT MultResultType;\
	typedef DRT DivResultType;\
};

//! \ingroup type_classes
//! \brief multiple type trait macro

//! This macro can be used to specialize a result type trait for arithmetic
//! operations where the operands are of different type.
#define ARITHMETICS_RESULT_TYPES(TA,TB,ART,SRT,MRT,DRT)\
	template<> class ResultTypeTrait<TA,TB>{ \
	public: \
	typedef ART AddResultType; \
	typedef SRT SubResultType; \
	typedef MRT MultResultType; \
	typedef DRT DivResultType;\
}; \
	\
	template<> class ResultTypeTrait<TB,TA>{\
	public:\
	typedef ART AddResultType;\
	typedef SRT SubResultType;\
	typedef MRT MultResultType;\
	typedef DRT DivResultType;\
};

//! \cond no_doc
//define results for integer integer operations
ARITHMETICS_RESULT_TYPES_SINGLE(Int8,Int16,Int16,Int16,Float32);
ARITHMETICS_RESULT_TYPES(Int8,UInt8,Int16,Int16,Int16,Float32);
ARITHMETICS_RESULT_TYPES(Int8,Int16,Int32,Int32,Int32,Float32);
ARITHMETICS_RESULT_TYPES(Int8,UInt16,Int32,Int32,Int32,Float32);
ARITHMETICS_RESULT_TYPES(Int8,Int32,Int64,Int64,Int64,Float64);
ARITHMETICS_RESULT_TYPES(Int8,UInt32,Int64,Int64,Int64,Float64);
ARITHMETICS_RESULT_TYPES(Int8,Int64,Int64,Int64,Int64,Float64);
ARITHMETICS_RESULT_TYPES(Int8,UInt64,Int64,Int64,Int64,Float64);

ARITHMETICS_RESULT_TYPES_SINGLE(UInt8,UInt16,Int16,UInt16,Float32);
ARITHMETICS_RESULT_TYPES(UInt8,Int16,Int32,Int32,Int32,Float32);
ARITHMETICS_RESULT_TYPES(UInt8,UInt16,UInt32,Int32,UInt32,Float32);
ARITHMETICS_RESULT_TYPES(UInt8,Int32,Int64,Int64,Int64,Float32);
ARITHMETICS_RESULT_TYPES(UInt8,UInt32,UInt64,Int64,UInt64,Float32);
ARITHMETICS_RESULT_TYPES(UInt8,Int64,Int64,Int64,Int64,Float64);
ARITHMETICS_RESULT_TYPES(UInt8,UInt64,UInt64,Int64,UInt64,Float64);

ARITHMETICS_RESULT_TYPES_SINGLE(Int16,Int32,Int32,Int32,Float32);
ARITHMETICS_RESULT_TYPES(Int16,UInt16,Int32,Int32,Int32,Float32);
ARITHMETICS_RESULT_TYPES(Int16,Int32,Int64,Int64,Int64,Float32);
ARITHMETICS_RESULT_TYPES(Int16,UInt32,Int64,Int64,Int64,Float32);
ARITHMETICS_RESULT_TYPES(Int16,Int64,Int64,Int64,Int64,Float64);
ARITHMETICS_RESULT_TYPES(Int16,UInt64,Int64,Int64,Int64,Float64);

ARITHMETICS_RESULT_TYPES_SINGLE(UInt16,UInt32,Int32,UInt32,Float32);
ARITHMETICS_RESULT_TYPES(UInt16,Int32,Int64,Int64,Int64,Float32);
ARITHMETICS_RESULT_TYPES(UInt16,UInt32,UInt64,Int64,UInt64,Float32);
ARITHMETICS_RESULT_TYPES(UInt16,Int64,Int64,Int64,Int64,Float64);
ARITHMETICS_RESULT_TYPES(UInt16,UInt64,UInt64,Int64,UInt64,Float64);

ARITHMETICS_RESULT_TYPES_SINGLE(Int32,Int64,Int64,Int64,Float64);
ARITHMETICS_RESULT_TYPES(Int32,UInt32,Int64,Int64,Int64,Float64);
ARITHMETICS_RESULT_TYPES(Int32,Int64,Int64,Int64,Int64,Float64);
ARITHMETICS_RESULT_TYPES(Int32,UInt64,Int64,Int64,Int64,Float64);

ARITHMETICS_RESULT_TYPES_SINGLE(UInt32,UInt64,Int64,UInt64,Float64);
ARITHMETICS_RESULT_TYPES(UInt32,Int64,Int64,Int64,Int64,Float64);
ARITHMETICS_RESULT_TYPES(UInt32,UInt64,UInt64,Int64,UInt64,Float64);

ARITHMETICS_RESULT_TYPES_SINGLE(Int64,Int64,Int64,Int64,Float64);
ARITHMETICS_RESULT_TYPES(Int64,UInt64,Int64,Int64,Int64,Float64);

ARITHMETICS_RESULT_TYPES_SINGLE(UInt64,UInt64,Int64,UInt64,Float64);


//result types for float-float operations
ARITHMETICS_RESULT_TYPES_SINGLE(Float32,Float32,Float32,Float32,Float32);
ARITHMETICS_RESULT_TYPES(Float32,Float64,Float64,Float64,Float64,Float64);
ARITHMETICS_RESULT_TYPES(Float32,Float128,Float128,Float128,Float128,Float128);

ARITHMETICS_RESULT_TYPES_SINGLE(Float64,Float64,Float64,Float64,Float64);
ARITHMETICS_RESULT_TYPES(Float64,Float128,Float128,Float128,Float128,Float128);

ARITHMETICS_RESULT_TYPES_SINGLE(Float128,Float128,Float128,Float128,Float128);

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
ARITHMETICS_RESULT_TYPES_SINGLE(Complex32,Complex32,Complex32,Complex32,Complex32);
ARITHMETICS_RESULT_TYPES(Complex32,Complex64,Complex64,Complex64,Complex64,Complex64);
ARITHMETICS_RESULT_TYPES(Complex32,Complex128,Complex128,Complex128,Complex128,Complex128);

ARITHMETICS_RESULT_TYPES_SINGLE(Complex64,Complex64,Complex64,Complex64,Complex64);
ARITHMETICS_RESULT_TYPES(Complex64,Complex128,Complex128,Complex128,Complex128,Complex128);

ARITHMETICS_RESULT_TYPES_SINGLE(Complex128,Complex128,Complex128,Complex128,Complex128);

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

//! \endcond

//end of namespace
}
}



#endif /* ADDITIONRESULTTYPE_HPP_ */
