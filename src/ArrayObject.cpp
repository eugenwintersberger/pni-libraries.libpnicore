/*
 * Implementation of class ArrayObject delcard in ArrayObject.hpp
 *
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniutils.
 *
 * libpniutils is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniutils is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Implementation of class ArrayObject. Which is the base class for all
 * instantiations of the Array<T> template declared in Array.hpp.
 *
 * Created on: Jun 1, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#include "ArrayShape.hpp"
#include "ArrayObject.hpp"

namespace pni{
namespace utils{

//======================constructors and desctructor============================
//implementation of the default constructor
ArrayObject::ArrayObject():NumericObject(){
}

//------------------------------------------------------------------------------
//implementation of the copy constructor
ArrayObject::ArrayObject(const ArrayObject &a):NumericObject(a){
	EXCEPTION_SETUP("ArrayObject::ArrayObject(const ArrayObject &a)");

	_shape = a._shape;
}

//------------------------------------------------------------------------------
//implementation of the standard constructor
ArrayObject::ArrayObject(const ArrayShape &s):NumericObject(){
	_shape = s;
}

//------------------------------------------------------------------------------
//implementation of the move constructor
ArrayObject::ArrayObject(ArrayObject &&a):NumericObject(std::move(a)){
	_shape = std::move(a._shape);
}

//------------------------------------------------------------------------------
//implementation of the destructor
ArrayObject::~ArrayObject(){
	//we have to do here something - so we set the rank to 0
	//that might be used as an indication that the array is
	//destroyed.
	_shape.rank(0);
}

//=====================class methods============================================
//implementation of shape
void ArrayObject::shape(const ArrayShape &s){
	EXCEPTION_SETUP("void ArrayObject::setShape(const ArrayShape &s)");

	//UInt32 orank = _shape.rank();

	if(this->is_allocated()){
		//an exception occurs typically here in cases where
		//no data buffer object has been set
		if (s.size() != this->buffer().size()) {
			//raise an exception if the size of the new shape object
			//and the buffer object do not fit.
			EXCEPTION_INIT(SizeMissmatchError,"shape and array size do not match!");
			EXCEPTION_THROW();
		}
	}
	//create a new shape object
	_shape = s;
}

//------------------------------------------------------------------------------
const ArrayShape &ArrayObject::shape() const{
	return _shape;
}





//end of namespace
}
}

