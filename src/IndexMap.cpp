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
 * Implementation of the IndexMap class. This class provides methods for easily
 * compute indices from multidimensional arrays.
 *
 * Created on: March 9, 2012
 *     Author: Eugen Wintersberger
 *
 */

#include <sstream>

#include "Exceptions.hpp"
#include "IndexMap.hpp"


namespace pni{
    namespace utils{
        //==========Implementation of constructors and destructor==============
        //implementation of the default constructor
        IndexMap::IndexMap():
            _offset(),
            _stride(),
            _shape()
        { }

        //---------------------------------------------------------------------
        //implementation of the copy constructor
        IndexMap::IndexMap(const IndexMap &o):
            _offset(o._offset),
            _stride(o._stride),
            _shape(o._shape)
        {}

        //---------------------------------------------------------------------
        //implementation of the move constructor
        IndexMap::IndexMap(IndexMap &&o):
            _offset(std::move(o._offset)),
            _stride(std::move(o._stride)),
            _shape(std::move(o._shape))
        {}
        
        //---------------------------------------------------------------------
        //first standard constructor
        IndexMap::IndexMap(const Shape &s):
            _offset(s.rank()),
            _stride(s.rank()),
            _shape(s)
        {
            _offset = 0;
            _stride = 1;
        }

        //---------------------------------------------------------------------
        //implementation of second standard constructor
        IndexMap::IndexMap(const Shape &s,const Buffer<ssize_t> &offset,
                           const Buffer<ssize_t> &stride):
            _offset(offset),
            _stride(stride),
            _shape(s)
        { 
            EXCEPTION_SETUP("IndexMap::IndexMap(const Buffer<ssize_t> &o,"
                    "const Buffer<ssize_t> &s, const Buffer<ssize_t> &c)");

            //need to check if all buffers have the same size
            if((_offset.size() != _stride.size())||
               (_offset.size() != _shape.rank())||
               (_stride.size() != _shape.rank()))
            {
                std::stringstream estrm(std::stringstream::in);
                estrm<<"Buffer sizes are not equal: "<<std::endl;
                estrm<<"Offset buffer: "<<_offset.size()<<std::endl;
                estrm<<"Stride buffer: "<<_stride.size()<<std::endl;
                estrm<<"Count  buffer: "<<_shape.rank()<<std::endl;
                estrm<<"Construction of IndexMap failed!";
                EXCEPTION_INIT(SizeMissmatchError,estrm.str());
                EXCEPTION_THROW();
            }
        }

        //---------------------------------------------------------------------
        //implementation of the destructor
        IndexMap::~IndexMap()
        {
            _offset.free();
            _stride.free();
        }

        //================implementation of assignment operators===============
        //implementation of copy assignment
        IndexMap &IndexMap::operator=(const IndexMap &o)
        {
            if(this != &o)
            {
                _offset = o._offset;
                _stride = o._stride;
                _shape  = o._shape;
            }
            return *this;
        }

        //---------------------------------------------------------------------
        //implementation of move assignment
        IndexMap &IndexMap::operator=(IndexMap &&o)
        {
            if(this != &o)
            {
                _offset = std::move(o._offset);
                _stride = std::move(o._stride);
                _shape  = std::move(o._shape);
            }
            return *this;
        }

        //==============access methods for map parameters======================
        void IndexMap::offset(size_t i,ssize_t o)
        {
            _offset[i] = o;
        }

        //---------------------------------------------------------------------
        void IndexMap::offset(const Buffer<ssize_t> &o)
        {
            EXCEPTION_SETUP("void IndexMap::offset(const Buffer<ssize_t> &o)");

            if(o.size()!=rank())
            {
                std::stringstream estrm(std::stringstream::in);
                estrm<<"Buffer size ("<<o.size()<<") does not match ";
                estrm<<"IndexMap rank ("<<rank()<<")!";
                EXCEPTION_INIT(SizeMissmatchError,estrm.str());
                EXCEPTION_THROW();
            }

            _offset = o;
        }
        
        //---------------------------------------------------------------------
        ssize_t IndexMap::offset(size_t i) const
        {
            return _offset[i];
        }

        //---------------------------------------------------------------------
        const Buffer<ssize_t> &IndexMap::offset() const
        {
            return _offset;
        }

        //---------------------------------------------------------------------
        void IndexMap::stride(size_t i,ssize_t s)
        {
            _stride[i] = s;
        }

        //---------------------------------------------------------------------
        void IndexMap::stride(const Buffer<ssize_t> &s)
        {
            EXCEPTION_SETUP("void IndexMap::stride(const Buffer<ssize_t> &s)");

            if(s.size()!=rank())
            {
                std::stringstream estrm(std::stringstream::in);
                estrm<<"Buffer size ("<<s.size()<<") does not match ";
                estrm<<"IndexMap rank ("<<rank()<<")!";
                EXCEPTION_INIT(SizeMissmatchError,estrm.str());
                EXCEPTION_THROW();
            }

            _stride = s;
        }
        
        //---------------------------------------------------------------------
        ssize_t IndexMap::stride(size_t i) const
        {
            return _stride[i];
        }

        //---------------------------------------------------------------------
        const Buffer<ssize_t> &IndexMap::stride() const
        {
            return _stride;
        }



    //end of namespace
    }
}
