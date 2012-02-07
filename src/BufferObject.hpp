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

#include "Types.hpp"
#include "boost/shared_ptr.hpp"
#include "service.hpp"

namespace pni{
namespace utils{

//! \ingroup data_classes
//! \brief abstract buffer class

//! BufferObject is an abstract class from which all buffer like objects
//! must derive. The most prominent descendant of BufferObject is the
//! Buffer<T> template. BufferObject can be used in all cases where such
//! an object is passed through the program without any type information.
//! Buffer like objects are assumed to hold a number of a elements
//! of a particular size contiguously in memory. Thus they behave pretty
//! much like pointers without all the drawbacks of a raw pointer.
//! Indeed libpniutils uses the Buffer<T> template every where where
//! a pointer could be used too.
class BufferObject{
private:
	size_t _size;       //!< number of elements in the buffer

protected:
	//! standard constructor

	//! This constructor is used by derived classes in order to
	//! set internal members of the base class
	explicit BufferObject(size_t size);

	//! set number of elements

	//! Sets the number of elements of a particular size that should be stored
	//! in the buffer. This method must not be invoked by a user and is
	//! thus protected. It is the job of the derived class to ensure the
	//! correct usage of this method.
	//! \param s number of elements
	virtual void size(size_t s);
public:
	//! smart pointer to a BufferObject
	typedef boost::shared_ptr<BufferObject> sptr;
	//! default constructor
	explicit BufferObject();
	//! copy constructor
	explicit BufferObject(const BufferObject &b);
	//! move constructor
	explicit BufferObject(BufferObject &&b);

	//! destructor
	virtual ~BufferObject();

	//! copy assignment operator
	BufferObject &operator=(const BufferObject &o);
	//! move assignment operator
	BufferObject &operator=(BufferObject &&o);

	//! get number of elements

	//! Returns the number of elements stored in the buffer (the
	//! size of each element in bytes can be obtained from
	//! element_size()).
	//! \returns number of elements
	virtual size_t size() const;

	//! get element size

	//! Returns the size of the elements stored in the buffer in bytes.
	//! \return element size
	virtual size_t element_size() const = 0;
	//! get memory size

	//! Returns the total memory occupied by the payload of the buffer object.
	//! \return total memory consumption
	virtual size_t mem_size() const = 0;
	//! allocate memory

	//! Allocate memory for size number of elements. Subsequent calls to this
	//! cause reallocation and all data originally stored is lost.
	//! \throws MemoryAllocationError if allocation fails or size=0
	//! \param size number of elements
	virtual void allocate(const size_t &size) = 0;
	//! buffer status

	//! Returns true if the buffer is allocated - false otherwise.
	//! Use this method to check the status of a buffer object.
	//! \return true/false depending on buffer status
	virtual bool is_allocated() const = 0;
	//! free memory

	//! Frees all memory allocated by the BufferObject.
	virtual void free() = 0;

	//! get read/write void pointer

	//! Returns a void pointer to the allocated memory region. The pointer can
	//! be used to read and write data to this region.
	//! Although void pointer access is not very save it is sometimes
	//! necessary in order to cooperate with other libraries.
	//! \return pointer to memory
	virtual void *void_ptr() = 0;
	//! get void pointer

	//! Returns a const. pointer to the allocated memory region.
	//! \return constant pointer to memory.
	virtual const void *void_ptr() const = 0;

	//! get type id

	//! Return the PNI type ID of the objects stored in the buffer.
	//! If a non-PNI type is stored PNITypeID::NONE is returned.
	//! \return type id of the buffer elements
	virtual TypeID type_id() const = 0;
};

//end of namespace
}
}

#endif /* BUFFEROBJECT_HPP_ */
