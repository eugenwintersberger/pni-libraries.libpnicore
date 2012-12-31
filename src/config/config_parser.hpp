/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 * Created on: Dec 27, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */


#include "configuration.hpp"
namespace pni{
namespace utils{

    /*!
    \brief read config from command line options
    
    Function constructs the configuration instance from command line options
    passed to a program.
    \param c reference to the configuration object
    \param argc number of command line arguments
    \param argv argument values
    */
    void parse(configuration &c,int argc,char **argv);

    //-------------------------------------------------------------------------
    /*!
    \brief read config from a file

    Function to read configuration from a configuration file. 
    \param c reference to the configuration object
    \param fname name of the configuration file
    */
    void parse(configuration &c,const String &fname);

//end of namespace
}
}
