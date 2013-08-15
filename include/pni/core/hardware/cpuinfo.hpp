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
 * Created on: Jan 01, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

namespace pni{
namespace core{
   
    /*!
    \brief abstract class for cpu information

    This abstract class defines the interface for classes obtaining CPU
    information for a particular operating system platform.
    */
    class cpuinfo
    {
        public:
            /*!
            \brief get number of physical CPUs

            Return the number of physical CPUs on the actual host. 
            */
            virtual size_t n_sockets() const = 0;

            //-----------------------------------------------------------------
            /*!
            \brief number of cores

            Total number of cores available on the host. This number is at least
            the number of sockets on the machine. The crucial question is to
            figure out how to obtain 
            \return number of cores
            */
            virtual size_t n_cpus() const = 0;

            //------------------------------------------------------------------
            /*!
            \brief number of cpus per socket

            This method computes the total  number of cpus per socket.
            \return cpus per socket. 
            */
            virtual size_t n_cpus_per_socket() const = 0;

    };

//end of namespace
}
}
