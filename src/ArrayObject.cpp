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


ArrayObject::ArrayObject():NumericObject(){
	_shape.reset();
	_data_object.reset();
	_index_buffer = NULL;
}

ArrayObject::ArrayObject(const ArrayObject &a):NumericObject(a){
	//set shape object
	_shape.reset(new ArrayShape(*(a._shape)));
	if (!_shape) {
		//raise an exception here if memory allocation fails
		MemoryAllocationError e("Array<T>::Array",
				"Cannot allocate memory for ArrayShape instance!");
		throw e;
	}

	_index_buffer = new unsigned int[_shape->getRank()];

}


ArrayObject::ArrayObject(const unsigned int &r, const unsigned int s[]):NumericObject(){
	_shape.reset(new ArrayShape(r, s));
	_index_buffer = new UInt32[_shape->getRank()];
}

ArrayObject::ArrayObject(const ArrayShape &s):NumericObject(){
	EXCEPTION_SETUP("ArrayObject::ArrayObject(const ArrayShape &s):NumericObject()");

	_shape.reset(new ArrayShape(s));
	if (!_shape) {
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for ArrayShape object!");
		EXCEPTION_THROW();
	}
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

ArrayObject &ArrayObject::operator=(const ArrayObject &o){
	if(this != &o){
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

	if(_data_object){
		//an exception occurs typically here in cases where
		//no data buffer object has been set
		if (s.getSize() != _data_object->getSize()) {
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

	if (_data_object) {
		if (s->getSize() != _data_object->getSize()) {
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
	_data_object = b;
}

const BufferObject::sptr ArrayObject::getBuffer() const{
	return _data_object;
}

//end of namespace
}
}

