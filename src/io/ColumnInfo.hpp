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
 * ColumnInfo class definition
 *
 * Created on: Apr 30, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#ifndef __COLUMNINFO_HPP__
#define __COLUMNINFO_HPP__


#include "../Types.hpp"
#include "../Shape.hpp"


using namespace pni::utils;

namespace pni{
namespace io{

    /*! \ingroup io_classes
    \brief Spreadsheet column information

    This class holds the basic information about a column stored in a
    spreadsheet. This includes the following parameters: the name of the column,
    its TypeID and the shape of each cell. The latter parameter allows even the
    storage of multidimensional data in such a structure.
    */
    class ColumnInfo
    {
        private:
            String _name; //!< name of the columne
            TypeID _tid;  //!< type ID of column type
            Shape  _shape; //!< shape of column data
        public:
            //====================constructors and destructor===================
            //! default constructor
            ColumnInfo();

            //! copy constructor
            ColumnInfo(const ColumnInfo &ci);

            //! move constructor
            ColumnInfo(ColumnInfo &&ci);

            //! standard constructor
            ColumnInfo(const String &n,TypeID tid,const Shape &s);

            //! destructor
            ~ColumnInfo();

            //===================assignment operators==========================
            //! copy assignment operator
            ColumnInfo &operator=(const ColumnInfo &ci);

            //! move assignment operator
            ColumnInfo &operator=(ColumnInfo &&ci);

            //======================public member methods======================
            /*! \brief get cell shape

            Returns the shape object from a column.
            \return shape object.
            */
            Shape shape() const { return _shape;}

            /*! \brief get cells type ID

            Return the TypeID of the column if available. This is only valid for
            systems where type information is stored in the file (like for FIO). 
            */
            TypeID type_id() const { return _tid; }

            /*! \brief get name

            Return the name of the column.
            \return name 
            */
            String name() const { return _name; }

    };


//end of namespace
}
}

#endif
