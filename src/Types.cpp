/*
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
 * implementation of operators and other functions related to types.
 *
 * Created on: Apr 25, 2012
 *     Author: Eugen Wintersberger
 *
 */

#include "Types.hpp"

namespace pni{
namespace utils{

    //! output operator for TypeID
    std::ostream &operator<<(std::ostream &o,const TypeID &tid)
    {
        if(tid==TypeID::NONE) {o<<"NONE"; return o;}
        if(tid==TypeID::INT8) {o<<"INT8"; return o;}
	    if(tid==TypeID::UINT8) {o<<"UINT8"; return o;}
		if(tid==TypeID::INT16) {o<<"INT16"; return o;}
		if(tid==TypeID::UINT16) {o<<"UINT16"; return o;}
		if(tid==TypeID::INT32) {o<<"INT32"; return o;}
		if(tid==TypeID::UINT32) {o<<"UINT32"; return o;}
		if(tid==TypeID::INT64) {o<<"INT64"; return o;}
		if(tid==TypeID::UINT64) {o<<"UINT64"; return o;}
	    if(tid==TypeID::FLOAT32) {o<<"FLOAT32"; return o;}
	    if(tid==TypeID::FLOAT64) {o<<"FLOAT64"; return o;}
	    if(tid==TypeID::FLOAT128) {o<<"FLOAT128"; return o;}
	    if(tid==TypeID::COMPLEX32) {o<<"COMPLEX32"; return o;}
	    if(tid==TypeID::COMPLEX64) {o<<"COMPLEX64"; return o;}
	    if(tid==TypeID::COMPLEX128) {o<<"COMPLEX128"; return o;}
	    if(tid==TypeID::STRING) {o<<"STRING"; return o;}
	    if(tid==TypeID::BINARY) {o<<"BINARY"; return o;}
	    if(tid==TypeID::BOOLEAN) {o<<"BOOLEAN"; return o;}
    }
//end of namespace 
}
}
