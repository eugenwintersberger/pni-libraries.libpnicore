/*
 * ArrayObject.hpp
 *
 *  Created on: Jun 9, 2011
 *      Author: eugen
 */

#ifndef ARRAYOBJECT_HPP_
#define ARRAYOBJECT_HPP_

#include "Buffer.hpp"
#include "ArrayShape.hpp"
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
	ArrayShape _shape; //!< shape object describing the shape of the array
							 //!< and managing the access to the data
	UInt32 *_index_buffer; 	 //!< a buffer used to hold index variables.
public:
	typedef boost::shared_ptr<ArrayObject> sptr;  //!< shared pointer to an ArrayObject
	//! default constructor
	ArrayObject();
	//! copy constructor
	ArrayObject(const ArrayObject &a);
	//! constructor with an array shape pointer

	//! The pointer to an existing ArrayShape object is used to construct
	//! the Array-object.
	//!
	//! \param s - reference to a shape object
	//! \sa Array(const boost::shared_ptr<ArrayShape> &s)
	ArrayObject(const ArrayShape &s);
	//! destructor
	virtual ~ArrayObject();

	//! get the type id of the elemnt type

	//! This method must be overloaded by child classes implementing a concrete
	//! array. It should return the type code of the native PNI type of the
	//! array data.
	//! \return type id of the native type
	virtual PNITypeID getTypeID() const;

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
	virtual void setShape(const ArrayShape &s);
	//! obtain the shape of an array

	//! Set the smart pointer ptr to the value of the pointer holding the
	//! ArrayShape-object in the Array. After this call ptr and the Array
	//! share the shape object.
	virtual const ArrayShape &getShape() const;

	//! set the BufferObject that belongs to an array
	virtual void setBuffer(const BufferObject &b);
	//! get the BufferObject

	//! Get the buffer object of an array. A constant reference is returned
	//! making it impossible to alter the buffer from outside the array.
	//! This should help to avoid segmentation faults that would occur
	//! if something like this happens.
	//! THIS METHOD MUST BE IMPLEMENTED BY THE CONCRETE ARRAY IMPLEMENTATION!!!!
	//! OTHERWISE A NotImplementedError will be raised.
	//! \return reference to a buffer object
	virtual const BufferObject &getBuffer() const;

	//allocate memory according to the shape object
	virtual void allocate(){

	}

	//return the size of the object
	virtual UInt64 size(){
		return _shape.getSize();
	}

	virtual bool isAllocated() const;
	virtual void *getVoidPtr();
	virtual const void *getVoidPtr() const;

	virtual void reset();
};





//end of namespace
}
}

#endif /* ARRAYOBJECT_HPP_ */
