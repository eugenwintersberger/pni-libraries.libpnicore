/*
 * Declaration of class Index
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
 * Declaration of class Index which represents an index vector for accessing
 * data in an array object.
 *
 * Created on: Aug 31, 2011
 *     Author: Eugen Wintersberger
 *
 */


#ifndef INDEX_H_
#define INDEX_H_

#include "Types.hpp"
#include "Buffer.hpp"

namespace pni {
namespace utils {

//! \ingroup util_classes
//! \brief array index class

//! This class describes an index object which can be used to address data
//! within an array. The rank of the Index object must be equal the rank
//! of the array object whose data should be accessed.
class Index {
private:
	Buffer<size_t> _index; //! buffer holding the actual index value
public:
	//! default constructor
	Index();
	//! standard constructor

	//! This constructor initializes the index object with its rank at
	//! creation time.
	//! \throws MemoryAllocationError if memory allocation fails or rank=0
	Index(size_t rank);
	//! copy constructor
	//! \throws MemoryAllocationError in cases that allocation of the index buffer fails
	Index(const Index &o);
	//! move constructor
	Index(Index &&o);
	//! destructor
	virtual ~Index();

	//! copy assignment operator
	//! \throws MemoryAllocationError in cases that allocation of the index buffer fails
	Index &operator=(const Index &o);
	//! move assignment operator
	Index &operator=(Index &&o);
	//! set index rank

	//! This method is used to set the rank of an index object. If invoked
	//! on an already existing object the index object will be reinitialized.
	//! All existing content is lost.
	//! \throws MemoryAllocationError if memory allocation fails or rank=0
	//! \param rank number of dimensions
	void rank(size_t rank);
	//! get index rank

	//! Returns the number of dimensions the index object describes.
	//! \return number of dimensions
	size_t rank() const;
	//! get index value

	//! Returns the value of index determined by index.
	//! \throws IndexError if index is larger than the rank of the Index object
	//! \param index dimension for which to get the index
	//! \return index value
	size_t get(size_t index) const;
	//! set index value

	//! Sets the value of index determined by index.
	//! \throws IndexError if index exceeds the rank of the Index object
	//! \param index dimension for which the index should be set
	//! \param value value of the index
	void set(size_t index,size_t value);
	//! increment index

	//! Increments the index determined by index by one.
	//! \throws IndexError if index exceeds the rank of the Index object
	//! \throws RangeError if the increment would lead to an index value > size_t maximum
	//! \param index index of the index to increment
	void inc(size_t index);
	//! decrement index

	//! Decrements the index determined by index by one.
	//! \throws IndexError if index exceeds the rank of the Index object
	//! \throws RangeError if the decrement would yield an index value < 0
	//! \param index index of the index to decrement
	void dec(size_t index);
	//! [] operator read only

	//! This version of the [] operator allows read only access to the
	//! index buffer. It returns the index at dimension index.
	//! \throws IndexError if index exceeds the rank of the Index object
	//! \return index value
	size_t operator[](size_t index) const;
	//! [] operator read/write

	//! The read/write version of the [] operator.
	//! \throws IndexError if index exceeds the rank of the Index object
	//! \return index value
	size_t &operator[](size_t index);

	//! output operator

	//! Prints the content of the index object to an output stream.
	//! \param o reference to a stream object
	//! \param index reference to the Index object to print
	//! \return reference to an outstream object
	friend std::ostream &operator<<(std::ostream &o,const Index &index);
	//! equality operator

	//! Returns true if the rank and the indices of two Index object are identical.
	//! \param i1 reference to the first Index object
	//! \param i2 reference to the second Index object
	//! \return true if equal false otherwise
	friend bool operator==(const Index &i1,const Index &i2);
	//! inequality operator

	//! Is the counterpart of the equality operator.
	//! \see bool operator==(const Index &i1,const Index &i2)
	//! \param i1 reference to the first Index object
	//! \param i2 reference to the second Index object
	//! \return true if the tow object are not equal
	friend bool operator!=(const Index &i1,const Index &i2);
};

//end of namespace
}
}

#endif /* INDEX_H_ */
