
#ifndef __SELECTION_HPP__
#define __SELECTION_HPP__

#include "PNITypes.hpp"
#include "ArrayShape.hpp"
#include "Index.hpp"

namespace pni{
namespace utils{

class Selection{
private:
	UInt32 _rank;     //!< rank of the source from which data is selected
	UInt32 _trank;    //!< rank of the target (determined by non-0 counts)
	UInt32 *_offset;
	UInt32 *_stride;
	UInt32 *_count;
	UInt32 *_block;

	void _allocate(UInt32 rank);
	void _compute_trank();
	void _free();

public:
	//! default constructor
	Selection();
	//! copy constructor

	//! Initializes a new Selection object with the values of an already existing
	//! one.
	//! \throws MemoryAllocationError if memory allocation fails
	//! \param s existing selection object
	Selection(const Selection &s);
	//! constructor

	//! Construct Selection object from an existing shape.

	//! Using this constructor creates a selection from an existing
	//! shape. The resulting selection can be moved within the
	//! source array using the offset.
	Selection(const ArrayShape &s);
	//! destructor
	virtual ~Selection();

	//! create shape from selection

	//! Returns the shape of the selection. This shape can be used to
	//! create a new array holding the data described by the selection.
	//! \return an instance of ArrayShape
	void getShape(ArrayShape &s) const;

	//! returns rank

	//! Returns the rank of the selection object.
	//! \return selection rank
	virtual UInt32 getRank() const;
	//! return target rank

	//! Returns the rank of the target array. This must not be equal
	//! to the rank of the selection (see above).
	//! \return number of dimensions of the target
	virtual UInt32 getTargetRank() const;
	//! sets rank

	//! Sets the rank of a Selection object. If the new rank differs from
	//! the original one all values are lost an new memory for the selection
	//! arrays is allocated.
	//! \throws MemoryAllocationError if memory allocation fails
	//! \param r new selection rank
	virtual void setRank(UInt32 r);

	//! increment offset

	//! Increments value i of the offset array by a value of one.
	//! \throws IndexError if i exceeds selection rank
	//! \param i dimension index to increment
	virtual void incrementOffset(UInt32 i);
	//! decrement offset

	//! Decrements value i of the offset array by a value of one.
	//! \throws IndexError if i exceeds the selection rank
	//! \throws RangeError if the decrement would yield a negative number
	//! \param i dimension index
	virtual void decrementOffset(UInt32 i);
	//! set offset value

	//! Set the value of offset at index i with value v.
	//! \throws IndexError if i exceeds the selection rank
	//! \param i dimension index
	//! \param v offset value
	virtual void setOffset(UInt32 i,UInt32 v);
	//! get offset value

	//! Returns the offset at dimension index i.
	//! \throws IndexError if i exceeds the selection rank
	//! \return offset value
	virtual UInt32 getOffset(UInt32 i) const;

	//! increment stride

	//! Increments value i in the stride array by a value of one.
	//! \throws IndexError if i exceeds the selection rank
	//! \param i dimension index
	virtual void incrementStride(UInt32 i);
	//! decrement stride

	//! Decrements value i in the stride array by a value of one.
	//! \throws IndexError if i exceeds the selection rank
	//! \throws RangeError if the decrement would yield a negative stride value
	//! \param i dimension index
	virtual void decrementStride(UInt32 i);
	//! set stride

	//! Sets the value i in the stride array.
	//! \throws IndexError if i exceeds the selection rank
	//! \param i dimension index
	//! \param v stride value at i
	virtual void setStride(UInt32 i,UInt32 v);
	//! get stride

	//! Returns the stride value at dimension i.
	//! \throws IndexError if i exceeds the selection rank
	//! \param i dimension index
	//! \return stride value at dimension i
	virtual UInt32 getStride(UInt32 i) const;

	//! increment count

	//! Increments value i in the count array by a value of one.
	//! \throws IndexError if i exceeds the selection rank
	//! \param i dimension index
	virtual void incrementCount(UInt32 i);
	//! decrement count

	//! Decrements value i in the count array by a value of one.
	//! \throws IndexError if i exceeds the selection rank
	//! \throws RangeError if the decrement would yield a negative count value
	//! \param i dimension index
	virtual void decrementCount(UInt32 i);
	//! set count

	//! Sets the value i in the count array.
	//! \throws IndexError if i exceeds the selection rank
	//! \param i dimension index
	//! \param v count value at i
	virtual void setCount(UInt32 i,UInt32 v);
	//! get count

	//! Returns the count value at dimension i.
	//! \throws IndexError if i exceeds the selection rank
	//! \param i dimension index
	//! \return count value at dimension i
	virtual UInt32 getCount(UInt32 i) const;
	//! increment block

	//! Increments value i in the block array by a value of one.
	//! \throws IndexError if i exceeds the selection rank
	//! \param i dimension index
	virtual void incrementBlock(UInt32 i);
	//! decrement block

	//! Decrements value i in the block array by a value of one.
	//! \throws IndexError if i exceeds the selection rank
	//! \throws RangeError if the decrement would yield a negative block value
	//! \param i dimension index
	virtual void decrementBlock(UInt32 i);
	//! set block

	//! Sets the value i in the block array.
	//! \throws IndexError if i exceeds the selection rank
	//! \param i dimension index
	//! \param v block value at i
	virtual void setBlock(UInt32 i,UInt32 v);
	//! get block

	//! Returns the block value at dimension i.
	//! \throws IndexError if i exceeds the selection rank
	//! \param i dimension index
	//! \return block value at dimension i
	virtual UInt32 getBlock(UInt32 i) const;



	//! return real Index

	//! Computes the Index object for the source array from that of the
	//! selection.
	//! \param index Index in the selection
	//! \param sindex index in the source array
	virtual void getSourceIndex(const Index &index,Index &sindex) const;


};


//end of namepsace
}
}


#endif
