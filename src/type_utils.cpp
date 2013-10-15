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

#include <sstream>
#include <stdexcept>
#include <pni/core/exceptions.hpp>
#include <pni/core/type_utils.hpp>


namespace pni{
namespace core{

    //-------------------------------------------------------------------------
    type_id_t get_type_id(const binary &v)
    {
        return type_id_t::BINARY;
    }

    //-------------------------------------------------------------------------
    type_id_t get_type_id(const string &v)
    {
        return type_id_t::STRING;
    }

    //-------------------------------------------------------------------------
    type_id_t type_id_from_str(const string &s)
    {
        try
        {
            return str2type_id.at(s);
        }
        catch(std::out_of_range &error)
        {
            string msg = "String ["+s+"] does not represent a type!";
            throw key_error(EXCEPTION_RECORD,s);
        }
    }

    //-------------------------------------------------------------------------
    string str_from_type_id(type_id_t id)
    {
        try
        {
            return type_id2str.at(id);
        }
        catch(std::out_of_range &error)
        {
            std::stringstream ss;
            ss<<"Type id ["<<id<<"] does not have a string representation!";
            throw key_error(EXCEPTION_RECORD,ss.str());
        }
    }

//end of namespace
}
}

