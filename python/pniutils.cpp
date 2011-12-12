/*
 * DataObject.cpp
 *
 *  Created on: Oct 4, 2011
 *      Author: eugen
 */

#include <boost/python.hpp>
#include <iostream>


#include "../src/DataObject.hpp"
#include "../src/NumericObject.hpp"
#include "../src/ArrayObject.hpp"
#include "../src/Types.hpp"
#include "../src/Shape.hpp"
#include "../src/Buffer.hpp"
#include "../src/Index.hpp"
#include "../src/Scalar.hpp"
#include "../src/ArrayObject.hpp"

using namespace pni::utils;
using namespace boost::python;

#define BUFFER_CLASS(type,name) \
	size_t (Buffer<type>::*(name ## size))() const = &Buffer<type>::size;\
	class_<Buffer<type> >(#name)\
			.def(init<Buffer<type> >())\
			.def(init<type>())\
			.add_property("size",(name ## size))\
			.add_property("element_size",&Buffer<type>::element_size)\
			.add_property("memory_size",&Buffer<type>::mem_size)\
			.def("allocate",&Buffer<type>::allocate)\
			.def("free",&Buffer<type>::free)\
			;

//===================Macros for various operators===============================
#define EQUALITY_OPERATOR(other_type)\
		.def(self == other<other_type>())\
		.def(other<other_type>() == self)\
		.def(other_type() == self)\
		.def(self == other_type())

//------------------------------------------------------------------------------
#define INEQUALITY_OPERATOR(other_type)\
		.def(self != other<other_type>())\
		.def(other<other_type>() != self)\
		.def(other_type() != self)\
		.def(self != other_type())

//------------------------------------------------------------------------------
#define BINARY_ADD_OPERATOR(other_type)\
		.def(self + other<other_type>())\
		.def(other<other_type>() + self)\
		.def(other_type() + self)\
		.def(self + other_type())

//------------------------------------------------------------------------------
#define BINARY_SUB_OPERATOR(other_type)\
		.def(self - other<other_type>())\
		.def(other<other_type>() - self)\
		.def(other_type() - self)\
		.def(self - other_type())

//------------------------------------------------------------------------------
#define BINARY_DIV_OPERATOR(other_type)\
		.def(self / other<other_type>())\
		.def(other<other_type>() / self)\
		.def(other_type() / self)\
		.def(self / other_type())

//------------------------------------------------------------------------------
#define BINARY_MULT_OPERATOR(other_type)\
		.def(self * other<other_type>())\
		.def(other<other_type>() * self)\
		.def(other_type() * self)\
		.def(self * other_type())

//------------------------------------------------------------------------------
#define EQUALITY_TOTAL()\
		EQUALITY_OPERATOR(UInt8)\
		EQUALITY_OPERATOR(Int8)\
		EQUALITY_OPERATOR(UInt16)\
		EQUALITY_OPERATOR(Int16)\
		EQUALITY_OPERATOR(UInt32)\
		EQUALITY_OPERATOR(Int32)\
		EQUALITY_OPERATOR(UInt64)\
		EQUALITY_OPERATOR(Int64)\
		EQUALITY_OPERATOR(Float32)\
		EQUALITY_OPERATOR(Float64)\
		EQUALITY_OPERATOR(Float128)

//------------------------------------------------------------------------------
#define INEQUALITY_TOTAL()\
		INEQUALITY_OPERATOR(UInt8)\
		INEQUALITY_OPERATOR(Int8)\
		INEQUALITY_OPERATOR(UInt16)\
		INEQUALITY_OPERATOR(Int16)\
		INEQUALITY_OPERATOR(UInt32)\
		INEQUALITY_OPERATOR(Int32)\
		INEQUALITY_OPERATOR(UInt64)\
		INEQUALITY_OPERATOR(Int64)\
		INEQUALITY_OPERATOR(Float32)\
		INEQUALITY_OPERATOR(Float64)\
		INEQUALITY_OPERATOR(Float128)

//------------------------------------------------------------------------------
#define BINARY_ADD_TOTAL()\
		BINARY_ADD_OPERATOR(UInt8)\
		BINARY_ADD_OPERATOR(Int8)\
		BINARY_ADD_OPERATOR(UInt16)\
		BINARY_ADD_OPERATOR(Int16)\
		BINARY_ADD_OPERATOR(UInt32)\
		BINARY_ADD_OPERATOR(Int32)\
		BINARY_ADD_OPERATOR(UInt64)\
		BINARY_ADD_OPERATOR(Int64)\
		BINARY_ADD_OPERATOR(Float32)\
		BINARY_ADD_OPERATOR(Float64)\
		BINARY_ADD_OPERATOR(Float128)

//------------------------------------------------------------------------------
#define BINARY_SUB_TOTAL()\
		BINARY_SUB_OPERATOR(UInt8)\
		BINARY_SUB_OPERATOR(Int8)\
		BINARY_SUB_OPERATOR(UInt16)\
		BINARY_SUB_OPERATOR(Int16)\
		BINARY_SUB_OPERATOR(UInt32)\
		BINARY_SUB_OPERATOR(Int32)\
		BINARY_SUB_OPERATOR(UInt64)\
		BINARY_SUB_OPERATOR(Int64)\
		BINARY_SUB_OPERATOR(Float32)\
		BINARY_SUB_OPERATOR(Float64)\
		BINARY_SUB_OPERATOR(Float128)

//------------------------------------------------------------------------------
#define BINARY_MULT_TOTAL()\
		BINARY_MULT_OPERATOR(UInt8)\
		BINARY_MULT_OPERATOR(Int8)\
		BINARY_MULT_OPERATOR(UInt16)\
		BINARY_MULT_OPERATOR(Int16)\
		BINARY_MULT_OPERATOR(UInt32)\
		BINARY_MULT_OPERATOR(Int32)\
		BINARY_MULT_OPERATOR(UInt64)\
		BINARY_MULT_OPERATOR(Int64)\
		BINARY_MULT_OPERATOR(Float32)\
		BINARY_MULT_OPERATOR(Float64)\
		BINARY_MULT_OPERATOR(Float128)

//------------------------------------------------------------------------------
#define BINARY_DIV_TOTAL()\
		BINARY_DIV_OPERATOR(UInt8)\
		BINARY_DIV_OPERATOR(Int8)\
		BINARY_DIV_OPERATOR(UInt16)\
		BINARY_DIV_OPERATOR(Int16)\
		BINARY_DIV_OPERATOR(UInt32)\
		BINARY_DIV_OPERATOR(Int32)\
		BINARY_DIV_OPERATOR(UInt64)\
		BINARY_DIV_OPERATOR(Int64)\
		BINARY_DIV_OPERATOR(Float32)\
		BINARY_DIV_OPERATOR(Float64)\
		BINARY_DIV_OPERATOR(Float128)

//=================Macro for instantiating a scalar object----------------------
#define SCALAR_TEMPLATE(type,name) \
		void (Scalar<type>::*(name ## _set_value))(const Scalar<type> &) = &Scalar<type>::value;\
		void (Scalar<type>::*(name ## _set_value_pod))(const type &) = &Scalar<type>::value;\
		type (Scalar<type>::*(name ## _get_value))() const = &Scalar<type>::value;\
		class_<Scalar<type>,bases<ScalarObject> >(#name)\
				.def(init<Scalar<type> >())\
				.def(init<type,String,String,String>())\
				.def(init<String,String,String>())\
				.def("value",(name ## _set_value))\
				.def("value",(name ## _get_value))\
				.def("value",(name ## _set_value_pod))\
				.def(self == self)\
				EQUALITY_TOTAL()\
				.def(self != self)\
				INEQUALITY_TOTAL()\
				.def(self + self)\
				BINARY_ADD_TOTAL()\
				.def(self - self)\
				BINARY_SUB_TOTAL()\
				.def(self / self)\
				BINARY_DIV_TOTAL()\
				.def(self * self)\
				BINARY_MULT_TOTAL()\
				;


BOOST_PYTHON_MODULE(pniutils)
{

	//===================Wrapping DataObject====================================
	String (DataObject::*get_name)() const = &DataObject::name;
	void   (DataObject::*set_name)(const String &) = &DataObject::name;
	String (DataObject::*get_description)() const = &DataObject::description;
	void   (DataObject::*set_description)(const String &) = &DataObject::description;
	class_<DataObject>("DataObject")
			.def(init<String>())
			.def(init<String,String>())
			.def(init<DataObject>())
			.add_property("name", get_name,set_name)
			.add_property("description",get_description,set_description)
			;

	//===================Wrapping NumericObject=================================
	String (NumericObject::*get_unit)() const = &NumericObject::unit;
	void   (NumericObject::*set_unit)(const String &) = &NumericObject::unit;
	class_<NumericObject,bases<DataObject> >("NumericObject")
			.def(init<String,String>())
			.def(init<String,String,String>())
			.def(init<NumericObject>())
			.add_property("unit",get_unit,set_unit)
			;

	//========================Wrapping Index====================================
	size_t (Index::*index_get_rank)() const = &Index::rank;
	void   (Index::*index_set_rank)(size_t) = &Index::rank;
	class_<Index>("Index")
			.def(init<UInt64>())
			.def(init<Index>())
			.add_property("rank",index_get_rank,index_set_rank)
			.def("getIndex",&Index::get)
			.def("setIndex",&Index::set)
			.def("increment",&Index::inc)
			.def("decrement",&Index::dec)
			.def(self == self)
			.def(self != self)
			;

	//====================Wrapping ArrayShape===================================
	size_t (Shape::*shape_get_rank)() const = &Shape::rank;
	void   (Shape::*shape_set_rank)(const size_t &) = &Shape::rank;
	size_t (Shape::*shape_get_dimension)(const size_t &) const = &Shape::dim;
	void   (Shape::*shape_set_dimension)(const size_t &,const size_t &) = &Shape::dim;
	class_<Shape>("Shape")
			.def(init<Shape>())
			.def(init<UInt64>())
			.add_property("rank",shape_get_rank,shape_set_rank)
			.def("setDimension",shape_set_dimension)
			.def("getDimension",shape_get_dimension)
			.def("size",&Shape::size)
			.def("offset",&Shape::offset)
			.def("index",&Shape::index)
			.def(self == self)
			.def(self != self)
			//need some operators
			;

	//======================Wrapping buffer objects=============================
	BUFFER_CLASS(UInt8,UInt8Buffer);
	BUFFER_CLASS(Int8,Int8Buffer);
	BUFFER_CLASS(UInt16,UInt16Buffer);
	BUFFER_CLASS(Int16,Int16Buffer);
	BUFFER_CLASS(UInt32,UInt32Buffer);
	BUFFER_CLASS(Int32,Int32Buffer);
	BUFFER_CLASS(UInt64,UInt64Buffer);
	BUFFER_CLASS(Int64,Int64Buffer);
	BUFFER_CLASS(Float32,Float32Buffer);
	BUFFER_CLASS(Float64,Float64Buffer);
	BUFFER_CLASS(Float128,Float128Buffer);

	//==========================Wrapping ScalarObject===========================
	class_<ScalarObject,bases<NumericObject> >("ScalarObject")
			.def(init<ScalarObject>())
			.def(init<>())
			.def(init<String,String>())
			.def(init<String,String,String>())
			;

	//==================Wrapping scalar templates===============================
	SCALAR_TEMPLATE(UInt8,UInt8Scalar);
	SCALAR_TEMPLATE(Int8,Int8Scalar);
	SCALAR_TEMPLATE(UInt16,UInt16Scalar);
	SCALAR_TEMPLATE(Int16,Int16Scalar);
	SCALAR_TEMPLATE(UInt32,UInt32Scalar);
	SCALAR_TEMPLATE(Int32,Int32Scalar);
	SCALAR_TEMPLATE(UInt64,UInt64Scalar);
	SCALAR_TEMPLATE(Int64,Int64Scalar);
	SCALAR_TEMPLATE(Float32,Float32Scalar);
	SCALAR_TEMPLATE(Float64,Float64Scalar);
	SCALAR_TEMPLATE(Float128,Float128Scalar);

	//================Wrapping ArrayObject =====================================

}




