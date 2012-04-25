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
            size_t size() const;

            String name() const;

            TypeID type_id() const;

            template<typename T> std::vector<T> value(std::ifstream &stream);

            friend std::ostream &operator<<(std::ostream &o,const IFDEntry &e);

    };

    template<typename T> std::vector<T> IFDEntry::value(std::ifstream &stream)
    {
        std::vector<T> result;
        //now we have to walk through all types available in TIFF - not very
        //nice but we have no other choice at runtime
        if(this->_tid == IFDEntryTypeID::BYTE)
            result = this->_read_entry<T,IFDEntryTypeID::BYTE>();
        if(this->_tid == IFDEntryTypeID::ASCII)
            result =  this->_read_entry<T,IFDEntryTypeID::ASCII>();
        if(this->_tid == IFDEntryTypeID::SHORT)
            result = this->_read_entry<T,IFDEntryTypeID::SHORT>();
        if(this->_tid == IFDEntryTypeID::LONG)
            result = this->_read_entry<T,IFDEntryTypeID::LONG>();
        if(this->_tid == IFDEntryTypeID::RATIONAL)
            result = this->_read_entry<T,IFDEntryTypeID::RATIONAL>();
        if(this->_tid == IFDEntryTypeID::SBYTE)
            result = this->_read_entry<T,IFDEntryTypeID::SBYTE>();
        if(this-> tid == IFDEntryTypeID::SSHORT)
            result = this->_read_entry<T,IFDEntryTypeID::SSHORT>();
        if(this->_tid == IFDEntryTypeID::SLONG)
            result = this->_read_entry<T,IFDEntryTypeID::SLONG>();
        if(this->_tid

        






        //in the very end we have to reset the stream to its original position
        stream.seekg(orig_pos,std::ios::beg);

    }



//end of namespace
}
}
}


#endif
