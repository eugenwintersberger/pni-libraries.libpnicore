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

#include <memory>
#include <iostream>
#include <fstream>
#include "../Types.hpp"

using namespace pni::utils;

namespace pni{
namespace io{

    /*! \ingroup io_classes
    \brief base class for data readers

    This is the base class for all data readers. Actually this class only
    manages the name of the file to open for reading.
    One cannot instantiate an object of this class directly. This is done 
    via the concrete reader classes. Thus all constructors are protected
    making them available only for derived classes.
    */
    class DataReader{
        private:
            String _fname;           //!< name of the file 
            bool _is_binary;         //!< flag determining how files will be opened
            //the stream is accessed via a unique pointer
            //this allows moveing the stream around while benefiting from
            //all advantages of a smart pointer
            std::unique_ptr<std::ifstream> _istream;  //!< stream from which to read data

            /*! \brief open the stream

            Virtual private method opening the stream. This class provides 
            a default implementation for this method. If a different 
            way of opening a stream is required this method must be
            overloaded by child classes.
            \throws FileError if opening the file fails
            */
            std::unique_ptr<std::ifstream> 
                _open_stream(const String &fname) const;
        protected:
            /*! \brief get stream

            Return a non-const reference to the stream on the file. This
            method is protected and thus only available to derived classes
            which can use this method to obtain a reference to the stream.
            \return non-const stream reference
            */
            std::ifstream &_get_stream() { return *_istream; } 

            /*! \brief set binary mode

            Set the stream mode to binary. This method is primarily used by 
            default constructors which do not have parameters.
            */
            void _set_binary() { _is_binary = true; }

            //==================Constructors=============================== 
            //! default constructor
            DataReader();
            /*! standard constructor

            This constructor takes the name of the file from which to reads
            data as its only argument and opens the file. 
            \throws FileError if opening the file fails
            \param fname name of the file
            \param binary if true stream will be opened in binary mode
            */
            explicit DataReader(const String &fname,bool binary=false);
            
            /*! move constructor
            */
            DataReader(DataReader &&r);

            //copy constructor is deleted
            DataReader(const DataReader &r) = delete;
            
            //=====================assignment operator=====================
            //copy assigment is deleted
            DataReader &operator=(const DataReader &r) = delete;

            //! move assignment
            DataReader &operator=(DataReader &&r);
            
            
            
        public:
            //===============constructor and destructors===================
            //! destructor
            virtual ~DataReader();

            //====================member methods===========================
            /*! \brief get filename

            \return name of the file from which to read data
            */
            pni::utils::String filename() const;

            //-------------------------------------------------------------
            /*! \brief set filename

            \param fname name of the file to read data from
            */
            void filename(const String &fname);

            //-------------------------------------------------------------
            //! close the file
            virtual void close();
            
            //-------------------------------------------------------------
            /*! \brief open file

            Opens the file given by filename. 
            \throws FileError in case of errors
            */
            virtual void open();

    };

//end of namespace
}
}


#endif
