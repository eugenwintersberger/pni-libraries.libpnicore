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
 * SpreadsheetReader class definition
 *
 * Created on: Apr 30, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#ifndef __SPREADSHEETREADER_HPP__
#define __SPREADSHEETREADER_HPP__

#include <vector>
#include "../Types.hpp"
#include "DataReader.hpp"

namespace pni{
namespace io{

    class SpreadsheetReader:public DataReader
    {
        protected:
            //============constructors and destructor==========================
            //! default constructor
            SpreadsheetReader();

            //! copy constructor is deleted
            SpreadsheetReader(const SpreadsheetReader &) = delete;

            //! move constructor
            SpreadsheetReader(SpreadsheetReader &&o);

            //! standard constructor
            SpreadsheetReader(const String &n);

        public:
            //! destructor
            virtual ~SpreadsheetReader();

            //===================assignment operators==========================
            //! copy assignment operator is deleted
            SpreadsheetReader &operator=(const SpreadsheetReader &) = delete;

            //! move assignment operator
            SpreadsheetReader &operator=(SpreadsheetReader &&r);

            //===============public memeber methods============================
            /*! \brief get column number 

            Returns the number of columns. 
            \return number of columns
            */
            virtual size_t ncolumns() const = 0;

            /*! \brief get record number

            Return the number of records in the spreadsheet.
            \return number of records
            */
            virtual size_t nrecords() const = 0;

            /*! \brief get column names

            Return a vector of strings holding the names of the columns if
            available. 
            \return column names
            */
            virtual std::vector<String> column_names() const = 0;

            virtual std::vector<TypeID> column_types() const = 0;


    };


//end of namespace
}
}

#endif

