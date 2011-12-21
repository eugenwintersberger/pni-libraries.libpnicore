/*
 * DataObject.cpp
 *
 *  Created on: Oct 4, 2011
 *      Author: Eugen Wintersberger
 */

extern "C"{
    #include<Python.h>
}

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
#include "../src/Array.hpp"
#include "../src/Exceptions.hpp"

using namespace pni::utils;
using namespace boost::python;

#define BUFFER_CLASS(type,name) \
	size_t (Buffer<type>::*(name ## size))() const = &Buffer<type>::size;\
	class_<Buffer<type> >(#name)\
			.def(init<Buffer<type> >())\
			.def(init<type>())\
			.add_property("size",(name ## size))\
			.add_property("element_size",&Buffer<type>::element_size)\
			.add_property("mem_size",&Buffer<type>::mem_size)\
			.def("allocate",&Buffer<type>::allocate)\
			.def("free",&Buffer<type>::free)\
			.add_property("type_id",&Buffer<type>::type_id)\
			.def("__getitem__",&Buffer<type>::get)\
			.def("__setitem__",&Buffer<type>::set)\
			;

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
				.add_property("type_id",&Scalar<type>::type_id)\
				.def(self == self)\
				EQUALITY_TOTAL(Scalar)\
				.def(self != self)\
				INEQUALITY_TOTAL(Scalar)\
				.def(self + self)\
				BINARY_ADD_TOTAL(Scalar)\
				.def(self - self)\
				BINARY_SUB_TOTAL(Scalar)\
				.def(self / self)\
				BINARY_DIV_TOTAL(Scalar)\
				.def(self * self)\
				BINARY_MULT_TOTAL(Scalar)\
				;


//=====================translate exceptions=====================================
void index_error_translator(IndexError const &error){
    PyErr_SetString(PyExc_UserWarning,"Index Error");
}

BOOST_PYTHON_MODULE(pniutils)
{
    //==================Wrap exceptions=========================================
    const String& (Exception::*Exception_get_name)() const = &Exception::name;
    void (Exception::*Exception_set_name)(const String &) = &Exception::name;
    const String& (Exception::*Exception_get_issuer)() const = &Exception::issuer;
    void (Exception::*Exception_set_issuer)(const String &) = &Exception::issuer;
    const String& (Exception::*Exception_get_description)() const =
        &Exception::description;
    void (Exception::*Exception_set_description)(const String &) =
        &Exception::description;
    class_<Exception>("Exception")
        .def(init<>())
        .def(init<String,String,String>())
        .add_property("name",
                make_function(Exception_get_name,return_internal_reference<1>()),
                Exception_set_name)
        .add_property("issuer",
                make_function(Exception_get_issuer,return_internal_reference<1>()),
                Exception_set_issuer)
        .add_property("description",
                make_function(Exception_get_description,return_internal_reference<1>()),
                Exception_set_description)
        ;

    class_<IndexError,bases<Exception> >("IndexError")
        .def(init<>())
        .def(init<String,String>())
        ;

    //===================register exception translators=========================
    register_exception_translator<IndexError>(index_error_translator);
	//===============Wrap TypeID enum class=====================================
	enum_<TypeID>("TypeID")
			.value("NONE",TypeID::NONE)
			.value("UINT8",TypeID::UINT8)
			.value("INT8",TypeID::INT8)
			.value("UINT16",TypeID::UINT16)
			.value("INT16",TypeID::INT16)
			.value("UINT32",TypeID::UINT32)
			.value("INT32",TypeID::INT32)
			.value("UINT64",TypeID::UINT64)
			.value("INT64",TypeID::INT64)
			.value("FLOAT32",TypeID::FLOAT32)
			.value("FLOAT64",TypeID::FLOAT64)
			.value("FLOAT128",TypeID::FLOAT128)
			.value("COMPLEX32",TypeID::COMPLEX32)
			.value("COMPLEX64",TypeID::COMPLEX64)
			.value("COMPLEX128",TypeID::COMPLEX128)
			.value("STRING",TypeID::STRING)
			.value("BINARY",TypeID::BINARY)
			.value("BOOLEAN",TypeID::BOOLEAN)
			;

	//==================Wrap TypeClass enum class===============================
	enum_<TypeClass>("TypeClass")
			.value("NONE",TypeClass::NONE)
			.value("INTEGER",TypeClass::INTEGER)
			.value("FLOAT",TypeClass::FLOAT)
			.value("BINARY",TypeClass::BINARY)
			.value("BOOL",TypeClass::BOOL)
			.value("COMPLEX",TypeClass::COMPLEX)
			;


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
			.def("type_id",&NumericObject::type_id)
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
			.def("dim",shape_set_dimension)
			.def("dim",shape_get_dimension)
			.def("size",&Shape::size)
			.def("offset",&Shape::offset)
			.def("index",&Shape::index)
            .def("__getitem__",shape_get_dimension)
            .def("__len__",shape_get_rank)
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

	//================Wrapping the Array template===============================
	void (Array<Float64>::*set_buffer)(const BufferObject &) = &Array<Float64>::buffer;
	const BufferObject &(Array<Float64>::*get_buffer)() const = &Array<Float64>::buffer;
	void (Array<Float64>::*set_shape)(const Shape &) = &Array<Float64>::shape;
	const Shape &(Array<Float64>::*get_shape)() const = &Array<Float64>::shape;
	class_<Array<Float64> >("Float64Array")
			.def(init<>())
			.def(init<Array<Float64> >())
			.def(init<Shape>())
			.def(init<Shape,Buffer<Float64> >())
			.def(init<Shape,Buffer<Float64>,String,String,String>())
			.def(init<Shape,String,String,String>())

			.add_property("buffer",make_function(get_buffer,return_internal_reference<1>()),
					set_buffer)
			.add_property("shape",make_function(get_shape,return_internal_reference<1>()),set_shape)

            .def("allocate",&Array<Float64>::allocate)
            ;

}




