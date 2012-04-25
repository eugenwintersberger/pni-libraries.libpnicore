/*
 * Declaration of class CBFReader
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
 * Definition of class TIFFIFDEntry
 *
 * Created on: Apr 24, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */


#ifndef __TIFFIFDENTRY_HPP__
#ifndef __TIFFIFDENTRY_HPP__


#include <iostream>
#include <fstream>

#include "../Types.hpp"

namespace pni{
    namespace utils{
    
        class TIFFIFDEntry
        {
            private:
                UInt16 _id;            //!< ID of the entry
                std::streampos _start; //!< marks the start position of the entry

            public:
                //=============constructors and destructor====================
                //! default constructor
                TIFFIFDEntry();

                //! copy constructor
                TIFFIFDEntry(const TIFFIFDEntry &e);

                //! move constructor
                TIFFIFDEntry(TIFFIFDEntry &&e);

                //! standard constructor
                TIFFIFDEntry(UInt16 id,const std::streampos &start);

                //! destructor
                ~TIFFIFDEntry();

                //=====================assignment operators====================
                //! copy assignment operator
                TIFFIFDEntry &operator=(const TIFFIFDEntry &e);

                //! move assignment operator
                TIFFIFDEntry &operator=(TIFFIFDEntry &&e);

                //==================class methods==============================
                /*! \brief number of elements

                Returns the number of elements that make up the entry.
                \return number of elements
                */
                size_t nelements() const;

                String name() const;

                template<typename T> T read(size_t i,std::ifstream &stream);


        };


    //end of namespace
    }
}


#endif
