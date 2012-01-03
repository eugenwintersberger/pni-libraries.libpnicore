/*
 * RefBuffer.cpp
 *
 *  Created on: Jan 03, 2012
 *      Author: Eugen Wintersberger
 */




#include <boost/python.hpp>


#include "../src/Types.hpp"
#include "../src/BufferObject.hpp"
#include "../src/Buffer.hpp"
#include "../src/RefBuffer.hpp"


using namespace pni::utils;
using namespace boost::python;

#define BUFFER_CLASS(type,name) \
	size_t (RefBuffer<type>::*(name ## size))() const = &RefBuffer<type>::size;\
	class_<RefBuffer<type>,bases<BufferObject> >(#name)\
            .def(init<Buffer<type> >())\
            .def(init<RefBuffer<type> >())\
			.def(init<type>())\
			.add_property("size",(name ## size))\
			.add_property("element_size",&RefBuffer<type>::element_size)\
			.add_property("mem_size",&RefBuffer<type>::mem_size)\
			.def("allocate",&RefBuffer<type>::allocate)\
			.def("free",&RefBuffer<type>::free)\
			.add_property("type_id",&RefBuffer<type>::type_id)\
			.def("__getitem__",&RefBuffer<type>::get)\
			.def("__setitem__",&RefBuffer<type>::set)\
			;

void wrap_refbuffer(){
	//======================Wrapping buffer objects=============================
	BUFFER_CLASS(UInt8,UInt8RefBuffer);
	BUFFER_CLASS(Int8,Int8RefBuffer);
	BUFFER_CLASS(UInt16,UInt16RefBuffer);
	BUFFER_CLASS(Int16,Int16RefBuffer);
	BUFFER_CLASS(UInt32,UInt32RefBuffer);
	BUFFER_CLASS(Int32,Int32RefBuffer);
	BUFFER_CLASS(UInt64,UInt64RefBuffer);
	BUFFER_CLASS(Int64,Int64RefBuffer);
	BUFFER_CLASS(Float32,Float32RefBuffer);
	BUFFER_CLASS(Float64,Float64RefBuffer);
	BUFFER_CLASS(Float128,Float128RefBuffer);

}


