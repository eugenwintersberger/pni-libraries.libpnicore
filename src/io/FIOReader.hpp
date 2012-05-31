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
 * FIOReader class definition
 *
 * Created on: Apr 30, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#ifndef __FIOREADER_HPP__
#define __FIOREADER_HPP__

#include<iostream>
#include<sstream>
#include<map>
#include<boost/regex.hpp>

#include "../Array.hpp"
#include "../ArrayFactory.hpp"
#include "SpreadsheetReader.hpp"

namespace pni{
namespace io{
   
    /*! \ingroup io_classes
    \brief FIO data reader

    FIO files are written by ONLINE a data acquisition and experiment control
    software used at DESY. FIO files are basically ACII files where data is
    stored in columns. Thus such files correspond to the family of spreadsheet
    style files. 
    */
    class FIOReader:public SpreadsheetReader
    {
        private:
            std::map<String,std::streampos> _param_map; //!< parameter stream positions
            std::streampos _data_offset; //!< offset where real data starts

            //====================private member methods=======================
            /*! \brief initial file parseing

            This private method runs through the entire file once and calles the
            appropriate parses. 
            \param stream input stream from which to read data
            */
            void _parse_file(std::ifstream &stream);

            /*! \brief parse parameter section

            Method parses the parameter section of a file. It sets up the
            _param_map member variable. 
            \param stream input stream from which to read data
            */
            void _parse_parameters(std::ifstream &stream);

            /*! \brief parse the data section

            Private function which execudes parser code for the data section of
            the FIO file. It collects all the information about columns present
            in the file.
            \param stream input stream from which to read data
            */
            void _parse_data(std::ifstream &stream);

            /*! \brief type id from type string 

            Method converts a FIO type string to a TypeID as provided by
            libpniutils.
            \param tstr type string
            \return TypeID 
            */
            static TypeID _typestr2id(const String &tstr);

            /*! \brief get ColumnInfo from line

            Method retrievs column information from a line. 
            \param line string object holding the lines content
            \return instance of ColumnInfo
            */
            static ColumnInfo _read_column_info(const String &line);
           
            /*! \brief read data line

            Reads a data line and splits the line into its cells. The method
            returns a vector of Strings where each elements corresponds to a
            particular cell. 
            \param line input line
            \return vector with cell content as strings
            */
            static std::vector<String> _read_data_line(const String &line);

            /*! \brief read parameter data

            This template is used internally to extract parameter data from the
            input stream and store the result in a variable of type T. 
            \param stream input stream
            \param value where to store data
            */
            template<typename T>
                void _get_parameter_data(std::ifstream &stream,T &value) const;

            /*! \brief read string parameter

            Overloaded version of the _get_parameter_data template method to
            handle string data. 
            \param stream input stream
            \param value string value where to store parameter data
            */
            void _get_parameter_data(std::ifstream &stream,String &value) const;

            /*! \brief read column data

            Private template method to read column data and store it to an array
            object. If EOF is reached before all data was read an exception will
            be thrown.
            \throw FileError if EOF is reached before end of data
            \param index index of the column in the file
            \param array instance of the Array template where to store the data
            */
            template<typename T,template<typename,typename> class BT,typename
                Allocator> 
                void _read_column(size_t index,Array<T,BT,Allocator> &array) const;

        public:
            //==============constructor and destructor=========================
            //! default constructor
            FIOReader();

            //! copy construction is deleted
            FIOReader(const FIOReader &r) = delete;

            //! move constructor
            FIOReader(FIOReader &&r);

            //! standard constructor
            FIOReader(const String &n);

            //! destructor
            ~FIOReader();

            //===================assignment operators==========================
            //! copy assignment is deleted
            FIOReader &operator=(const FIOReader &r) = delete;

            //! move assignemnt operator
            FIOReader &operator=(FIOReader &&r);

            //=================public member methods===========================
            /*! \brief get number of parameters

            Return the number of parameters stored in the file.
            \return number of parameters
            */
            size_t nparameters() const;

            /*! \brief get parameter names

            Returns a vector of Strings holding the parameter names stored in
            the file.
            \return parameter names
            */
            std::vector<String> parameter_names() const;

            /*! \brief get parameter by name

            Return the value of a parameter stored in the FIO file by name. 
            \throws KeyError if parameter name does not exist
            \param name parameter name
            \return parameter value as type T
            */
            template<typename T> T parameter(const String &name) const;
            
            /*! \brief get single column

            Returns a single column and stores the data into an array object.
            If the column name does not exist an exception is thrown.
            \throws KeyError if column does not exist
            \throws FileError if EOF is reached before end of data
            \param n name of the column
            \return instance of ATYPE holding the data.
            */
            template<typename ATYPE> ATYPE column(const String &n) const;

    };
    
    //==========implementation of private template methods=====================
    template<typename T> void FIOReader::_get_parameter_data(
            std::ifstream &stream,T &value) const
    {
        stream>>value;
    }

    //======================template implementation============================
    template<typename T> T FIOReader::parameter(const String &name) const
    {
        std::ifstream &stream = this->_get_stream();
        std::streampos opos = stream.tellg(); //backup old stream position
    
        //obtain stream offset
        stream.seekg(this->_param_map.find(name)->second,std::ios::beg);

        //read data
        T value;

        this->_get_parameter_data(stream,value);

        //reset stream position
        stream.seekg(opos,std::ios::beg);
    
        return value;
    }


    //-------------------------------------------------------------------------
    template<typename ATYPE> ATYPE FIOReader::column(const String &n) const
    {
        EXCEPTION_SETUP("template<typename ATYPE> ATYPE FIOReader::"
                        "column(const String &n) const");

        //allocate a new array
        Shape s({this->nrecords()});
        ATYPE array = ArrayFactory<typename ATYPE::value_type>::create(s);

        //determine the index of the column
        size_t index = 0;
        for(auto c: *this)
        {
            if(c.name() == n) 
            {
                this->_read_column(index,array);
                return array;
            }
            index++;
        }

        //throw an exception here
        EXCEPTION_INIT(KeyError,"File ["+this->filename()+"] does not have a "
                "a column ["+n+"]!");
        EXCEPTION_THROW();
        return array; //just to avoid compiler warnings
    }

    //-------------------------------------------------------------------------
    template<typename T,template<typename,typename> class BT,typename Allocator> 
        void FIOReader::_read_column(size_t index,Array<T,BT,Allocator> &array) const
    {
        EXCEPTION_SETUP("template<typename T,template<typename> class BT> "
                        "void FIOReader::_read_column(size_t index,"
                        "Array<T,BT> &array) const");

        std::ifstream &stream = this->_get_stream();
        std::streampos orig_pos = stream.tellg();
        //move stream to data section
        stream.seekg(_data_offset,std::ios::beg);

        size_t lcnt=0;
        String linebuffer;
        while(!stream.eof())
        {
            std::getline(stream,linebuffer);
            std::vector<String> string_data = this->_read_data_line(linebuffer);
            std::stringstream ss(string_data[index]);
            ss>>array[lcnt];
            lcnt++;
            if(lcnt == this->nrecords())
            {
                //reset the stream position
                stream.seekg(orig_pos,std::ios::beg);
                //return from this method
                return;
            }
        }

        //if we come to some reason here to this point the stream ended before
        //data was finished - throw an exception
        //reset the stream 
        stream.seekg(orig_pos,std::ios::beg);
        EXCEPTION_INIT(FileError,"EOF of file ["+this->filename()+"] before"
                " reading data was completed!");
        EXCEPTION_THROW();

    }

//end of namespace
}
}

#endif
