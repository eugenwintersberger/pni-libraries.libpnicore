/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpnicore.
 *
 * libpnicore is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpnicore is distributed in the hope that it will be useful,
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
namespace core{

    //=====================implementation of helper functions===================

    //-------------------------------------------------------------------------
    void check_index(size_t index,size_t maxindex,const ExceptionRecord &i)
    {
        if(index>=maxindex)
        {
            std::stringstream ss;
            ss<<"Index ("<<index<<") exceeds maximum value ("<<maxindex<<")!";
            throw IndexError(i,ss.str());
        }
    }

//end of namespace
}
}
