/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 * Base class for an index map.
 *
 * Created on: Jul 19, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

#include <iostream>
#include <vector>

namespace pni {
namespace core {

    /*! 
    \ingroup index_mapping_classes
    \brief base class for dynamic index maps

    This class can be used as a base class for dynamic (configurable at runtime)
    index maps. 
    */
    class index_map_base
    {
        private:
            //! buffer storing the shape of the index map
            std::vector<size_t> _shape;
            //! total size represented by the index map
            size_t _size;

            //! update the size of the map
            void _size_update();
        public:
            //================constructors and destructor======================
            //! default constructor
            index_map_base();
            
            //-----------------------------------------------------------------
            //! copy constructor
            index_map_base(const index_map_base &m);

            //-----------------------------------------------------------------
            //! move constructor
            index_map_base(index_map_base &&m);

            //-----------------------------------------------------------------
            //! initialization from a container
            template<template<typename ...> class CTYPE,typename ...OTYPES> 
                explicit index_map_base(const CTYPE<OTYPES...> &c):
                _shape(c.size())
            {
                std::copy(c.begin(),c.end(),_shape.begin());

                //update the number of elements
                _size_update();
            }

            //-----------------------------------------------------------------
            //! initialization from an initializer list
            explicit index_map_base(const std::initializer_list<size_t> &l):
                _shape(l.size())
            {
                std::copy(l.begin(),l.end(),_shape.begin());

                //update the number of elements
                _size_update();
            }

            //-----------------------------------------------------------------
            //! destructor
            virtual ~index_map_base() {}

            //=================assignment operators============================
            //! copy assignment operator
            index_map_base &operator=(const index_map_base &m);

            //-----------------------------------------------------------------
            //! move assignment operator
            index_map_base &operator=(index_map_base &&m);

            //===================public methods================================
            /*! 
            \brief get size of the map

            Return the total number of elements that can be addressed by the
            map. If the map is not initialized as it would be the case when only
            the default constructor is used the size is 0.
            \return number of elements
            */
            size_t size() const
            {
                //return 0 if the map is not initialized
                if(_shape.size() == 0) return 0;

                return _size;

            }

            //-----------------------------------------------------------------
            /*!
            \brief get rank

            Return the rank of the map - which is the number of dimensions
            managed by the map. If the map is not initialized like it is the
            case when the instance in use was created by calling the default
            constructor the rank is 0.
            \return number of dimensions
            */
            size_t rank() const;

            //-----------------------------------------------------------------
            /*!
            \brief get shape

            Returns a const reference to the shape buffer.
            \return buffer reference
            */
            const std::vector<size_t> &shape() const { return _shape; }

            //-----------------------------------------------------------------
            /*! 
            \brief get shape

            Returns a copy of the shape buffer in an arbitary container type.
            \return container with shape data
            */
            template<typename CTYPE> CTYPE shape() const
            {
                CTYPE c(_shape.size());
                std::copy(_shape.begin(),_shape.end(),c.begin());
                return c;
            }

            //-----------------------------------------------------------------
            /*! 
            \brief set shape

            Set the shape of the index map from an arbitrary container. 
            \tparam CTYPE type of the container passed to the method
            \param c container with shape information
            */
            template<typename CTYPE> void shape(const CTYPE &c) 
            {
                _shape = std::vector<size_t>(c.size());
                std::copy(c.begin(),c.end(),_shape.begin());

                //update the number of elements
                _size_update();
            }
    };

//end of namespace
}
}
