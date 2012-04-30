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
 * SpreadsheetReader class implementation
 *
 * Created on: Apr 30, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */
            

#include "SpreadsheetReader.hpp"

namespace pni{
namespace io{

    //============constructors and destructor==================================
    //default constructor implementation
    SpreadsheetReader::SpreadsheetReader():DataReader(){}

    //-------------------------------------------------------------------------
    //move constructor implementation
    SpreadsheetReader::SpreadsheetReader(SpreadsheetReader &&o):
        DataReader(std::move(o))
    {}

    //-------------------------------------------------------------------------
    //standard constructor implementation
    SpreadsheetReader::SpreadsheetReader(const String &n):
        DataReader(n)
    {}

    //-------------------------------------------------------------------------
    //destructor implementation
    SpreadsheetReader::~SpreadsheetReader()
    {}

    //=====================assignment operators================================
    //move assignment operator implementation
    SpreadsheetReader &SpreadsheetReader::operator=(SpreadsheetReader &&r)
    {
        if(this == &r) return *this;

        DataReader::operator=(std::move(r));
        return *this;
    }

//end of namespace
}}
