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
            _count()
        { }

        //---------------------------------------------------------------------
        //implementation of the copy constructor
        IndexMap::IndexMap(const IndexMap &o):
            _offset(o._offset),
            _stride(o._stride),
            _count(o._count)
        {}

        //---------------------------------------------------------------------
        //implementation of the move constructor
        IndexMap::IndexMap(IndexMap &&o):
            _offset(std::move(o._offset)),
            _stride(std::move(o._stride)),
            _count(std::move(o._count))
        {}
        
        //---------------------------------------------------------------------
        //first standard constructor
        IndexMap::IndexMap(size_t rank):
            _offset(rank),
            _stride(rank),
            _count(rank)
        {}

        //---------------------------------------------------------------------
        //implementation of second standard constructor
        IndexMap::IndexMap(const Buffer<ssize_t> &o,const Buffer<ssize_t> &s,
                           const Buffer<ssize_t> &c):
            _offset(o),
            _stride(s),
            _count(c)
        { 
            EXCEPTION_SETUP("IndexMap::IndexMap(const Buffer<ssize_t> &o,"
                    "const Buffer<ssize_t> &s, const Buffer<ssize_t> &c)");

            //need to check if all buffers have the same size
            if((_offset.size() != _stride.size())||
               (_offset.size() != _count.size())||
               (_stride.size() != _count.size()))
            {
                std::stringstream estrm(std::stringstream::in);
                estrm<<"Buffer sizes are not equal: "<<std::endl;
                estrm<<"Offset buffer: "<<_offset.size()<<std::endl;
                estrm<<"Stride buffer: "<<_stride.size()<<std::endl;
                estrm<<"Count  buffer: "<<_count.size()<<std::endl;
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
            _count.free();
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
                _count  = o._count;
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
                _count  = std::move(o._count);
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

        //---------------------------------------------------------------------
        void IndexMap::count(size_t i,ssize_t c)
        {
            _count[i] = c;
        }

        //---------------------------------------------------------------------
        void IndexMap::count(const Buffer<ssize_t> &c)
        {
            EXCEPTION_SETUP("void IndexMap::count(const Buffer<ssize_t> &c)");

            if(c.size()!=rank())
            {
                std::stringstream estrm(std::stringstream::in);
                estrm<<"Buffer size ("<<c.size()<<") does not match ";
                estrm<<"IndexMap rank ("<<rank()<<")!";
                EXCEPTION_INIT(SizeMissmatchError,estrm.str());
                EXCEPTION_THROW();
            }

            _count = c;
        }
        
        //---------------------------------------------------------------------
        ssize_t IndexMap::count(size_t i) const
        {
            return _count[i];
        }

        //---------------------------------------------------------------------
        const Buffer<ssize_t> &IndexMap::count() const
        {
            return _count;
        }

        //---------------------------------------------------------------------
        /*
        Buffer<size_t> index(size_t offset)
        {
            Buffer<size_t> ibuffer(rank());


            size_t o,t;
            o = offset;
            for(size_t d = 0;d<rank();d++){
                //compute dimension stride 
                

                t = o%_dimstrides[d];
                i[d] = (o-t)/_dimstrides[d];
                o = t;
            }

            return ibuffer;
        }*/

    //end of namespace
    }
}
