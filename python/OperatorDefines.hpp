/*
 * OperatorDefines.hpp
 *
 *  Created on: Dec 22, 2011
 *      Author: Eugen Wintersberger
 */

#ifndef __OPERATORDEFINES_HPP__
#define __OPERATORDEFINES_HPP__

//===================Macros for various operators===============================
#define EQUALITY_OPERATOR(other_type,other_template)\
		.def(self == other<other_template<other_type> >())\
		.def(other<other_template<other_type> >() == self)\
		.def(other_type() == self)\
		.def(self == other_type())

//------------------------------------------------------------------------------
#define INEQUALITY_OPERATOR(other_type,other_template)\
		.def(self != other<other_template<other_type> >())\
		.def(other<other_template<other_type> >() != self)\
		.def(other_type() != self)\
		.def(self != other_type())

//------------------------------------------------------------------------------
#define BINARY_ADD_OPERATOR(other_type,other_template)\
		.def(self + other<other_template<other_type> >())\
		.def(other<other_template<other_type> >() + self)\
		.def(other_type() + self)\
		.def(self + other_type())

//------------------------------------------------------------------------------
#define BINARY_SUB_OPERATOR(other_type,other_template)\
		.def(self - other<other_template<other_type> >())\
		.def(other<other_template<other_type> >() - self)\
		.def(other_type() - self)\
		.def(self - other_type())

//------------------------------------------------------------------------------
#define BINARY_DIV_OPERATOR(other_type,other_template)\
		.def(self / other<other_template<other_type> >())\
		.def(other<other_template<other_type> >() / self)\
		.def(other_type() / self)\
		.def(self / other_type())

//------------------------------------------------------------------------------
#define BINARY_MULT_OPERATOR(other_type,other_template)\
		.def(self * other<other_template<other_type> >())\
		.def(other<other_template<other_type> >() * self)\
		.def(other_type() * self)\
		.def(self * other_type())

//------------------------------------------------------------------------------
#define EQUALITY_TOTAL(other_template)\
		EQUALITY_OPERATOR(UInt8,other_template)\
		EQUALITY_OPERATOR(Int8,other_template)\
		EQUALITY_OPERATOR(UInt16,other_template)\
		EQUALITY_OPERATOR(Int16,other_template)\
		EQUALITY_OPERATOR(UInt32,other_template)\
		EQUALITY_OPERATOR(Int32,other_template)\
		EQUALITY_OPERATOR(UInt64,other_template)\
		EQUALITY_OPERATOR(Int64,other_template)\
		EQUALITY_OPERATOR(Float32,other_template)\
		EQUALITY_OPERATOR(Float64,other_template)\
		EQUALITY_OPERATOR(Float128,other_template)

//------------------------------------------------------------------------------
#define INEQUALITY_TOTAL(other_template)\
		INEQUALITY_OPERATOR(UInt8,other_template)\
		INEQUALITY_OPERATOR(Int8,other_template)\
		INEQUALITY_OPERATOR(UInt16,other_template)\
		INEQUALITY_OPERATOR(Int16,other_template)\
		INEQUALITY_OPERATOR(UInt32,other_template)\
		INEQUALITY_OPERATOR(Int32,other_template)\
		INEQUALITY_OPERATOR(UInt64,other_template)\
		INEQUALITY_OPERATOR(Int64,other_template)\
		INEQUALITY_OPERATOR(Float32,other_template)\
		INEQUALITY_OPERATOR(Float64,other_template)\
		INEQUALITY_OPERATOR(Float128,other_template)

//------------------------------------------------------------------------------
#define BINARY_ADD_TOTAL(other_template)\
		BINARY_ADD_OPERATOR(UInt8,other_template)\
		BINARY_ADD_OPERATOR(Int8,other_template)\
		BINARY_ADD_OPERATOR(UInt16,other_template)\
		BINARY_ADD_OPERATOR(Int16,other_template)\
		BINARY_ADD_OPERATOR(UInt32,other_template)\
		BINARY_ADD_OPERATOR(Int32,other_template)\
		BINARY_ADD_OPERATOR(UInt64,other_template)\
		BINARY_ADD_OPERATOR(Int64,other_template)\
		BINARY_ADD_OPERATOR(Float32,other_template)\
		BINARY_ADD_OPERATOR(Float64,other_template)\
		BINARY_ADD_OPERATOR(Float128,other_template)

//------------------------------------------------------------------------------
#define BINARY_SUB_TOTAL(other_template)\
		BINARY_SUB_OPERATOR(UInt8,other_template)\
		BINARY_SUB_OPERATOR(Int8,other_template)\
		BINARY_SUB_OPERATOR(UInt16,other_template)\
		BINARY_SUB_OPERATOR(Int16,other_template)\
		BINARY_SUB_OPERATOR(UInt32,other_template)\
		BINARY_SUB_OPERATOR(Int32,other_template)\
		BINARY_SUB_OPERATOR(UInt64,other_template)\
		BINARY_SUB_OPERATOR(Int64,other_template)\
		BINARY_SUB_OPERATOR(Float32,other_template)\
		BINARY_SUB_OPERATOR(Float64,other_template)\
		BINARY_SUB_OPERATOR(Float128,other_template)

//------------------------------------------------------------------------------
#define BINARY_MULT_TOTAL(other_template)\
		BINARY_MULT_OPERATOR(UInt8,other_template)\
		BINARY_MULT_OPERATOR(Int8,other_template)\
		BINARY_MULT_OPERATOR(UInt16,other_template)\
		BINARY_MULT_OPERATOR(Int16,other_template)\
		BINARY_MULT_OPERATOR(UInt32,other_template)\
		BINARY_MULT_OPERATOR(Int32,other_template)\
		BINARY_MULT_OPERATOR(UInt64,other_template)\
		BINARY_MULT_OPERATOR(Int64,other_template)\
		BINARY_MULT_OPERATOR(Float32,other_template)\
		BINARY_MULT_OPERATOR(Float64,other_template)\
		BINARY_MULT_OPERATOR(Float128,other_template)

//------------------------------------------------------------------------------
#define BINARY_DIV_TOTAL(other_template)\
		BINARY_DIV_OPERATOR(UInt8,other_template)\
		BINARY_DIV_OPERATOR(Int8,other_template)\
		BINARY_DIV_OPERATOR(UInt16,other_template)\
		BINARY_DIV_OPERATOR(Int16,other_template)\
		BINARY_DIV_OPERATOR(UInt32,other_template)\
		BINARY_DIV_OPERATOR(Int32,other_template)\
		BINARY_DIV_OPERATOR(UInt64,other_template)\
		BINARY_DIV_OPERATOR(Int64,other_template)\
		BINARY_DIV_OPERATOR(Float32,other_template)\
		BINARY_DIV_OPERATOR(Float64,other_template)\
		BINARY_DIV_OPERATOR(Float128,other_template)

#endif
