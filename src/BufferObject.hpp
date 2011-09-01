/*
 * BufferObject.hpp
 *
 *  Created on: Aug 31, 2011
 *      Author: eugen
 */

#ifndef BUFFEROBJECT_HPP_
#define BUFFEROBJECT_HPP_

#include "PNITypes.hpp"
#include "boost/shared_ptr.hpp"

namespace pni{
namespace utils{


//! \addtogroup Data-objects
//! @{

//! BufferObject - base class for data buffers

//! BufferObject is the base class for the Buffer<T> template.
//! This class can be used for polymorphic operations for accessing
//! instances of Buffer<T> objects of unknown data type.
class BufferObject{
private:
	void   *_ptr;       //!< pointer to the allocated memory region
	UInt64 _size;       //!< number of elements in the buffer
	UInt64 _elem_size;  //!< size of a single element in byte
	UInt64 _tot_size;   //!< size in bytes

	void _compute_total_size();

public:
	typedef boost::shared_ptr<BufferObject> sptr;  //!< smart pointer to a BufferObject
	//! default constructor
	BufferObject();
	//! copy constructor

	//! \throws MemoryAllocationError if memory allocation failes
	//! \param b orignal buffer object
	BufferObject(const BufferObject &b);
	//! constructor

	//! Constructor for a BufferObject that initializes the number of elements
	//! in the buffer and the element size (in bytes). Thus using this
	//! constructor memory is allocated at object creation.
	//! \throws MemoryAllocationError if memory allocation fails
	//! \param n number of elements in the buffer
	//! \param es element size
	BufferObject(UInt64 n,UInt64 es);
	//! destructor
	virtual ~BufferObject();

	//! assignment operator

	//! Assigning the content of buffer o to this buffer. If the total size
	//! of o differs from that of the assigned buffer new memory is allocated.
	//! \throws MemoryAllocationError if memory allocation fails
	//! \param o buffer from which to assign
	//! \return reference to this object
	BufferObject &operator=(const BufferObject &o);

	//! return the number of elements in the buffer
	virtual UInt64 getSize() const;
	//! set the number of elements
	virtual void setSize(UInt64 s);
	//! set element size
	virtual void setElementSize(UInt64 es);
	//! get element size
	virtual UInt64 getElementSize() const;
	//! return the total amount of memory allocated by the buffer
	virtual UInt64 getMemSize() const{return _tot_size;}
	//! memory allocation

	//! Allocates memory for the requested number of elements.
	//! This method must be implemented by child classes of DataBuffer.
	//! \throws MemoryAllocationError if memory allocation failes
	//! \param n number of elements in the buffer
	virtual void allocate();
	virtual void free();

	//! return a void pointer to the allocated memory
	virtual void *getVoidPtr();
	virtual const void *getVoidPtr() const;

	friend bool operator==(const BufferObject &a,const BufferObject &b);
	friend bool operator!=(const BufferObject &a,const BufferObject &b);
};

//end of namespace
}
}

#endif /* BUFFEROBJECT_HPP_ */
