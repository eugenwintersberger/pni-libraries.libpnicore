/*
 * Index.cpp
 *
 *  Created on: Aug 31, 2011
 *      Author: eugen
 */

#include "Index.hpp"
#include "Exceptions.hpp"

namespace pni {
namespace utils {


//=======================Constructors and destructors==========================
Index::Index(){
	_rank = 0;
	_index = NULL;
}

Index::Index(UInt32 rank){
	EXCEPTION_SETUP("Index::Index(UInt32 rank)");
	_index = NULL;

	_index = new UInt32[rank];
	if(_index == NULL){
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for index buffer!");
		EXCEPTION_THROW();
	}

	_rank = rank;
}

Index::Index(const Index &o){
	EXCEPTION_SETUP("Index::Index(const Index &o)");

	if(o._rank != 0){
		_index = NULL;
		_index = new UInt32[o._rank];
		if(_index == NULL){
			EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for index buffer!");
			EXCEPTION_THROW();
		}
	}else{
		_index = NULL;
		_rank = 0;
	}
}

Index::~Index(){
	if(_index != NULL) delete [] _index;
}


//============================ Operators =======================================
Index &Index::operator=(const Index &o){
	EXCEPTION_SETUP("Index &Index::operator=(const Index &o)");

	if( this != &o ){
		if(o._rank != _rank){
			//if indices have different rank we need reallocation
			if( _index != NULL) delete [] _index;

			if(o._rank != 0){
				_index = new UInt32[o._rank];
				if(_index == NULL){
					EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for index buffer!");
					EXCEPTION_THROW();
				}
				_rank = o._rank;

			}else{
				_index = NULL;
				_rank = 0;
				return *this;
			}

		}

		for(UInt32 i=0; i < _rank; i++) _index[i] = o._index[i];
	}

	return *this;
}

UInt32 Index::operator[](UInt32 index) const{
	EXCEPTION_SETUP("UInt32 Index::operator[](UInt32 index) const");

	if(index >= _rank){
		EXCEPTION_INIT(IndexError,"Index index exceeds index rank!");
		EXCEPTION_THROW();
	}

	return _index[index];
}

UInt32 &Index::operator[](UInt32 index){
	EXCEPTION_SETUP("UInt32 &Index::operator[](UInt32 index)");

	if(index >= _rank){
		EXCEPTION_INIT(IndexError,"Index index exceeds index rank!");
		EXCEPTION_THROW();
	}

	return _index[index];
}


//================Methods modifying the rank of the Index object===============
void Index::setRank(UInt32 rank){
	EXCEPTION_SETUP("void Index::setRank(UInt32 rank)");

	if(_rank != rank){
		if(_index != NULL) delete [] _index;

		_index = new UInt32[rank];
		if(_index != NULL){
			EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for index buffer!");
			EXCEPTION_THROW();
		}
		_rank = rank;
	}
	//initialize the index buffer
	for(UInt32 i=0;i<_rank;i++) _index[i] = 0;
}

UInt32 Index::getRank() const{
	return _rank;
}

//============Methods for modifying and accessing index values==================
UInt32 Index::getIndex(UInt32 index) const{
	EXCEPTION_SETUP("UInt32 Index::getIndex(UInt32 index) const");

	if(index >= _rank){
		EXCEPTION_INIT(IndexError,"Index index exceeds index rank!");
		EXCEPTION_THROW();
	}

	return _index[index];
}

void Index::setIndex(UInt32 index,UInt32 value){
	EXCEPTION_SETUP("void Index::setIndex(UInt32 index,UInt32 value)");

	if(index >= _rank){
		EXCEPTION_INIT(IndexError,"Index index exceeds index rank!");
		EXCEPTION_THROW();
	}

	_index[index] = value;
}

void Index::increment(UInt32 index){
	EXCEPTION_SETUP("void Index::increment(UInt32 index)");

	try{
		(*this)[index]++;
	}catch(IndexError &e){
		EXCEPTION_INIT(IndexError,e.getDescription());
		EXCEPTION_THROW();
	}
}

void Index::decrement(UInt32 index){
	EXCEPTION_SETUP("void Index::decrement(UInt32 index)");

	try{
		if((*this)[index] == 0){
			EXCEPTION_INIT(RangeError,"Index value would become negative!");
			EXCEPTION_THROW();
		}

		(*this)[index]--;
	}catch(IndexError &e){
		EXCEPTION_INIT(IndexError,e.getDescription());
		EXCEPTION_THROW();
	}

}

//end of namespace
}
}
