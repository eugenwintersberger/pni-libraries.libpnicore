/*
 * Buffer.cpp
 *
 *  Created on: Dec 22, 2011
 *      Author: Eugen Wintersberger
 */




#include <boost/python.hpp>


#include "../src/Types.hpp"
#include "../src/BufferObject.hpp"
#include "../src/Buffer.hpp"


using namespace pni::utils;
using namespace boost::python;

#define BUFFER_CLASS(type,name) \
	size_t (Buffer<type>::*(name ## size))() const = &Buffer<type>::size;\
	class_<Buffer<type>,bases<BufferObject> >(#name)\
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

void wrap_buffer(){
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

}


