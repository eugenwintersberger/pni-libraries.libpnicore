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
 * ColumnInfo class implementation
 *
 * Created on: Apr 30, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */


#include "ColumnInfo.hpp"

namespace pni{
namespace io{

    //==================implementation of constructors and destructor==========
    //implementation of the  default constructor
    ColumnInfo::ColumnInfo():
        _name(),
        _tid(TypeID::NONE),
        _shape()
    {}

    //--------------------------------------------------------------------------
    //implementation of the copy constructor
    ColumnInfo::ColumnInfo(const ColumnInfo &ci):
        _name(ci._name),
        _tid(ci._tid),
        _shape(ci._shape)
    {}

    //-------------------------------------------------------------------------
    //implementation of the move constructor
    ColumnInfo::ColumnInfo(ColumnInfo &&ci):
        _name(std::move(ci._name)),
        _tid(std::move(ci._tid)),
        _shape(std::move(ci._shape))
    {}

    //-------------------------------------------------------------------------
    //implementation of the standard constructor
    ColumnInfo::ColumnInfo(const String &n,TypeID tid,const Shape &s):
        _name(n),
        _tid(tid),
        _shape(s)
    {}

    //-------------------------------------------------------------------------
    //implementation of the destructor
    ColumnInfo::~ColumnInfo()
    {}

    //===================implementation of assignment operators================
    //implementation of the  copy assignment operator
    ColumnInfo &ColumnInfo::operator=(const ColumnInfo &ci)
    {
        if(this == &ci) return *this;

        _name = ci._name;
        _shape = ci._shape;
        _tid = ci._tid;

        return *this;
    }

    //! move assignment operator
    ColumnInfo &ColumnInfo::operator=(ColumnInfo &&ci)
    {
        if(this == &ci) return *this;

        _name = std::move(ci._name);
        _shape = std::move(ci._shape);
        _tid = std::move(ci._tid);
        return *this;
    }

//end of namespace
}
}
