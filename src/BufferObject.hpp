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

//! \brief data buffer

//! This class acts as a raw data buffer. It performs no type checking but rather
//! simply allocates memory on the system. The size of memory allocated depends on
//! two parameters
//! - size of elements in bytes
//! - number of elements in the buffer
//!
//! Both values can be configured after the instantiation using the appropriate methods
//! or directly via the constructor at object creation. The two parameters can be obtained
//! from a class using getElementSize() and getSize() respectively. In addition, the total
//! size in bytes occupied by the buffer in system memory can be obtained using getMemSize().
//!
//! This object allocates only contiguous memory regions. If no contiguous region of the
//! requested type can be allocated, memory allocation fails. This object is most probably
//! not that important for application developers but quite useful for those who want to
//! contribute to this library. For application developers the Buffer<T> template
//! is much more applicable.
class BufferObject{
private:
	void   *_ptr;       //!< pointer to the allocated memory region
	UInt64 _size;       //!< number of elements in the buffer
	UInt64 _elem_size;  //!< size of a single element in byte
	UInt64 _tot_size;   //!< total size of memory occupied in bytes

	void _compute_total_size();

public:
	//! smart pointer to a BufferObject
	typedef boost::shared_ptr<BufferObject> sptr;
	//! default constructor

	//! This constructor sets all internal parameters to 0. No memory is allocated.
	BufferObject();
	//! copy constructor

	//! Initializes a new BufferObject with the content of an already existing one.
	//! \throws MemoryAllocationError if memory allocation fails
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

	//! get number of elements

	//! Returns the number of elements of a particular size (can be obtained using
	//! getElementSize()).
	//! \returns number of elements
	virtual UInt64 getSize() const;
	//! set number of elements

	//! Sets the number of elements of a particular size that should be stored in the
	//! buffer.
	//! \param s number of elements
	virtual void setSize(UInt64 s);
	//! set element size

	//! Sets the size of the elements in the buffer in bytes.
	//! \param es element size
	virtual void setElementSize(UInt64 es);
	//! get element size

	//! Returns the size of each element in the buffer in bytes.
	//! \return element size
	virtual UInt64 getElementSize() const;
	//! return total size

	//! This method returns the total amount of memory allocated by the buffer
	//! in bytes. Basically this number can be computed with
	//! number of elements times element size.
	//! \return total memory consumption
	virtual UInt64 getMemSize() const{return _tot_size;}
	//! allocate memory

	//! Allocates memory for the requested number of elements of particular size.
	//! After initializing the class this method finally allocated the
	//! memory.
	//! \throws MemoryAllocationError if memory allocation fails
	virtual void allocate();
	//! free memory

	//! Frees all memory allocated by the BufferObject.
	virtual void free();

	//! get void pointer

	//! Returns a void pointer to the allocated memory region. The pointer can
	//! be used to read and write data to this region.
	//! \return pointer to memory
	virtual void *getVoidPtr();
	//! get void pointer

	//! Returns a const. pointer to the allocated memory region.
	//! \return constant pointer to memory.
	virtual const void *getVoidPtr() const;

	//! equality operator

	//! Compares tow different BufferObjects and considers them equal if the
	//! following conditions are satisfied
	//! - number of elements is equal
	//! - size of elements is equal
	//! - content in memory is equal
	//!
	//! The equality of the content is done by comparing the values on the level
	//! of single bytes. Thus only integer number comparison is necessary which
	//! should speed up the procedure.
	//! \return true/false
	friend bool operator==(const BufferObject &a,const BufferObject &b);
	//! Inequality operator

	//! The counterpart of the == operator.
	//! \see bool operator==(const BufferObject &a,const BufferObject &b)
	friend bool operator!=(const BufferObject &a,const BufferObject &b);
};

//! @}

//end of namespace
}
}

#endif /* BUFFEROBJECT_HPP_ */
