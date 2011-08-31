
#include "Selection.hpp"
#include "Exceptions.hpp"

namespace pni{
namespace utils{

//===========private functions for memory management===========================
void Selection::_free(){
	if(_offset != NULL) delete [] _offset;
	if(_stride != NULL) delete [] _stride;
	if(_count != NULL) delete [] _count;
	if(_block != NULL) delete [] _block;
}

void Selection::_allocate(UInt32 rank){
	EXCEPTION_SETUP("void Selection::_allocate(UInt32 rank)");
	if(_offset != NULL) delete [] _offset;
	_offset = new UInt32[rank];
	if(_offset==NULL){
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for offset buffer!");
		EXCEPTION_THROW();
	}

	if(_stride != NULL) delete [] _stride;
	_stride = new UInt32[rank];
	if(_stride == NULL){
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for stride buffer!");
		_free();
		EXCEPTION_THROW();
	}

	if(_count != NULL) delete [] _count;
	_count = new UInt32[rank];
	if(_count == NULL){
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for count buffer!");
		_free();
		EXCEPTION_THROW();
	}

	if(_block != NULL) delete [] _block;
	_block = new UInt32[rank];
	if(_block == NULL){
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for block buffer!");
		_free();
		EXCEPTION_THROW();
	}
}

//=======================Constructors and destructors===========================
Selection::Selection(){
	_stride = NULL;
	_offset = NULL;
	_block = NULL;
	_count = NULL;
	_rank = 0;
}

Selection::Selection(const Selection &o){
	EXCEPTION_SETUP("Selection::Selection(const Selection &o)");
	//initialize member variables
	_stride = NULL;
	_offset = NULL;
	_block = NULL;
	_count = NULL;
	_rank = 0;

	try{
		_allocate(o._rank);
	}catch(MemoryAllocationError &e){
		EXCEPTION_INIT(MemoryAllocationError,"Memory allocation for Selection object failed!");
		EXCEPTION_THROW();
	}
	_rank = o._rank;
}

Selection::~Selection(){
	_free();
	_rank = 0;
}

//================Methods for manipulating the rank of the selection============

UInt32 Selection::getRank() const{
	return _rank;
}

void Selection::setRank(UInt32 r){
	EXCEPTION_SETUP("void Selection::setRank(UInt32 r)");

	if(_rank != r){
		try{
			_allocate(r);
		}catch(MemoryAllocationError &e){
			EXCEPTION_INIT(MemoryAllocationError,"Memory allocation for Selection object failed!");
			EXCEPTION_THROW();
		}
		_rank = r;
	}
}

//================Methods for manipulating the offset array=====================
void Selection::incrementOffset(UInt32 i){
	EXCEPTION_SETUP("void Selection::incrementOffset(UInt32 i)");

	if(i>=_rank){
		EXCEPTION_INIT(IndexError,"Offset index exceeds selection rank!");
		EXCEPTION_THROW();
	}

	_offset[i]++;
}

void Selection::decrementOffset(UInt32 i){
	EXCEPTION_SETUP("void Selection::decrementOffset(UInt32 i)");

	if(i>=_rank){
		EXCEPTION_INIT(IndexError,"Offset index exceeds selection rank!");
		EXCEPTION_THROW();
	}

	if(_offset[i] == 0){
		EXCEPTION_INIT(RangeError,"Decrement would yield negative numbers!");
		EXCEPTION_THROW();
	}

	_offset[i]--;
}

void Selection::setOffset(UInt32 i,UInt32 v){
	EXCEPTION_SETUP("void Selection::setOffset(UInt32 i,UInt32 v)");

	if(i>=_rank){
		EXCEPTION_INIT(IndexError,"Offset index exceeds selection rank!");
		EXCEPTION_THROW();
	}

	_offset[i] = v;
}

UInt32 Selection::getOffset(UInt32 i) const{
	EXCEPTION_SETUP("UInt32 Selection::getOffset(UInt32 i)");
	if(i>=_rank){
		EXCEPTION_INIT(IndexError,"Offset index exceeds selection rank!");
		EXCEPTION_THROW();
	}

	return _offset[i];
}

//================Methods for manipulating the stride array=====================

void Selection::incrementStride(UInt32 i){
	EXCEPTION_SETUP("void Selection::incrementStride(UInt32 i)");
	if(i>=_rank){
		EXCEPTION_INIT(IndexError,"Stride index exceeds selection rank!");
		EXCEPTION_THROW();
	}
	_stride[i]++;
}

void Selection::decrementStride(UInt32 i){
	EXCEPTION_SETUP("void Selection::decrementStride(UInt32 i)");
	if(i>=_rank){
		EXCEPTION_INIT(IndexError,"Stride index exceeds selection rank!");
		EXCEPTION_THROW();
	}

	if(_stride[i]==0){
		EXCEPTION_INIT(RangeError,"Decrement would yield negative stride value!");
		EXCEPTION_THROW();
	}
	_stride[i]--;
}

void Selection::setStride(UInt32 i,UInt32 v){
	EXCEPTION_SETUP("void Selection::setStride(UInt32 i,UInt32 v)");
	if(i>=_rank){
		EXCEPTION_INIT(IndexError,"Stride index exceeds selection rank!");
		EXCEPTION_THROW();
	}
	_stride[i] = v;
}

UInt32 Selection::getStride(UInt32 i) const{
	EXCEPTION_SETUP("UInt32 Selection::getStride(UInt32 i) const");
	if(i>=_rank){
		EXCEPTION_INIT(IndexError,"Stride index exceeds selection rank!");
		EXCEPTION_THROW();
	}

	return _stride[i];
}

//================Methods for manipulating the count array======================

void Selection::incrementCount(UInt32 i){
	EXCEPTION_SETUP("void Selection::incrementCount(UInt32 i)");
	if(i>=_rank){
		EXCEPTION_INIT(IndexError,"Count index exceeds selection rank!");
		EXCEPTION_THROW();
	}

	_count[i]++;
}

void Selection::decrementCount(UInt32 i){
	EXCEPTION_SETUP("void Selection::decrementCount(UInt32 i)");
	if(i>=_rank){
		EXCEPTION_INIT(IndexError,"Count index exceeds selection rank!");
		EXCEPTION_THROW();
	}

	if(_count[i] == 0){
		EXCEPTION_INIT(RangeError,"Decrement would yield a negative count!");
		EXCEPTION_THROW();
	}
	_count[i]--;
}

void Selection::setCount(UInt32 i,UInt32 v){
	EXCEPTION_SETUP("void Selection::setCount(UInt32 i,UInt32 v)");
	if(i>=_rank){
		EXCEPTION_INIT(IndexError,"Count index exceeds selection rank!");
		EXCEPTION_THROW();
	}
	_count[i] = v;
}

UInt32 Selection::getCount(UInt32 i) const{
	EXCEPTION_SETUP("UInt32 Selection::getCount(UInt32 i) const");
	if(i>=_rank){
		EXCEPTION_INIT(IndexError,"Count index exceeds selection rank!");
		EXCEPTION_THROW();
	}

	return _count[i];
}

//================Methods for manipulating the block array======================
void Selection::incrementBlock(UInt32 i){
	EXCEPTION_SETUP("void Selection::incrementBlock(UInt32 i)");
	if(i>=_rank){
		EXCEPTION_INIT(IndexError,"Block index exceeds selection rank!");
		EXCEPTION_THROW();
	}
	_block[i]++;
}

void Selection::decrementBlock(UInt32 i){
	EXCEPTION_SETUP("void Selection::decrementBlock(UInt32 i)");
	if(i>=_rank){
		EXCEPTION_INIT(IndexError,"Block index exceeds selection rank!");
		EXCEPTION_THROW();
	}
	if(_block[i] == 0){
		EXCEPTION_INIT(RangeError,"Decrement would yield a negative block value!");
		EXCEPTION_THROW();
	}

	_block[i]--;
}

void Selection::setBlock(UInt32 i,UInt32 v){
	EXCEPTION_SETUP("void Selection::setBlock(UInt32 i,UInt32 v)");
	if(i>=_rank){
		EXCEPTION_INIT(IndexError,"Block index exceeds selection rank!");
		EXCEPTION_THROW();
	}
	_block[i] = v;
}

UInt32 Selection::getBlock(UInt32 i) const{
	EXCEPTION_SETUP("UInt32 Selection::getBlock(UInt32 i) const");
	if(i>=_rank){
		EXCEPTION_INIT(IndexError,"Block index exceeds selection rank!");
		EXCEPTION_THROW();
	}
	return _block[i];
}

//end of namespace
}
}
