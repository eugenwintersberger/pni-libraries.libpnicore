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
 * DataReader class definition
 *
 * Created on: Apr 23, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */


#ifndef __DATAREADER_HPP__
#define __DATAREADER_HPP__

#include <iostream>
#include <fstream>
#include "../Types.hpp"

namespace pni{
    namespace utils{

        /*! \ingroup io_classes
        \brief base class for data readers

        This is the base class for all data readers. Actually this class only
        manages the name of the file to open for reading.
        */
        class DataReader{
            private:
                String _fname;           //!< name of the file 
                std::ifstream _istream;  //!< stream from which to read data

                /*! \brief open the stream

                Virtual private method opening the stream. This class provides 
                a default implementation for this method. If a different 
                way of opening a stream is required this method must be
                overloaded by child classes.
                \throws FileError if opening the file fails
                */
                virtual void _open_stream();


            public:
                //===============constructor and destructors===================
                //! default constructor
                DataReader();
                /*! standard constructor

                This constructor takes the name of the file from which to reads
                data as its only argument and opens the file. 
                \throws FileError if opening the file fails
                */
                DataReader(const String &fname);

                /*! move constructor
                */
                DataReader(DataReader &&r);

                //copy constructor is deleted
                DataReader(const DataReader &r) = delete;

                //! destructor
                virtual ~DataReader();

                //=====================assignment operator=====================
                //copy assigment is deleted
                DataReader &operator=(const DataReader &r) = delete;

                //! move assignment
                DataReader &operator=(DataReader &&r);

                //====================member methods===========================
                /*! \brief get filename

                \return name of the file from which to read data
                */
                String filename() const;

                //-------------------------------------------------------------
                /*! \brief set filename

                \param fname name of the file to read data from
                */
                void filename(const String &fname);

                //-------------------------------------------------------------
                //! close the file
                void close();

                //-------------------------------------------------------------
                /*! \brief open file

                Opens the file given by filename. 
                \throws FileError in case of errors
                */
                void open();


                






                

        };

    //end of namespace
    }
}


#endif
