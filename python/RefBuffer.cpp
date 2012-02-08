/*
 * RefBuffer.cpp
 *
 *  Created on: Jan 03, 2012
 *      Author: Eugen Wintersberger
 */




#include <boost/python.hpp>

extern "C"{
#include <numpy/ndarrayobject.h>
#include <numpy/ndarraytypes.h>
}

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
			.add_property("size",(name ## size))\
			.add_property("element_size",&RefBuffer<type>::element_size)\
			.add_property("mem_size",&RefBuffer<type>::mem_size)\
			.def("allocate",&RefBuffer<type>::allocate)\
			.def("free",&RefBuffer<type>::free)\
			.add_property("type_id",&RefBuffer<type>::type_id)\
			.def("__getitem__",&RefBuffer<type>::get)\
			.def("__setitem__",&RefBuffer<type>::set)\
			;

template<typename T> RefBuffer<T> create_buffer_from_numpy_array(object a)
{
    if(a.is_none()){
        std::cerr<<"Object not initialized!"<<std::endl;
        //most probably one should throw an exception here. 
    }
    //need to obtain the python object from object
    PyObject *obj = a.ptr();

    PyArrayObject *array = (PyArrayObject*)obj;
    size_t size=1;
    for(ssize_t i=0;i<array->nd;i++){
        size *= array->dimensions[i];
    }

    T *ptr = nullptr;
    ptr = (T *)PyArray_DATA(obj);

    return RefBuffer<T>(size,ptr);
}

#define REFBUFFER_GENERATOR(name,type) \
    def(name,create_buffer_from_numpy_array<type>)\
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

    REFBUFFER_GENERATOR("UInt8RefBufferGenerator",UInt8);
    REFBUFFER_GENERATOR("Int8RefBufferGenerator",Int8);
    REFBUFFER_GENERATOR("UInt16RefBufferGenerator",UInt16);
    REFBUFFER_GENERATOR("Int16RefBufferGenerator",Int16);
    REFBUFFER_GENERATOR("UInt32RefBufferGenerator",UInt32);
    REFBUFFER_GENERATOR("Int32RefBufferGenerator",Int32);
    REFBUFFER_GENERATOR("UInt64RefBufferGenerator",UInt64);
    REFBUFFER_GENERATOR("Int64RefBufferGenerator",Int64);
    REFBUFFER_GENERATOR("Float32RefBufferGenerator",Float32);
    REFBUFFER_GENERATOR("Float64RefBufferGenerator",Float64);
    REFBUFFER_GENERATOR("Float128RefBufferGenerator",Float128);

}


