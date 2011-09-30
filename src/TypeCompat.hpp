/*
 * Declaration of class template TypeCompat
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
 * Template provides information if tow types are assignable and if they can
 * be used in unary arithmetic operations.
 *
 * Created on: Sep 9, 2011
 *     Author: Eugen Wintersberger
 *
 */

/*
 * TypeCompat.hpp
 *
 *  Created on: Sep 8, 2011
 *      Author: eugen
 */

#ifndef TYPECOMPAT_HPP_
#define TYPECOMPAT_HPP_

#include "PNITypes.hpp"

namespace pni{
namespace utils{


template<typename A,typename B> class TypeCompat{
public:
	static const bool isAssignable = true;   //can be assigned
	static const bool isUnaryACompat = true; //can be used for unary arithmetic operations
};

#define SET_TYPE_COMPATABILITY(A,B,ASS,UAC)\
	template<> class TypeCompat<A,B>{\
	public:\
		static const bool isAssignable = ASS;\
		static const bool isUnaryACompat = UAC;\
};

//you can never assign a Float or Complex to an integer

SET_TYPE_COMPATABILITY(Int8,Float32,false,false);
SET_TYPE_COMPATABILITY(Int8,Float64,false,false);
SET_TYPE_COMPATABILITY(Int8,Float128,false,false);
SET_TYPE_COMPATABILITY(Int8,Complex32,false,false);
SET_TYPE_COMPATABILITY(Int8,Complex64,false,false);
SET_TYPE_COMPATABILITY(Int8,Complex128,false,false);

SET_TYPE_COMPATABILITY(UInt8,Float32,false,false);
SET_TYPE_COMPATABILITY(UInt8,Float64,false,false);
SET_TYPE_COMPATABILITY(UInt8,Float128,false,false);
SET_TYPE_COMPATABILITY(UInt8,Complex32,false,false);
SET_TYPE_COMPATABILITY(UInt8,Complex64,false,false);
SET_TYPE_COMPATABILITY(UInt8,Complex128,false,false);

SET_TYPE_COMPATABILITY(Int16,Float32,false,false);
SET_TYPE_COMPATABILITY(Int16,Float64,false,false);
SET_TYPE_COMPATABILITY(Int16,Float128,false,false);
SET_TYPE_COMPATABILITY(Int16,Complex32,false,false);
SET_TYPE_COMPATABILITY(Int16,Complex64,false,false);
SET_TYPE_COMPATABILITY(Int16,Complex128,false,false);

SET_TYPE_COMPATABILITY(UInt16,Float32,false,false);
SET_TYPE_COMPATABILITY(UInt16,Float64,false,false);
SET_TYPE_COMPATABILITY(UInt16,Float128,false,false);
SET_TYPE_COMPATABILITY(UInt16,Complex32,false,false);
SET_TYPE_COMPATABILITY(UInt16,Complex64,false,false);
SET_TYPE_COMPATABILITY(UInt16,Complex128,false,false);

SET_TYPE_COMPATABILITY(Int32,Float32,false,false);
SET_TYPE_COMPATABILITY(Int32,Float64,false,false);
SET_TYPE_COMPATABILITY(Int32,Float128,false,false);
SET_TYPE_COMPATABILITY(Int32,Complex32,false,false);
SET_TYPE_COMPATABILITY(Int32,Complex64,false,false);
SET_TYPE_COMPATABILITY(Int32,Complex128,false,false);

SET_TYPE_COMPATABILITY(UInt32,Float32,false,false);
SET_TYPE_COMPATABILITY(UInt32,Float64,false,false);
SET_TYPE_COMPATABILITY(UInt32,Float128,false,false);
SET_TYPE_COMPATABILITY(UInt32,Complex32,false,false);
SET_TYPE_COMPATABILITY(UInt32,Complex64,false,false);
SET_TYPE_COMPATABILITY(UInt32,Complex128,false,false);

SET_TYPE_COMPATABILITY(Int64,Float32,false,false);
SET_TYPE_COMPATABILITY(Int64,Float64,false,false);
SET_TYPE_COMPATABILITY(Int64,Float128,false,false);
SET_TYPE_COMPATABILITY(Int64,Complex32,false,false);
SET_TYPE_COMPATABILITY(Int64,Complex64,false,false);
SET_TYPE_COMPATABILITY(Int64,Complex128,false,false);

SET_TYPE_COMPATABILITY(UInt64,Float32,false,false);
SET_TYPE_COMPATABILITY(UInt64,Float64,false,false);
SET_TYPE_COMPATABILITY(UInt64,Float128,false,false);
SET_TYPE_COMPATABILITY(UInt64,Complex32,false,false);
SET_TYPE_COMPATABILITY(UInt64,Complex64,false,false);
SET_TYPE_COMPATABILITY(UInt64,Complex128,false,false);

SET_TYPE_COMPATABILITY(Float32,Complex32,false,false);
SET_TYPE_COMPATABILITY(Float32,Complex64,false,false);
SET_TYPE_COMPATABILITY(Float32,Complex128,false,false);

SET_TYPE_COMPATABILITY(Float64,Complex32,false,false);
SET_TYPE_COMPATABILITY(Float64,Complex64,false,false);
SET_TYPE_COMPATABILITY(Float64,Complex128,false,false);

SET_TYPE_COMPATABILITY(Float128,Complex32,false,false);
SET_TYPE_COMPATABILITY(Float128,Complex64,false,false);
SET_TYPE_COMPATABILITY(Float128,Complex128,false,false);

//end of namespace
}
}


#endif /* TYPECOMPAT_HPP_ */
