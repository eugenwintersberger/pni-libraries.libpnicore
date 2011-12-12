/*
 * DataObject.cpp
 *
 *  Created on: Oct 4, 2011
 *      Author: eugen
 */

#include <boost/python.hpp>
#import <iostream>


#include "../src/DataObject.hpp"
#include "../src/NumericObject.hpp"
#include "../src/ArrayObject.hpp"
#include "../src/Types.hpp"
#include "../src/ArrayShape.hpp"
#include "../src/Buffer.hpp"
#include "../src/Index.hpp"
#include "../src/Scalar.hpp"

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
			.def(str(self))
			;

	//====================Wrapping ArrayShape===================================
	size_t (ArrayShape::*shape_get_rank)() const = &ArrayShape::rank;
	void   (ArrayShape::*shape_set_rank)(const size_t &) = &ArrayShape::rank;
	size_t (ArrayShape::*shape_get_dimension)(const size_t &) const = &ArrayShape::dim;
	void   (ArrayShape::*shape_set_dimension)(const size_t &,const size_t &) = &ArrayShape::dim;
	class_<ArrayShape>("Shape")
			.def(init<ArrayShape>())
			.def(init<UInt64>())
			.add_property("rank",shape_get_rank,shape_set_rank)
			.def("setDimension",shape_set_dimension)
			.def("getDimension",shape_get_dimension)
			.def("size",&ArrayShape::size)
			.def("offset",&ArrayShape::offset)
			.def("index",&ArrayShape::index)
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
	void (Scalar<Float32>::*Float32_set_value)(const Scalar<Float32> &) = &Scalar<Float32>::value;
	void (Scalar<Float32>::*Float32_set_value_pod)(const Float32 &) = &Scalar<Float32>::value;
	Float32 (Scalar<Float32>::*Float32_get_value)() const = &Scalar<Float32>::value;
	class_<Scalar<Float32>,bases<ScalarObject> >("Float32Scalar")
			.def(init<Float32Scalar>())
			.def(init<Float32,String,String,String>())
			.def(init<String,String,String>())
			.def("value",Float32_set_value)
			.def("value",Float32_get_value)
			.def("value",Float32_set_value_pod)
			;


}




