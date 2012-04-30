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
#include "../Exceptions.hpp"
#include "DataReader.hpp"
#include "ColumnInfo.hpp"

namespace pni{
namespace io{

    class SpreadsheetReader:public DataReader
    {
        private:
            std::vector<ColumnInfo> _columns_info; //!< column information

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

            //==================protected member functions=====================
            virtual void _append_column(const ColumnInfo &i)
            {
                _columns_info.push_back(i);
            }

            virtual ColumnInfo _get_column(size_t i) const
            {
                return _columns_info.at(i);
            }

            virtual ColumnInfo _get_column(const String &n) const
            {
                EXCEPTION_SETUP("virtual ColumnInfo SpreadsheetReader::"
                        "_get_column(const String &n) const");

                size_t i=0;
                for(auto c: _columns_info)
                {
                    if(c.name() == n)
                        return _get_column(i); 

                    //increment column counter
                    i++;
                }
                
                EXCEPTION_INIT(KeyError,"Column ["+n+"] not found!");
                EXCEPTION_THROW();
                return ColumnInfo(); //just to get rid of compiler warning
            }


        public:
            //========================public type==============================
            typedef std::vector<ColumnInfo>::iterator column_info_iterator;
            typedef std::vector<ColumnInfo>::const_iterator
                column_info_const_iterator;
            //=======================destructor================================
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
            size_t ncolumns() const
            {
                return _columns_info.size();
            }

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

