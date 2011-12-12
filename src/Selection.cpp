/*
 * Implementation class Selection
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
 * The Selection object provides facilities to select data from an Array<T>
 * object.
 *
 * Created on: Apr 19, 2011
 *     Author: Eugen Wintersberger
 *
 */

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

void Selection::_compute_trank(){
	_trank = 0;
	if(_rank != 0){
		for(UInt32 i=0;i<_rank;i++) if(_count[i] != 1) _trank++;
	}else{
		_trank = 0;
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
	}catch(MemoryAllocationError &error){
		EXCEPTION_INIT(MemoryAllocationError,"Memory allocation for Selection object failed!");
		EXCEPTION_THROW();
	}
	_rank = o._rank;
	//copy data
	for(UInt32 i=0;i<_rank;i++){
		_stride[i] = o._stride[i];
		_offset[i] = o._offset[i];
		_block[i] = o._block[i];
		_count[i] = o._count[i];
	}
	//compute the rank of the target
	_compute_trank();
}

Selection::Selection(const Shape &s){
	EXCEPTION_SETUP("Selection::Selection(const ArrayShape &s)");

	_stride = NULL;
	_offset = NULL;
	_block = NULL;
	_count = NULL;
	_rank = 0;

	try{
		_allocate(s.rank());
	}catch(MemoryAllocationError &error){
		EXCEPTION_INIT(MemoryAllocationError,"Memory allocation for Selection object failed!");
		EXCEPTION_THROW();
	}

	_rank = s.rank();

	for(UInt32 i=0;i<s.rank();i++){
		_count[i] = s.dim(i);
	}
}

Selection::~Selection(){
	_free();
	_rank = 0;
	_trank = 0;
}

//========================selections and shapes=================================
void Selection::getShape(Shape &s) const {
	EXCEPTION_SETUP("void Selection::getShape(ArrayShape &s) const");
	UInt32 rank=0;

	try{
		s.rank(_trank);
	}catch(MemoryAllocationError &error){
		EXCEPTION_INIT(MemoryAllocationError,"Memory allocation for ArrayShape object failed!");
		EXCEPTION_THROW();
	}


	for(UInt32 i=0;i<_rank;i++){
		if(_count[i] != 1){
			s.dim(rank,_count[i]);
			rank++;
		}
	}
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
		}catch(MemoryAllocationError &error){
			EXCEPTION_INIT(MemoryAllocationError,"Memory allocation for Selection object failed!");
			EXCEPTION_THROW();
		}
		_rank = r;
	}
}

UInt32 Selection::getTargetRank() const {
	return _trank;
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

void Selection::getSourceIndex(const Index &index,Index &sindex) const{
	EXCEPTION_SETUP("void Selection::getSourceIndex(const Index &i, Index &si)");

	if(index.rank()!=sindex.rank()){
		EXCEPTION_INIT(ShapeMissmatchError,"Selection index and source index have different rank!");
		EXCEPTION_THROW();
	}

	for(UInt32 i=0;i<index.rank();i++){
		sindex[i] = index[i]+getOffset(i);
	}
}

//end of namespace
}
}
