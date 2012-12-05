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
 * Implementation of the exception classes declared in Exceptions.hpp.
 *
 * Created on: Apr 19, 2011
 *     Author: Eugen Wintersberger
 *
 */

#include<iostream>
#include<string>

#include "Exceptions.hpp"

namespace pni{
namespace utils{

    //-------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const ExceptionRecord &rec)
    {
        o<<rec.file()<<"\t"<<rec.line()<<"\t"<<rec.function()<<std::endl;
        return o;
    }

    //============Implementation of constructors and destructor================
    Exception::Exception():
        std::exception()
    {}

    //--------------------------------------------------------------------------
    Exception::Exception(const String &n):
        std::exception(),
        _name(n),
        _description(),
        _records()
    {}

    //--------------------------------------------------------------------------
    Exception::Exception(const String &n,const ExceptionRecord &i):
        std::exception(),
        _name(n),
        _description(),
        _records()
    { 
        _records.push_back(i); 
    }

    //--------------------------------------------------------------------------
    Exception::Exception(const String &n,const ExceptionRecord &i,const String &d):
        std::exception(),
        _name(n),
        _description(d),
        _records()
    {
        _records.push_back(i);
    }

    //==========Implementation of output methods and operator===================
    std::ostream &Exception::print(std::ostream &o) const 
    {
        o<<"Exception: "<<this->name()<<std::endl<<std::endl;
        o<<std::endl<<"Description:"<<std::endl;
        o<<this->description()<<std::endl<<std::endl;
        o<<"Exception thrown by:"<<std::endl;
#ifdef NOFOREACH
        for(auto iter = this->begin();iter != this->end(); iter++)
        {
            auto rec = *iter;
#else
        for(auto rec: *this){
#endif
            o<<rec<<std::endl;
        }
    
        o<<std::endl;

        return o;
    }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &ostr,const Exception &ex)
    {
        return ex.print(ostr);
    }

    //=========Implementation of the output operators for other errors==========
    std::ostream &operator<<(std::ostream &o,const MemoryAllocationError &e)
    {
        return e.print(o);
    }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const ShapeMissmatchError &e)
    {
        return e.print(o);
    }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const SizeMissmatchError &e)
    {
        return e.print(o);
    }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const IndexError &e)
    {
        return e.print(o);
    }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const FileError &e)
    {
        return e.print(o);
    }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const TypeError &e)
    {
        return e.print(o);
    }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const RangeError &e)
    {
        return e.print(o);
    }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const NotImplementedError &e)
    {
        return e.print(o);
    }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const IteratorError &e)
    {
        return e.print(o);
    }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const KeyError &e)
    {
        return e.print(o);
    }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const MemoryNotAllocatedError &e)
    {
        return e.print(o);
    }

//end of namespace
}
}
