/*
 * Declaration of class ArrayObject
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
 * Declaration of class ArrayObject which is the base class for all
 * instantiations of the Array<T> template declared in Array.hpp.
 *
 * Created on: Jun 9, 2011
 *     Author: Eugen Wintersberger
 *
 */

#ifndef ARRAYOBJECT_HPP_
#define ARRAYOBJECT_HPP_

#include "Buffer.hpp"
#include "Shape.hpp"
#include "NumericObject.hpp"
#include "boost/shared_ptr.hpp"

namespace pni{
namespace utils{

//! \ingroup Data-objects
//! \brief Base class for numeric arrays

//! The class ArrayObject acts as a base class for all array-like classes.
//! It provides the management of the array shape object and an interface
//! of methods an Array-class must overload in order to work properly.
class ArrayObject:public NumericObject {
private:

	//some operators should not be available from outside
	//! assignment operator
	ArrayObject &operator=(const ArrayObject &);
protected:
	Shape _shape; //!< shape object describing the shape of the array
					   //!< and managing the access to the data

	//! copy constructor
	ArrayObject(const ArrayObject &a);
	//! move constructor
	ArrayObject(ArrayObject &&a);
	//! constructor with an array shape pointer

	//! The pointer to an existing ArrayShape object is used to construct
	//! the Array-object.
	//!
	//! \param s - reference to a shape object
	//! \sa Array(const boost::shared_ptr<ArrayShape> &s)
	ArrayObject(const Shape &s);
public:
	typedef boost::shared_ptr<ArrayObject> sptr;  //!< shared pointer to an ArrayObject
	//! default constructor
	ArrayObject();
	//! destructor
	virtual ~ArrayObject();

	//! set the shape of the array

	//! This method behaves different depending on the allocation status of the
	//! array object. If the array is not allocated yet any kind of
	//! shape object can be passed to this method. If the array is already
	//! allocated (which means that it holds already a shape object) the
	//! size of the shape (the total number of elements) must match that of the
	//! actual shape object of the array. Otherwise an exception will be thrown.
	//! The shape object is passed by reference and thus a copy of it will be
	//! created. Furthermore, the size of the shape object must not be zero.
	//! \throws SizeMissmatchError shape sizes do not match or size is zero
	//! \param s reference to the existing shape object
	//! \sa void setShape(boost::shared_ptr<ArrayShape> &s)
	virtual void shape(const Shape &s);
	//! obtain the shape of an array

	//! Set the smart pointer ptr to the value of the pointer holding the
	//! ArrayShape-object in the Array. After this call ptr and the Array
	//! share the shape object.
	virtual const Shape &shape() const;

	//! set the BufferObject that belongs to an array
	virtual void buffer(const BufferObject &b) = 0;
	//! get the BufferObject

	//! Get the buffer object of an array. A constant reference is returned
	//! making it impossible to alter the buffer from outside the array.
	//! This should help to avoid segmentation faults that would occur
	//! if something like this happens.
	//! THIS METHOD MUST BE IMPLEMENTED BY THE CONCRETE ARRAY IMPLEMENTATION!!!!
	//! OTHERWISE A NotImplementedError will be raised.
	//! \return reference to a buffer object
	virtual const BufferObject &buffer() const = 0;

	//allocate memory according to the shape object
	virtual void allocate() = 0;

	//! total number of elements in the array
	virtual UInt64 size(){
		return _shape.size();
	}

	virtual bool is_allocated() const = 0;
	virtual void *void_ptr() = 0;
	virtual const void *void_ptr() const = 0;
	virtual void reset(){
		_shape.rank(0);
	}

};


//end of namespace
}
}

#endif /* ARRAYOBJECT_HPP_ */
