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

//! Base class for numeric arrays
class ArrayObject:public NumericObject {
protected:
	BufferObject::sptr _data_object; //!< general buffer object
	ArrayShape::sptr _shape;     	 //!< shape object describing the shape of the array
								 	 //!< and managing the access to the data
	unsigned int *_index_buffer; 	 //!< a buffer used to hold index variables.
public:
	typedef boost::shared_ptr<ArrayObject> sptr;
	//! default constructor
	ArrayObject();
	//! copy constructor
	ArrayObject(const ArrayObject &);
	//! constructor where rank and dimension are set
	//! In this case a shape object is created and memory allocated.
	//! The shape object as well as the data buffer will be managed
	//! by the resulting Array object.

	//! \param r rank of the array
	//! \param s array with number of elements along each direction
	ArrayObject(const unsigned int &r, const unsigned int s[]);
	//! constructor with an array shape pointer

	//! The pointer to an existing ArrayShape object is used to construct
	//! the Array-object.
	//!
	//! \param s - reference to a shape object
	//! \sa Array(const boost::shared_ptr<ArrayShape> &s)
	ArrayObject(const ArrayShape &s);
	//! constructor with a smart pointer to an array shape

	//! Since a smart pointer is used the the shape object of the
	//! created Array object will be shared with the array's creator.

	//! \param &s reference to a smart pointer to a shape object
	ArrayObject(const ArrayShape::sptr &s);
	virtual ~ArrayObject();

	//! get the type id of the elemnt type
	virtual PNITypeID getTypeID() const;

	//! set the shape of the array

	//! The size of the shape array and that of the existing array must match
	//! otherwise and exception will be raised. Since a reference to a plain
	//! ArrayShape object is passed the Array object creates a new ArrayShape
	//! instance and copies the content from the existing one.

	//! \param s reference to the existing shape object
	//! \sa void setShape(boost::shared_ptr<ArrayShape> &s)
	virtual void setShape(const ArrayShape &s);
	//! set the shape of the array

	//! The size of the shape array and that of the existing array must match
	//! otherwise and exception will be raised. Here a shared smart pointer
	//! is passed to the method. Thus the calling instance and the array
	//! will share the shape object -  no copy process takes place.

	//! \param s reference to the existing shape object
	//! \sa void setShape(const ArrayShape &s)
	virtual void setShape(const ArrayShape::sptr &s);

	//! obtain the shape of an array

	//! Set the smart pointer ptr to the value of the pointer holding the
	//! ArrayShape-object in the Array. After this call ptr and the Array
	//! share the shape object.
	virtual const ArrayShape::sptr getShape() const;

	virtual void setBuffer(const BufferObject &b);
	virtual void setBuffer(BufferObject::sptr &b);
	virtual const BufferObject::sptr getBuffer() const;
};





//end of namespace
}
}

#endif /* ARRAYOBJECT_HPP_ */
