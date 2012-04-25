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
#define __TIFFIFDENTRY_HPP__


#include <iostream>
#include <fstream>
#include <map>

#include "../../Types.hpp"

using namespace pni::utils;

namespace pni{
namespace io{
namespace tiff{
    
    enum class IFDEntryTypeID { BYTE, ASCII,SHORT,LONG,RATIONAL,SBYTE,UNDEFINED,
                                  SSHORT,SLONG,SRATIONAL,FLOAT,DOUBLE};


    class IFDEntry
    {
        private:
            UInt16 _tag;            //!< ID of the entry
            IFDEntryTypeID _tid;   //!< type id of the entry
            size_t _size;          //!< number of elements of the entry
            std::streampos _data;  //!< marks data position

        public:
            //=============constructors and destructor====================
            //! default constructor
            IFDEntry();

            //! copy constructor
            IFDEntry(const IFDEntry &e);

            //! move constructor
            IFDEntry(IFDEntry &&e);

            /*! \brief standard constructor

            Standard constructor to create a IFDEntry.
            \param tag TIFF tag of the entry
            \param tid type ID of the entry
            \param size number of elements stored in this entry
            \param data starting position of data in the stream
            */
            IFDEntry(UInt16 tag,IFDEntryTypeID tid,size_t size,std::streampos
                    data);

            //! destructor
            ~IFDEntry();

            //=====================assignment operators====================
            //! copy assignment operator
            IFDEntry &operator=(const IFDEntry &e);

            //! move assignment operator
            IFDEntry &operator=(IFDEntry &&e);

            //===============static methods================================
            static IFDEntry create_from_stream(std::ifstream &stream);

            //==================class methods==============================
            /*! \brief number of elements

            Returns the number of elements that make up the entry.
            \return number of elements
            */
            size_t nelements() const;

            String name() const;

            TypeID type_id() const;

            friend std::ostream &operator<<(std::ostream &o,const IFDEntry &e);

    };



//end of namespace
}
}
}


#endif
