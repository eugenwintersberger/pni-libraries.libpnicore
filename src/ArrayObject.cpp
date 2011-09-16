/*
 * ArrayObject.cpp
 *
 *  Created on: Jun 1, 2011
 *      Author: Eugen Wintersberger
 */

#include "ArrayShape.hpp"
#include "ArrayObject.hpp"

namespace pni{
namespace utils{

//======================constructors and desctructor============================
ArrayObject::ArrayObject():NumericObject(){
	EXCEPTION_SETUP("ArrayObject::ArrayObject():NumericObject()");

	//there is nothing to do with _shape

	_index_buffer = NULL;
}

ArrayObject::ArrayObject(const ArrayObject &a):NumericObject(a){
	EXCEPTION_SETUP("ArrayObject::ArrayObject(const ArrayObject &a):NumericObject(a)");

	//set shape object
	try{
		_shape = a.getShape();
	}catch(MemoryAllocationError &error){
		EXCEPTION_INIT(MemoryAllocationError,"Memory allocation of ArrayShape object faile!");
		EXCEPTION_THROW();
	}

	_index_buffer = NULL;
	_index_buffer = new UInt32[_shape.getRank()];
	if(_index_buffer == NULL){
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for index buffer!");
		EXCEPTION_THROW();
	}
}


ArrayObject::ArrayObject(const ArrayShape &s):NumericObject(){
	EXCEPTION_SETUP("ArrayObject::ArrayObject(const ArrayShape &s):NumericObject()");

	try{
		_shape = s;
	}catch(MemoryAllocationError &error){
		EXCEPTION_INIT(MemoryAllocationError,"Memory allocation of ArrayShape object failed!");
		EXCEPTION_THROW();
	}

	_index_buffer = NULL;
	_index_buffer = new UInt32[_shape.getRank()];
	if (_index_buffer == NULL) {
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for index buffer!");
		EXCEPTION_THROW();
	}
}


ArrayObject::~ArrayObject(){
	if (_index_buffer != NULL) delete[] _index_buffer;
}



PNITypeID ArrayObject::getTypeID() const {
	return NONE;
}

void ArrayObject::setShape(const ArrayShape &s){
	EXCEPTION_SETUP("void ArrayObject::setShape(const ArrayShape &s)");

	/*
	if(s.getSize() == 0){
		EXCEPTION_INIT(SizeMissmatchError,"Size of shape object must not be zero if set by reference!");
		EXCEPTION_THROW();
	}*/

	UInt32 orank = _shape.getRank();

	if(isAllocated()){
		//an exception occurs typically here in cases where
		//no data buffer object has been set
		if (s.getSize() != getBuffer().getSize()) {
			//raise an exception if the size of the new shape object
			//and the buffer object do not fit.
			EXCEPTION_INIT(SizeMissmatchError,"shape and array size do not match!");
			EXCEPTION_THROW();
		}
	}
	//create a new shape object
	_shape = s;

	//if the rank of the shape has changed we need to reallocate the
	//index buffer
	if(orank != _shape.getRank()){

		if (_index_buffer != NULL) delete[] _index_buffer;

		_index_buffer = new UInt32[_shape.getRank()];
		if (_index_buffer == NULL) {
			EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for index buffer!");
			EXCEPTION_THROW();
		}
	}
}



const ArrayShape &ArrayObject::getShape() const{
	return _shape;
}

void ArrayObject::reset(){
	_shape = ArrayShape();
}



//===methods which must be overloaded by the concrete array implementation======

void ArrayObject::setBuffer(const BufferObject &b){
	EXCEPTION_SETUP("void ArrayObject::setBuffer(const BufferObject &b)");
	EXCEPTION_INIT(NotImplementedError,"This method must be overridden by an concrete implementation!");
	EXCEPTION_THROW();
}

const BufferObject &ArrayObject::getBuffer() const{
	EXCEPTION_SETUP("const BufferObject &ArrayObject::getBuffer() const");
	EXCEPTION_INIT(NotImplementedError,"This method must be overridden by a concrete implementation!");
	EXCEPTION_THROW();

	//this does not matter because this code will never be reached!
	BufferObject *o = new BufferObject();
	return *o;
}

bool ArrayObject::isAllocated() const{
	EXCEPTION_SETUP("bool ArrayObject::isAllocated() const");
	EXCEPTION_INIT(NotImplementedError,"This method must be overridden by a concrete implementation!");
	EXCEPTION_THROW();
	return false;
}

void *ArrayObject::getVoidPtr(){
	EXCEPTION_SETUP("void *ArrayObject::getVoidPtr()");
	EXCEPTION_INIT(NotImplementedError,"This method must be overridden by a concrete implementation!");
	EXCEPTION_THROW();
	return NULL;
}

const void *ArrayObject::getVoidPtr() const{
	EXCEPTION_SETUP("const void *ArrayObject::getVoidPtr() const");
	EXCEPTION_INIT(NotImplementedError,"This method must be overridden by a concrete implementation!");
	return NULL;
}

//end of namespace
}
}

