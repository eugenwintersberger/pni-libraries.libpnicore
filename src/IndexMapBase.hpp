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
 * Definition of a dynamic array template.
 *
 * Created on: Jul 19, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef __INDEXMAPBASE_HPP__
#define __INDEXMAPBASE_HPP__

#include "DBuffer.hpp"

namespace pni {
namespace utils {

    class IndexMapBase
    {
        private:
            //! buffer storing the shape of the index map
            DBuffer<size_t> _shape;
        public:
            //================constructors and destructor======================
            //! default constructor
            IndexMapBase():_shape() {}

            //-----------------------------------------------------------------
            //! initialization from a container
            template<typename CTYPE> IndexMapBase(const CTYPE &c):
                _shape(c.size())
            {
                std::copy(c.begin(),c.end(),_shape.begin());
            }

            //-----------------------------------------------------------------
            //! initialization from an initializer list
            IndexMapBase(const std::initializer_list<size_t> &l):
                _shape(l.size())
            {
                std::copy(l.begin(),l.end(),_shape.begin());
            }

            //-----------------------------------------------------------------
            //! destructor
            virtual ~IndexMapBase() {}

            //=================assignment operators============================
            //! copy assignment operator
            IndexMapBase &operator=(const IndexMapBase &m);

            //! move assignment operator
            IndexMapBase &operator=(IndexMapBase &&m);

            //===================public methods================================
            //! get size of the map
            size_t size() const;

            //-----------------------------------------------------------------
            /*!
            \brief get shape

            Returns a const reference to the shape buffer.
            \return buffer reference
            */
            const DBuffer<size_t> &shape() const { return _shape; }

            //-----------------------------------------------------------------
            /*! 
            \brief get shape

            Returns a copy of the shape buffer in an arbitary container type.
            \return container with shape data
            */
            template<typename CTYPE> CTYPE shape() const
            {
                CYTPE c(_shape.size());
                std::copy(_shape.begin(),_shape.end(),c.begin());
                return c;
            }

    };

//end of namespace
}
}

#endif
