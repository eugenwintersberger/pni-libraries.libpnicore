/*
 * Array.cpp
 *
 *  Created on: Dec 22, 2011
 *      Author: Eugen Wintersberger
 */




#include <boost/python.hpp>


#include "../src/Types.hpp"
#include "../src/ArrayObject.hpp"
#include "../src/BufferObject.hpp"
#include "../src/RefBuffer.hpp"
#include "../src/Array.hpp"


using namespace pni::utils;
using namespace boost::python;

#define ARRAY_CLASS(type,name) \
    void (Array<type,RefBuffer>::*(name ## set_buffer))(const BufferObject &) = &Array<type,RefBuffer>::buffer;\
    const BufferObject &(Array<type,RefBuffer>::*(name ## get_buffer))() const = &Array<type,RefBuffer>::buffer;\
    void (Array<type,RefBuffer>::*(name ## set_shape))(const Shape &) = &Array<type,RefBuffer>::shape;\
    const Shape &(Array<type,RefBuffer>::*(name ## get_shape))() const = &Array<type,RefBuffer>::shape;\
	class_<Array<type,RefBuffer>,bases<ArrayObject> >(#name)\
            .def(init<>())\
            .def(init<Array<type,RefBuffer> >())\
            .def(init<Shape>())\
            .def(init<Shape,RefBuffer<type> >())\
            .def(init<Shape,RefBuffer<type>,String,String,String>())\
            .def(init<Shape,String,String,String>())\
            .add_property("buffer",make_function(name ## get_buffer,return_internal_reference<1>()),name ## set_buffer)\
            .add_property("shape",make_function(name ## get_shape,return_internal_reference<1>()),name ## set_shape)\
            ;
			


void wrap_array(){
	//================Wrapping the Array template===============================
    ARRAY_CLASS(UInt8,UInt8RefArray);
    ARRAY_CLASS(Int8,Int8RefArray);
    ARRAY_CLASS(UInt16,UInt16RefArray);
    ARRAY_CLASS(Int16,Int16RefArray);
    ARRAY_CLASS(UInt32,UInt32RefArray);
    ARRAY_CLASS(Int32,Int32RefArray);
    ARRAY_CLASS(UInt64,UInt64RefArray);
    ARRAY_CLASS(Int64,Int64RefArray);
    ARRAY_CLASS(Float32,Float32RefArray);
    ARRAY_CLASS(Float64,Float64RefArray);
    ARRAY_CLASS(Float128,Float128RefArray);

}
