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
 *  Created on: Mar 7, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <iostream>
#include <vector>
#include <utility>

namespace pni{
namespace core{

    /*!
    \ingroup util_classes
    \brief range distributor 

    This class subdivides a range of size s into n intervals of (mostly) equal
    size. This is particularly usefull in the case of multithreaded applications
    where operations on a container of size s must be distributed over n
    threads.The range distributor acts as an interable container for the
    subintervals. Subintervals are stored as pairs where the first and second
    element are the first and the last index of the interval. 

    In cases where s is not an integer multiple of n. The first s%n subintervals
    are 1 element larger than the nominal floor(s/n). 
    */
    class range_distributor
    {
        private:
            //! vector with ranges
            std::vector<std::pair<size_t,size_t> > _ranges;
        public:
            //=================public types====================================
            //! the value type of the contianer
            typedef std::pair<size_t,size_t> value_type;
            //! read/write iterator
            typedef std::vector<value_type>::iterator iterator;
            //! const iterator
            typedef std::vector<value_type>::const_iterator const_iterator;
            
            //================constructor and destructor=======================
            //! default constructor
            range_distributor():_ranges() {}

            //-----------------------------------------------------------------
            /*! 
            \brief constructor

            Constructor for a range_distributor. 
            \param n number of intervals
            \param s size of the index range
            */
            range_distributor(size_t n,size_t s);

            //==================iterator methods===============================
            //! get iterator to first element
            iterator begin() { return _ranges.begin(); }

            //! get iterator to last+1 element
            iterator end() { return _ranges.end(); }

            //! get const iterator to first element
            const_iterator begin() const { return _ranges.begin(); }

            //! get const iterator to last+1 element
            const_iterator end() const { return _ranges.end(); }

            
    };
}
}
