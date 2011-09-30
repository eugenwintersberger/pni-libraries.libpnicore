/*
 * Implementation of class CBFBinStreamReader
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
 * Implementation of class CBFBinStreamReader.
 *
 * Created on: Apr 19, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#include "CBFBinStreamReader.hpp"

namespace pni{
namespace utils{


CBFBinStreamReader::CBFBinStreamReader(){
	nelements_ = 0;
	elemsize_ = 0;
	_stream = NULL;
	_buffer = NULL;
}

CBFBinStreamReader::CBFBinStreamReader(unsigned long n){
	nelements_ = n;
	elemsize_ = 0;
	_stream = NULL;
	_buffer = NULL;
}

CBFBinStreamReader::~CBFBinStreamReader(){
	nelements_ = 0;
	elemsize_ = 0;
	_stream = NULL;
	_buffer = NULL;
}

//end of namespaces
}
}
