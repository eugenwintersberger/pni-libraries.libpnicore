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
 * Class Reader is the base class for all readers which retrieve data from
 * files and other sources.
 *
 * Created on: Apr 23, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */


#include "ImageReader.hpp"

namespace pni{
    namespace utils{

        //============implementation of constructors==========================
        //implementation of the default constructor
        ImageReader::ImageReader():DataReader() {}

        //--------------------------------------------------------------------
        //implementation of the move constructor
        ImageReader::ImageReader(ImageReader &&i):
            DataReader(std::move(i))
        {}

        //---------------------------------------------------------------------
        //implementation of the standard constructor
        ImageReader::ImageReader(const String &fname):
            DataReader(fname)
        {}

        //---------------------------------------------------------------------
        //implementation of the destructor
        ImageReader::~ImageReader() {} 

        //===========implementation of assignment operators====================
        //implementation of move assignment
        ImageReader &ImageReader::operator=(ImageReader &&i)
        {
            if(this == &i) return *this;

            DataReader::operator=(std::move(i));
            return *this;
        }

    //end of namespace
    }
}
