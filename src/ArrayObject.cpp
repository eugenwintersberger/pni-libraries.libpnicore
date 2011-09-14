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
	_shape.reset(new ArrayShape());
	_index_buffer = NULL;
}

ArrayObject::ArrayObject(const ArrayObject &a):NumericObject(a){
	EXCEPTION_SETUP("ArrayObject::ArrayObject(const ArrayObject &a):NumericObject(a)");

	//set shape object
	_shape.reset(new ArrayShape(*(a._shape)));
	if (!_shape) {
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for ArrayShape object!");
		EXCEPTION_THROW();
	}

	_index_buffer = NULL;
	_index_buffer = new UInt32[_shape->getRank()];
	if(_index_buffer == NULL){
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for index buffer!");
		_shape.reset();
		EXCEPTION_THROW();
	}
}


ArrayObject::ArrayObject(const unsigned int &r, const unsigned int s[]):NumericObject(){
	EXCEPTION_SETUP("ArrayObject::ArrayObject(const unsigned int &r, const unsigned int s[]):NumericObject()");

	_shape.reset(new ArrayShape(r, s));
	if(!_shape){
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for ArrayShape object!");
		EXCEPTION_THROW();
	}

	_index_buffer = NULL;
	_index_buffer = new UInt32[_shape->getRank()];
	if(_index_buffer == NULL){
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for index buffer!");
		_shape.reset();
		EXCEPTION_THROW();
	}
}

ArrayObject::ArrayObject(const ArrayShape &s):NumericObject(){
	EXCEPTION_SETUP("ArrayObject::ArrayObject(const ArrayShape &s):NumericObject()");

	_shape.reset(new ArrayShape(s));
	if (!_shape) {
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for ArrayShape object!");
		EXCEPTION_THROW();
	}

	_index_buffer = NULL;
	_index_buffer = new UInt32[_shape->getRank()];
	if (_index_buffer == NULL) {
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for index buffer!");
		_shape.reset();
		EXCEPTION_THROW();
	}
}

ArrayObject::ArrayObject(const ArrayShape::sptr &s):NumericObject(){
	EXCEPTION_SETUP("ArrayObject::ArrayObject(const ArrayShape::sptr &s):NumericObject()");
	_shape = s; //the shape is now shared with the array creator (will increment reference counter)

	_index_buffer = NULL;
	_index_buffer = new UInt32[_shape->getRank()];
	if (_index_buffer == NULL) {
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for index buffer!");
		EXCEPTION_THROW();
	}
}

ArrayObject::~ArrayObject(){
	if (_index_buffer != NULL)
		delete[] _index_buffer;
	_shape.reset();
}

//=======================assignment operator====================================
ArrayObject &ArrayObject::operator=(const ArrayObject &o){
	if(this != &o){
		if(o._shape->getSize()!=_shape->getSize()){

		}
		//ATTENTION: _shape is a shared pointer => we cannot simply
		//copy the pointer because that is not what we want. We have
		//to assign the CONTENT of the pointer.
		*_shape = *o._shape;

		//allocate memory for the new index buffer
		if(_index_buffer != NULL) delete [] _index_buffer;
		_index_buffer = new UInt32[_shape->getRank()];
		//initialize the index buffer
		for(UInt32 i = 0; i < _shape->getRank(); i++) _index_buffer[i] = 0;
	}

	return *this;
}

PNITypeID ArrayObject::getTypeID() const {
	return NONE;
}

void ArrayObject::setShape(const ArrayShape &s){
	EXCEPTION_SETUP("void ArrayObject::setShape(const ArrayShape &s)");

	if(isAllocated()){
		//an exception occurs typically here in cases where
		//no data buffer object has been set
		if (s.getSize() != getBuffer()->getSize()) {
			//raise an exception if the size of the new shape object
			//and the buffer object do not fit.
			EXCEPTION_INIT(SizeMissmatchError,"shape and array size do not match!");
			EXCEPTION_THROW();
		}
	}
	//create a new shape object
	_shape.reset(new ArrayShape(s));

	if (_index_buffer != NULL)
		delete[] _index_buffer;

	_index_buffer = new UInt32[_shape->getRank()];
	if (_index_buffer == NULL) {
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for index buffer!");
		EXCEPTION_THROW();
	}
}

void ArrayObject::setShape(const ArrayShape::sptr &s){
	EXCEPTION_SETUP("void ArrayObject::setShape(const ArrayShape::sptr &s)");

	//need to take care if the buffer is already allocated
	if (isAllocated()) {
		if (s->getSize() != getBuffer()->getSize()) {
			//raise and exception if the size of the new shape object
			//and the buffer object do not match
			EXCEPTION_INIT(SizeMissmatchError,"shape and array size do not match!");
			EXCEPTION_THROW();
		}
	}

	_shape = s;

	if (_index_buffer != NULL)
		delete[] _index_buffer;
	_index_buffer = new UInt32[_shape->getRank()];
	if (_index_buffer == NULL) {
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for index buffer!");
		EXCEPTION_THROW();
	}
}

const ArrayShape::sptr ArrayObject::getShape() const{
	return _shape;
}


void ArrayObject::setBuffer(BufferObject::sptr b){

}

void ArrayObject::setBuffer(const BufferObject &b){

}

const BufferObject::sptr ArrayObject::getBuffer() const{
	return NULL;
}

bool ArrayObject::isAllocated() const{
	return false;
}

void *ArrayObject::getVoidPtr(){
	return NULL;
}

const void *ArrayObject::getVoidPtr() const{
	return NULL;
}

//end of namespace
}
}

