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
 * along with lipniutils.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * 
 * Exception related utility functions - definition.
 *
 * Created on: May 23, 2012
 *     Author: Eugen Wintersberger
 *
 */

#include "ExceptionUtils.hpp"

namespace pni{
namespace utils{

    //=====================implementation of helper functions===================

    //-------------------------------------------------------------------------
    void check_index(size_t index,size_t maxindex,const String &i)
    {
        if(index>=maxindex)
        {
            IndexError error;
            std::stringstream ss;
            ss<<"Index ("<<i<<") exceeds maximum value ("<<maxindex<<")!";
            error.issuer(i);
            error.description(ss.str());
            throw error;
        }
    }

//end of namespace
}
}
