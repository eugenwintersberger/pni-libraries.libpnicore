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
 * Implementation of class TIFFIFDEntry
 *
 * Created on: Apr 24, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */


#include "TIFFStandard.hpp"


namespace pni{
    namespace utils{



        //==================constructors and destructor========================
        //implementation of the  default constructor
        TIFFIFDEntry::TIFFIFDEntry():
            _id(0),
            _start(0)
        {}

        //---------------------------------------------------------------------
        //implementation of the copy constructor
        TIFFIFDEntry::TIFFIFDEntry(const TIFFIFDEntry &e):
            _id(e._id),
            _start(e._start)
        {}

        //---------------------------------------------------------------------
        //implementation of the  move constructor
        TIFFIFDEntry::TIFFIFDEntry(TIFFIFDEntry &&e)
            _id(std::move(e._id)),
            _start(std::move(e._start))
        {}

        //---------------------------------------------------------------------
        //implementation of the standard constructor
        TIFFIFDEntry::TIFFIFDEntry(UInt16 id,const std::streampos &start):
            _id(id),
            _start(start)
        { }

        //---------------------------------------------------------------------
        //implementation of the destructor
        TIFFIFDEntry::~TIFFIFDEntry()
        {}

        //=====================assignment operators============================
        //implementation of the copy assignment operator
        TIFFIFDEntry &TIFFIFDEntry::operator=(const TIFFIFDEntry &e)
        {
            if(this == &e) return *this;

            _id = e._id;
            _start = e._start;
            return *this;
        }

        //---------------------------------------------------------------------
        //implementation of the move assignment operator
        TIFFIFDEntry &TIFFIFDEntry::operator=(TIFFIFDEntry &&e)
        {
            if(this == &e) return *this;
            _id = std::move(e._id);
            _start = std::move(e._start);
            return *this;
        }

        //=======================class methods=================================
        //implementation of nelements
        size_t nelements() const;

        //----------------------------------------------------------------------
        String TIFFIFDEntry::name() const
        {
           try{
               return TIFFTagNameMap[_id];
           }catch(...){
               return String("unknown");
           }
        }

        //----------------------------------------------------------------------
        template<typename T> T read(size_t i,std::ifstream &stream);

    //end of namespace
    }
}
