/*
 * Implementation of class Index
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
 * Implementation of class Index which represents an index vector for accessing
 * data in an array object.
 *
 * Created on: Aug 31, 2011
 *     Author: Eugen Wintersberger
 *
 */

#include <limits>
#include "Index.hpp"
#include "Exceptions.hpp"

namespace pni {
namespace utils {


//=======================Constructors and destructors==========================
//implementation of the default constructor
Index::Index(){
}

//------------------------------------------------------------------------------
//implementation of the standard constructor
Index::Index(size_t rank){
	EXCEPTION_SETUP("Index::Index(size_t rank)");

	_index.allocate(rank);

	for(size_t i=0;i<rank;i++) _index[i] = 0;
}

//------------------------------------------------------------------------------
//implementation of the copy constructor
Index::Index(const Index &o){
	EXCEPTION_SETUP("Index::Index(const Index &o)");

	_index = o._index;
}

//------------------------------------------------------------------------------
//implementation of the move constructor
Index::Index(Index &&o){
	_index = std::move(o._index);
}

//------------------------------------------------------------------------------
//implementation of the destructor
Index::~Index(){
	_index.free();
}


//============Implementation of the assignment operators========================
//implementation of copy assignment
Index &Index::operator=(const Index &o){
	EXCEPTION_SETUP("Index &Index::operator=(const Index &o)");

	if( this != &o ){
		_index = o._index;
	}

	return *this;
}

//-----------------------------------------------------------------------------
//implementation of move assignment
Index &Index::operator=(Index &&o){
	if(this != &o){
		_index = std::move(o._index);
	}

	return *this;
}

//======================Implementation of the access operators==================
//implementation of read only access
size_t Index::operator[](size_t index) const{
	return _index[index];
}

//------------------------------------------------------------------------------
//implementation of read/write access
size_t &Index::operator[](size_t index){
	return _index[index];
}


//================Methods modifying the rank of the Index object===============
//implementation of set rank
void Index::rank(size_t rank){

	_index.allocate(rank);
	//initialize the index buffer
	for(size_t i=0;i<rank;i++) _index[i] = 0;
}

//------------------------------------------------------------------------------
//implementation of get rank
size_t Index::rank() const{
	return _index.size();
}

//============Methods for modifying and accessing index values==================
//implementation of get an index
size_t Index::get(size_t index) const{
	return _index.at(index);
}

//------------------------------------------------------------------------------
//implementation of set an index
void Index::set(size_t index,size_t value){
	_index.at(index) = value;
}

//------------------------------------------------------------------------------
//implementation of index increment
void Index::inc(size_t index){
	EXCEPTION_SETUP("void Index::inc(size_t index)");

	//throw an exception in cases where the increment would exceed
	//the numeric range of size_t
	if(get(index) == std::numeric_limits<size_t>::max()){
		EXCEPTION_INIT(RangeError,"Index exceeds numeric limits!");
		EXCEPTION_THROW();
	}

	_index.at(index)++;
}

//------------------------------------------------------------------------------
//implementation of index decrement
void Index::dec(size_t index){
	EXCEPTION_SETUP("void Index::dec(size_t index)");

	//throw an exception if the decrement would lead to a number smaller
	//than zero (which is not possible for an unsigned type as size_t)
	//and thus causing an overflow
	if((*this)[index]==0){
		EXCEPTION_INIT(RangeError,"Index becomes < 0!");
		EXCEPTION_THROW();
	}

    _index.at(index)--;
}

//=================Implementation of output operators===========================
std::ostream &operator<<(std::ostream &o,const Index &index){
	o<<"Index ("<<index.rank()<<"): ";

	for(size_t i=0;i<index.rank();i++) o<<index[i]<<" ";

	return o;
}

//=================Implementation of comparison operators=======================
//implementation of equality check
bool operator==(const Index &i1,const Index &i2){
	if(i1.rank() != i2.rank()) return false;

	for(size_t i=0;i<i1.rank();i++){
		if(i1[i] != i2[i]) return false;
	}

	return true;
}

//------------------------------------------------------------------------------
//implementation of in-equality
bool operator!=(const Index &i1,const Index &i2){
	if(i1 == i2) return false;
	return true;
}

//end of namespace
}
}
