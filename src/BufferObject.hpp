/*
 * Declaration of class BufferObject
 *
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 * BufferObject is the base class for all buffers and thus defines their
 * interfaces.
 *
 * Created on: Aug 31, 2011
 *     Author: Eugen Wintersberger
 *
 */


#ifndef BUFFEROBJECT_HPP_
#define BUFFEROBJECT_HPP_

#include "PNITypes.hpp"
#include "boost/shared_ptr.hpp"
#include "service.hpp"

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
	size_t _size;       //!< number of elements in the buffer
	size_t _elem_size;  //!< size of a single element in byte
	size_t _tot_size;   //!< total size of memory occupied in bytes

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
	//! move constructor
	BufferObject(BufferObject &&o);
	//! constructor

	//! Constructor for a BufferObject that initializes the number of elements
	//! in the buffer and the element size (in bytes).
	//! \param n number of elements in the buffer
	//! \param es element size
	BufferObject(UInt64 n,UInt64 es);
	//! destructor
	virtual ~BufferObject();

	//! copy assignment operator
	BufferObject &operator=(const BufferObject &o);
	//! move assignment operator
	BufferObject &operator=(BufferObject &&o);

	//! get number of elements

	//! Returns the number of elements of a particular size (can be obtained using
	//! getElementSize()).
	//! \returns number of elements
	virtual size_t getSize() const;
	virtual size_t size() const;
	//! set number of elements

	//! Sets the number of elements of a particular size that should be stored in the
	//! buffer. If the buffer is already allocated an exception is thrown.
	//! \param s number of elements
	virtual void setSize(size_t s);
	virtual void size(size_t s);
	//! set element size

	//! Sets the size of the elements in the buffer in bytes.
	//! \param es element size
	virtual void setElementSize(UInt64 es);
	virtual void element_size(size_t es);
	//! get element size

	//! Returns the size of each element in the buffer in bytes.
	//! \return element size
	virtual size_t getElementSize() const;
	virtual size_t element_size() const;
	//! return total size

	//! This method returns the total amount of memory allocated by the buffer
	//! in bytes. Basically this number can be computed with
	//! number of elements times element size.
	//! \return total memory consumption
	virtual size_t getMemSize() const{
		DEPRECATION_WARNING("size_t BufferObject::getMemSize() const",
							"size_t BufferObject::mem_size() const");
		return mem_size();
	}
	virtual size_t mem_size() const { return _tot_size;}
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
	virtual void allocate(const size_t &size,const size_t &esize);
	//! allocate memory

	//! Allocate memory assuming that the element size has already been set.
	//! \throws MemoryAllocationError if memory allocation fails or buffer is already allocated
	//! \throws SizeMissmatchError if element size is not set yet
	virtual void allocate(const size_t &size);
	//! buffer status

	//! Returns true if the buffer is allocated - false otherwise.
	//! Use this method to check the status of a buffer object.
	//! \return true/false depending on buffer status
	virtual bool isAllocated() const;
	virtual bool is_allocated() const;
	//! free memory

	//! Frees all memory allocated by the BufferObject.
	virtual void free();

	//! get void pointer

	//! Returns a void pointer to the allocated memory region. The pointer can
	//! be used to read and write data to this region.
	//! This method must be implemented by the child class.
	//! \return pointer to memory
	virtual void *getVoidPtr();
	virtual void *void_ptr();
	//! get void pointer

	//! Returns a const. pointer to the allocated memory region.
	//! This method must be implemented by the child class.
	//! \return constant pointer to memory.
	virtual const void *getVoidPtr() const;
	virtual const void *void_ptr() const;
};

//! @}

//end of namespace
}
}

#endif /* BUFFEROBJECT_HPP_ */
