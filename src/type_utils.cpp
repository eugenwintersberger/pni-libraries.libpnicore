/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 * Created on: Sep 30, 2013
 *     Author: Eugen Wintersberger
 *
 */

#include <pni/core/type_utils.hpp>


namespace pni{
namespace core{

    type_id_t type_id(const binary &v)
    {
        return type_id_t::BINARY;
    }

    type_id_t type_id(const string &v)
    {
        return type_id_t::STRING;
    }

//end of namespace
}
}

