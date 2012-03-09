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
 * Definition of the IndexMap class. This class provides methods for easily
 * compute indices from multidimensional arrays.
 *
 * Created on: March 9, 2012
 *     Author: Eugen Wintersberger
 *
 */


#ifndef __INDEXMAP_HPP__
#define __INDEXMAP_HPP__

#include "Buffer.hpp"

namespace pni{
    namespace utils{

            /*! \brief compute multidimensional indices.

            */
            class IndexMap{
                private:
                    Buffer<ssize_t> _offset;
                    Buffer<ssize_t> _stride;
                    Buffer<ssize_t> _count;
                public:
                    //========constructors and destructor======================
                    //! default constructor
                    IndexMap();

                    //! copy constructor
                    IndexMap(const IndexMap &o);

                    //! move constructor
                    IndexMap(IndexMap &&o);

                    //! standard constructor
                    IndexMap(size_t rank);

                    //! standard constructor
                    IndexMap(const Buffer<ssize_t> &o,const Buffer<ssize_t> &s,
                             const Buffer<ssize_t> &c);

                    //! destructor
                    ~IndexMap();

                    //============assignment operators=========================
                    //! copy constructor
                    IndexMap &operator=(const IndexMap &o);

                    //! move constructor
                    IndexMap &operator=(IndexMap &&o);





            };

    //end of namespace
    }
}

#endif
