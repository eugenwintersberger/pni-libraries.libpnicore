/*
 * Declaration of TIFF related exceptions
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
 * Declaration of exceptions regarding the TIFF classes.
 *
 * Created on: Sep 26, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#include "../Exceptions.hpp"

#ifndef TIFFEXCEPTIONS_HPP_
#define TIFFEXCEPTIONS_HPP_

namespace pni{
namespace utils{

//! \ingroup error_classes
//! \brief error during TIFF reading

//! This exception is thrown in cases where errors occur during reading
//! TIFF files.
class TIFFReadError:public Exception{
public:
	//! default constructor
	TIFFReadError():Exception("TIFFReadError"){}
	//! constructor

	//! \param i signature of the exception issuer
	//! \param d description of the error
	TIFFReadError(const String &i,const String &d):Exception("TIFFReadError",i,d){}
	//! destructor
	virtual ~TIFFReadError() throw() {}

	//! output operator
	friend std::ostream &operator<<(std::ostream &o,const TIFFReadError &e);
};

//end of namespace
}
}



#endif /* TIFFEXCEPTIONS_HPP_ */
