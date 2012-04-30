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

#include "SpreadsheetReader.hpp"

namespace pni{
namespace io{
    
    class FIOReader:public SpreadsheetReader
    {
        private:
            std::map<String,std::streampos> _param_map;
            std::streampos _data_offset;

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

            /*! \brief read parameter data

            This template is used internally to extract parameter data from the
            input stream and store the result in a variable of type T. 
            \parma stream input stream
            \param value where to store data
            */
            template<typename T>
                void _get_parameter_data(std::ifstream &stream,T &value) const;

            void _get_parameter_data(std::ifstream &stream,String &value) const;

            //static regular expressions

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

            virtual size_t nrecords() const;

            virtual std::vector<String> column_names() const;

            virtual std::vector<TypeID> column_types() const;

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

    }

}
}

#endif
