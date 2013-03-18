/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpnicore.
 *
 * libpnicore is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpnicore is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Created on: Dec 27, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include "../config.h"
#include "../types.hpp"
#include "configuration.hpp"
#include "config_parser.hpp"

namespace pni{
namespace core{


    /*!
    \brief configuration class for pniutils

    Configuration class of the pniutils library. This library is used by all
    other classes to obtain configuration information.

    This class most probably become a singleton.
    */
    class library_config
    {
        private:
            configuration conf; //!< configuration objecct
            size_t _nthreads;   //!< number of threads that should be used

            //!create the configuration structure
            void _setup_configuration();
        public:
            //! default constructor
            library_config();
            //! standard constructor
            library_config(const string &fname);
            //! destructor
            ~library_config();


            //! set number of thread for arithmetics
            void n_arithmetic_threads(size_t n) { _nthreads = n; }

            //! obtain number of threads for arithmetics
            size_t n_arithmetic_threads() const;

    };

//create the static global configuration object by reading data from the central
//configuration work. 
static library_config pnicore_config(CONFIG_FILE_PATH);

//end of namespace
}
}
