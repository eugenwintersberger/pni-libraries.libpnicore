/*
 * DataObject.cpp
 *
 *  Created on: Oct 4, 2011
 *      Author: eugen
 */

#include <boost/python.hpp>


#include "../src/DataObject.hpp"
#include "../src/NumericObject.hpp"
#include "../src/ArrayObject.hpp"
#include "../src/PNITypes.hpp"
#include "../src/ArrayShape.hpp"
#include "../src/Buffer.hpp"
#include "../src/Index.hpp"

using namespace pni::utils;
using namespace boost::python;

#define BUFFER_CLASS(type,name) \
	void (Buffer<type>::*(name ## allocate0))() = &Buffer<type>::allocate;\
	void (Buffer<type>::*(name ## allocate1))(const UInt64 &) = &Buffer<type>::allocate;\
	class_<Buffer<type> >(#name)\
			.def(init<Buffer<type> >())\
			.def(init<type>())\
			.add_property("size",&Buffer<type>::getSize,&Buffer<type>::setSize)\
			.add_property("element_size",&Buffer<type>::getElementSize)\
			.add_property("memory_size",&Buffer<type>::getMemSize)\
			.def("allocate",(name ## allocate0))\
			.def("allocate",(name ## allocate1))\
			.def("free",&Buffer<type>::free)\
			;

BOOST_PYTHON_MODULE(pniutils)
{

	class_<DataObject>("DataObject")
			.def(init<String>())
			.def(init<String,String>())
			.def(init<DataObject>())
			.add_property("name", &DataObject::getName,&DataObject::setName)
			.add_property("description",&DataObject::getDescription,&DataObject::setDescription)
			;

	class_<NumericObject,bases<DataObject> >("NumericObject")
			.def(init<String,String>())
			.def(init<String,String,String>())
			.def(init<NumericObject>())
			.add_property("unit",&NumericObject::getUnit,&NumericObject::setUnit)
			;

	class_<Index>("Index")
			.def(init<UInt64>())
			.def(init<Index>())
			.add_property("rank",&Index::getRank,&Index::setRank)
			.def("getIndex",&Index::getIndex)
			.def("setIndex",&Index::setIndex)
			.def("increment",&Index::increment)
			.def("decrement",&Index::decrement)
			.def(self == self)
			.def(self != self)
			;

	class_<ArrayShape>("ArrayShape")
			.def(init<ArrayShape>())
			.def(init<UInt64>())
			.add_property("rank",&ArrayShape::getRank,&ArrayShape::setRank)
			.def("setDimension",&ArrayShape::setDimension)
			.def("getDimension",&ArrayShape::getDimension)
			.def("getSize",&ArrayShape::getSize)
			.def("getOffset",&ArrayShape::getOffset)
			.def("getIndex",&ArrayShape::getIndex)
			.def(self == self)
			.def(self != self)
			//need some operators
			;




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




