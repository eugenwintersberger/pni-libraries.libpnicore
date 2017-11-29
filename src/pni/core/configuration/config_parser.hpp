//
// (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpnicore.
//
// libpnicore is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpnicore is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
//
// ============================================================================
//
// Created on: Dec 27, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
///
#pragma once

#include <pni/core/configuration/configuration.hpp>

#include <pni/core/windows.hpp>

namespace pni{
namespace core{

    //-------------------------------------------------------------------------
    //!
    //! \ingroup config_classes
    //! \brief store cli options in vector
    //!
    //! This function stores CLI options and arguments in a vector. 
    //!
    //! \param argc number of arguments
    //! \param argv argument values
    //!\return vector with arguments and options
    //!
    std::vector<string> PNICORE_EXPORT cliargs2vector(int argc,char **argv);

    //-------------------------------------------------------------------------
    //!
    //! \ingroup config_classes
    //! \brief read configuration from vector
    //!
    //! This function parses CLI options an arguments from a vector. Unlike 
    //! the original pointer approach the vector must not contain the program 
    //! name (usually passed as the first argument to a program). A utilty 
    //! function can be used to convert the defautl CLI argument pointer to 
    //! a vector
    /*!
    \code
    int main(int argc,char **argv)
    {
      ......
    
      std::vector<string> args = cliargs2vector(argc,argv);
      configuration config;
      ......
      parse(config,args);
    
     ......
    }
    \endcode
    !*/
    //! 
    //! \param c reference to the configuration to be parsed
    //! \param args command line arguments in a vector
    //! \param unregistered flag to allow unregistered options
    //! \return a vector with uncrecognized options
    //!
    std::vector<string> 
    PNICORE_EXPORT parse(configuration &c,const std::vector<string> &args,
                         bool unregistered=false);

    //-------------------------------------------------------------------------
    //!
    //! \ingroup config_classes
    //! \brief read config from a file
    //!
    //! Function to read configuration from a configuration file. 
    //! 
    //! \param c reference to the configuration object
    //! \param fname name of the configuration file
    //!
    void PNICORE_EXPORT parse(configuration &c,const string &fname);

//end of namespace
}
}
