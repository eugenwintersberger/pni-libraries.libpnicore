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
 * Created on: Jul 23,2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */


#ifndef __NUMARRAY_HPP__
#define __NUMARRAY_HPP__

#include "Types.hpp"
#include "Shape.hpp"
#include "Iterator.hpp"
#include "ArrayViewSelector.hpp"

namespace pni{
namespace utils{



    template<typename ATYPE> class NumArray
    {
        //need to do here a compiletime check if types are equal
        private:
            ATYPE &_array;
        public:
            //====================public types=================================

            typedef typename ATYPE::value_type value_type;
            typedef NumArray<ATYPE> array_type;
            typedef typename ATYPE::storage_type storage_type;
            typedef ArrayView<array_type> view_type;
            typedef std::shared_ptr<array_type> shared_ptr;
            typedef std::unique_ptr<array_type> unique_ptr;

            typedef typename ATYPE::iterator iterator;
            typedef typename ATYPE::const_iterator const_iterator;
            
            //=====================public members==============================
            static const type_id = TypeIDMap<value_type>::type_id;

            //======================constructors and destructor================
            //! default constructor
            Array() = delete;

            //-----------------------------------------------------------------
            //! construct from an arbitary array type
            Array(ATYPE &a):_array(a) {}

            //-----------------------------------------------------------------
            //! copy constructor
            Array(const array_type &a):_array(a._array) {}

            //-----------------------------------------------------------------
            //! destructor
            ~Array() {} 

            //====================inquery methods=============================
            size_t size() const { return this->_array.size(); }

            //----------------------------------------------------------------
            size_t rank() const { return this->_array.rank(); }

            //-----------------------------------------------------------------
            template<typename CTYPE> CTYPE shape() const 
            {
                return this->_array.template shape<CTYPE>();
            }

            //==================accessing data=================================
        
            value_type operator[](size_t i) const { return this->_array[i]; }

            //-----------------------------------------------------------------
            value_type &operator[](size_t i) { return this->_array[i]; }

            //-----------------------------------------------------------------
            value_type &at(size_t i) { return this->_array.at(i); }

            //-----------------------------------------------------------------
            value_type at(size_t i) const { return this->_array.at(i); }

            //-----------------------------------------------------------------
            void insert(size_t i,const value_type &v)
            {
                this->_array.insert(i,v);
            }

            //-----------------------------------------------------------------
            const storage_type &storage() const
            {
                return this->_array.storage();
            }

            //-----------------------------------------------------------------
            template<typename ...ITYPES>
            typename ArrayViewSelector<array_type,ITYPES...>::reftype
            operator()(ITYPES ...indices)
            {
                return this->_array(indices...);
            }

            //-----------------------------------------------------------------
            template<typename ...ITYPES>
            typename ArrayViewSelector<array_type,ITYPES...>::viewtype
            operator()(ITYPES ...indices) const
            {
                return this->_array(indices...);
            }

            //-----------------------------------------------------------------
            template<template<typename ...> class CTYPE,typename ...OTS>
            typename ArrayViewSelector<array_type,typename CTYPE<OTS...>::value_type>::reftype
            operator()(const CTYPE<OTS...> &c)
            {
                return this->_array(c);
            }

            //-----------------------------------------------------------------
            template<template<typename ...> class CTYPE,typename ...OTS>
            typename ArrayViewSelector<array_type,typename CTYPE<OTS...>::value_type>::viewtype
            operator()(const CTYPE<OTS...> &c) const
            {
                return this->_array(c);
            }

            //===================iterators=====================================
            iterator begin() { return this->_array.begin(); }

            //-----------------------------------------------------------------
            iterator end() { return this->_array.end(); }

            //-----------------------------------------------------------------
            const_iterator begin() const { return this->_array.begin(); }

            //-----------------------------------------------------------------
            const_iterator end() const { return this->_array.end(); }

    };



//end of namespace
}
}

#endif
