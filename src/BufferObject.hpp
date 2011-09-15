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

//! This class is the base class for all data holding classes.
//! It does not allocate data at all but rather holds a couple of basic paramters
//! required for memory allocation. These parameters are
//! - number of elements in the buffer
//! - size of each elements in bytes
//! - total amount of memory occupied in bytes
//!
//! All of these parameters can be configured by the interface provided by this
//! class. Again - no memory allocation is done. This must be implemented
//! child classes implementing this functionality.
class BufferObject{
private:
	UInt64 _size;       //!< number of elements in the buffer
	UInt64 _elem_size;  //!< size of a single element in byte
	UInt64 _tot_size;   //!< total size of memory occupied in bytes

	//! compute total memory consumption

	//! This method computes the total memory that will be occupied by the
	//! buffer using the _size and the _elem_size field with
	//! \f[
	//!    size = \mbox{number of elements} \times \mbox{element size}
	//! \f]
	void _compute_total_size();

public:
	//! smart pointer to a BufferObject
	typedef boost::shared_ptr<BufferObject> sptr;
	//! default constructor

	//! This constructor sets all internal parameters to 0. No memory is allocated.
	BufferObject();
	//! copy constructor

	//! Copies all buffer parameters from the original buffer to the
	//! new one.
	//! \param b original buffer object
	BufferObject(const BufferObject &b);
	//! constructor

	//! Constructor for a BufferObject that initializes the number of elements
	//! in the buffer and the element size (in bytes).
	//! \param n number of elements in the buffer
	//! \param es element size
	BufferObject(UInt64 n,UInt64 es);
	//! destructor
	virtual ~BufferObject();
	//! get number of elements

	//! Returns the number of elements of a particular size (can be obtained using
	//! getElementSize()).
	//! \returns number of elements
	virtual UInt64 getSize() const;
	//! set number of elements

	//! Sets the number of elements of a particular size that should be stored in the
	//! buffer. If the buffer is already allocated an exception is thrown.
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
	//! After initializing the class this method finally allocates the
	//! memory. Each call of this method reallocates memory and discards
	//! the content of an eventually already allocated portion of memory.
	//! This method must be implemented by the child classes of
	//! BufferObject.
	//! If this method is called and the buffer is already allocated a
	//! MemoryAllocationError exception is thrown. You must explicitly
	//! free a buffer object prior to a new call to allocat().

	//! \throws MemoryAllocationError if memory allocation fails
	//! \throws SizeMissmatchError if element size or number of elements not set
	virtual void allocate();
	//! allocate memory

	//! This method acts as a shortcut to allocate(). It calls internally
	//! setSize() and setElementSize() and allocates the buffer.
	//! \throws MemoryAllocationError if memory allocation fails or buffer is already allocated
	//! \param size number of elements
	//! \param esize element size
	virtual void allocate(const UInt64 &size,const UInt64 &esize);
	//! allocate memory

	//! Allocate memory assuming that the element size has already been set.
	//! \throws MemoryAllocationError if memory allocation fails or buffer is already allocated
	//! \throws SizeMissmatchError if element size is not set yet
	virtual void allocate(const UInt64 &size);
	//! buffer status

	//! Returns true if the buffer is allocated - false otherwise.
	//! Use this method to check the status of a buffer object.
	//! \return true/false depending on buffer status
	virtual bool isAllocated() const;
	//! free memory

	//! Frees all memory allocated by the BufferObject.
	virtual void free();

	//! get void pointer

	//! Returns a void pointer to the allocated memory region. The pointer can
	//! be used to read and write data to this region.
	//! This method must be implemented by the child class.
	//! \return pointer to memory
	virtual void *getVoidPtr();
	//! get void pointer

	//! Returns a const. pointer to the allocated memory region.
	//! This method must be implemented by the child class.
	//! \return constant pointer to memory.
	virtual const void *getVoidPtr() const;
};

//! @}

//end of namespace
}
}

#endif /* BUFFEROBJECT_HPP_ */
