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
 * Created on: Oct 28, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

//#include<memory>
#include<iostream>
#include<sstream>
#include<stdexcept>
#include<utility>
#include<complex>
#include<cstdarg>
#include<cstdio>
#include<memory>

#include "exception_utils.hpp"
#include "types.hpp"
#include "slice.hpp"
//#include "array_view.hpp"
//#include "array_view_selector.hpp"
#include "index_map/index_maps.hpp"

#include "type_id_map.hpp"
#include "type_conversion.hpp"

namespace pni {
namespace core {

    /*! 
    \ingroup multidim_array_classes
    \brief template for a multi-dimensional array class

    \tparam STORAGE storage object to use to keep the data
    \tparam IMAP the index map 
    */
    template<typename STORAGE,
             typename IMAP=cindex_map > 
    class mdarray
    {
        private:
            //! Index map of the array 
            IMAP _imap;  
            //! instance of STORAGE
            STORAGE _data;  

        public:
            //================public types=====================================
            //! type of the buffer object
            typedef STORAGE storage_type;
            //! arrays element type
            typedef typename storage_type::value_type value_type;  
            //! index map type
            typedef IMAP map_type;
            //! type of the array
            typedef mdarray<storage_type,map_type> array_type;
            //! shared pointer to array_type
            typedef std::shared_ptr<array_type> shared_ptr;
            //! unique pointer to array type
            typedef std::unique_ptr<array_type> unique_ptr; 
            //! type for array view
            //typedef array_view<array_type> view_type;
            //! iterator type
            typedef typename storage_type::iterator iterator;
            //! const iterator type
            typedef typename storage_type::const_iterator const_iterator; 
            //! reverse iterator
            typedef typename storage_type::reverse_iterator reverse_iterator;
            //! const reverse iterator
            typedef typename storage_type::const_reverse_iterator
                const_reverse_iterator;
            
            //==================public members=================================
            //! type ID of the element type
            static const type_id_t type_id; 

            //=================constructors and destructor=====================
            mdarray():_imap(),_data() {}

            //-----------------------------------------------------------------
            mdarray(const IMAP &map,const STORAGE &s):
                _imap(map),
                _data(s)
            {}

            //-----------------------------------------------------------------
            mdarray(IMAP &&map,STORAGE &&s):
                _imap(std::move(map)),
                _data(std::move(s))
            {}

            //================public methods===================================
            /*! \brief get index map

            Returns a const reference to the index map of the array.
            \return reference to index map
            */
            map_type map() const { return this->_imap; }

            //----------------------------------------------------------------
            //! shape to container
            template<typename CTYPE> CTYPE shape() const
            {
                CTYPE c(_imap.rank());
                std::copy(_imap.begin(),_imap.end(),c.begin());
                return c;
            }

            //-----------------------------------------------------------------
            /*!
            \brief change the shape 

            Change the shape of an array if supported by the index map. 
            In general, what is true for all arrays is that the number of
            elements in the new shape must be equal to the original number of
            elements. However, there are certain limitations depending on which
            index map is used. 

            \li in the case of a fully dynamic map rank and number of elements
            can be changed 
            \li for a map with fixed rank only the number of elements along each
            dimension can be changed
            \li finally for a static map this operation will always fail 

            \throws shape_mismatch_error in case of any error
            \tparam CTYPE container type 
            \parma new_shape instance of CTYPE with the new shape of the array
            */
            /*
            template<typename CTYPE> void shape(const CTYPE &new_shape)
            {
                //first let's create a new map - if the map type supports this
                //operation (including possible resizeing of the maps internal
                //storage) everything is fine so far.
                auto new_map = map_utils<map_type>::create(new_shape);

                //now we have to check if the total size would not change
                if(new_map.max_elements() != _imap.max_elements())
                {
                    throw shape_mismatch_error(EXCEPTION_RECORD,"");
                }

                _imap = std::move(new_map);

            }*/


            //-----------------------------------------------------------------
            /*! \brief obtain buffer reference

            Return a const reference to the arrays buffer object.
            \return buffer reference
            */
            const STORAGE &storage() const { return _data; }

            //-----------------------------------------------------------------
            /*! \brief get size of array

            Returns the total number of elements stored in the array.
            \return total number of elements
            */
            size_t size() const { return _data.size(); }

            //-----------------------------------------------------------------
            //! get number of dimensions of the array
            size_t rank() const { return _imap.rank(); }

            //=============operators and methods to access array data==========
            /*! \brief get referece to element i

            Returns a reference to the element at linear index i. No index
            checking is done! Thus use this operator with care.
            \param i linear index 
            \return reference to the element at linear index i
            */
            value_type& operator[](size_t i) { return _data[i]; }

            //-----------------------------------------------------------------
            /*! \brief get value at i

            Returns the value of the element at the linar array index i. No
            index checking is done! Thus use this operator with care.
            \param i linear index of the element
            \return value of the element at linear index i
            */
            value_type operator[](size_t i) const { return _data[i]; }

            //-----------------------------------------------------------------
            /*! \brief get value at i

            Return a reference to the value at linear index i. This method
            performs index checking. 
            \throws index_error if i exceeds array size
            \param i linear index of element
            \return reference to the value at i
            */
            value_type &at(size_t i) 
            { 
                try
                {
                    return _data.at(i); 
                }
                catch(std::out_of_range &error)
                {
                    std::stringstream ss;
                    ss<<"Index "<<i<<" is out of range ("<<size()<<")!";
                    throw index_error(EXCEPTION_RECORD,ss.str());
                }
            
            } 

            //-----------------------------------------------------------------
            /*! \brief get value at i

            Return the value of element i. This method
            performs index checking. 
            \throws index_error if i exceeds array size
            \param i linear index of element
            \return value at i
            */
            value_type at(size_t i) const 
            { 
                try
                {
                    return _data.at(i); 
                }
                catch(std::out_of_range &error)
                {
                    std::stringstream ss;
                    ss<<"Index "<<i<<" is out of range ("<<size()<<")!";
                    throw index_error(EXCEPTION_RECORD,ss.str());
                }
            
            } 

            //-----------------------------------------------------------------
            /*!
            \brief insert value at index i

            Insert value at index i. 
            \throws index_error if i exceeds the size of the array
            \param i linear index of the element
            \param value the value to store at index i
            */
            void insert(size_t i,const value_type &value)
            {
                at(i)=value;
            }

            //-----------------------------------------------------------------
            /*!
            \brief multiindex access

            The () operator allows multindex access to the data stored in the
            array. Like the [] operator it does not perform any checks of index
            ranges and should thus be used with care. However, due to the
            missign checks it is extremely fast. If index checking is required
            have a look the corresponding at() member function.

            \tparam ITYPES index types
            \param indexes list of index values
            \return reference to the value at the given index
            */
            template<typename... ITYPES>
            value_type &operator()(ITYPES... indexes)
            {
                std::array<size_t,sizeof...(ITYPES)> buffer{{indexes...}};

                return _data[_imap.offset(buffer)];
            }

            //-----------------------------------------------------------------
            /*!
            \brief multiindex access

            The () operator allows multindex access to the data stored in the
            array. Like the [] operator it does not perform any checks of index
            ranges and should thus be used with care. However, due to the
            missign checks it is extremely fast. If index checking is required
            have a look the corresponding at() member function.

            \tparam ITYPES index types
            \param indexes list of index values
            \return value at the given index
            */
            //-----------------------------------------------------------------
            template<typename... ITYPES>
            value_type operator()(ITYPES ...indexes) const
            {
                std::array<size_t,sizeof...(ITYPES)> buffer{{indexes...}};

                return _data[_imap.offset(buffer)];
            }


            //-----------------------------------------------------------------
            /*!
            \brief reference to first element

            Return a reference to the first element in the linear view of the
            array.
            \return reference to first element
            */
            value_type &front() { return _data.front(); }

            //-----------------------------------------------------------------
            /*!
            \brief value of first element

            Return the value of the first element in the linear view of the
            array.
            \return value of the first element
            */
            value_type front() const { return _data.front(); }

            //-----------------------------------------------------------------
            /*!
            \brief reference to last element

            Return a reference to the last element in the linear view of the
            array.
            \return reference to last element
            */
            value_type &back() { return _data.back(); }

            //-----------------------------------------------------------------
            /*!
            \brief value of last element

            Return the value of the last element in the linear view of the
            array. 
            \return value of last element
            */
            value_type back() const { return _data.back(); }

            //-----------------------------------------------------------------
            /*! \brief iterator to first element

            Returns a non-const iterator to the first element in the array.
            \return iterator to first element
            */
            iterator begin() { return _data.begin(); }

            //-----------------------------------------------------------------
            /*! \brief iterator to last element

            Returns a non-const iterator to the last element in the array. 
            \return iterator to last element
            */
            iterator end() { return _data.end(); }

            //-----------------------------------------------------------------
            /*! \brief const-iterator to first element

            Returns a const-iterator to the first element in the array.
            \return iterator to first element
            */
            const_iterator begin() const { return _data.begin(); }

            //-----------------------------------------------------------------
            /*! \brief const-iterator to last element

            Returns a const-iterator to the last element in the array.
            \return iterator to last element
            */
            const_iterator end() const { return _data.end(); }

            //-----------------------------------------------------------------
            //! return reverse iterator to last element
            reverse_iterator rbegin() { return _data.rbegin(); }

            //-----------------------------------------------------------------
            //! return const reverse iterator to last element
            const_reverse_iterator rbegin() const { return _data.rbegin(); }

            //-----------------------------------------------------------------
            //! return reverse iterator to 0-1 element
            reverse_iterator rend() { return this->_data.rend(); }

            //-----------------------------------------------------------------
            //! return const reverse iterator to 0-1 element
            const_reverse_iterator rend() const { return _data.rend(); }


    };

    //set data for static member attribute
    template<typename STORAGE,typename IMAP>
    const type_id_t mdarray<STORAGE,IMAP>::type_id = 
    type_id_map<typename STORAGE::value_type>::type_id;
    //=====================non-member operators================================

    /*!
    \brief output operator

    Writes content of a DArray to an output stream. 
    \param o output stream
    \param a array to output
    \return output stream
    */
    template<typename STORAGE,typename IMAP>
    std::ostream &operator<<(std::ostream &o,const mdarray<STORAGE,IMAP> &a)
    {
        for(auto iter = a.begin();iter!=a.end();++iter)
            o<<*iter<<" ";

        return o;
    }

    //-------------------------------------------------------------------------
    /*!
    \brief input stream operator

    Read data from an input stream. 
    \param is input stream
    \param a array where to store the data
    \return reference to input stream
    */
    template<typename STORAGE,typename IMAP>
    std::istream &operator>>(std::istream &is,mdarray<STORAGE,IMAP> &a)
    {
        for(auto iter=a.begin();iter!=a.end();++iter)
            is>>*iter;

        return is;
    }
   
    //-------------------------------------------------------------------------
    template<typename STORAGE,typename IMAP>
    bool operator==(const mdarray<STORAGE,IMAP> &b1, 
                    const mdarray<STORAGE,IMAP> &b2) 
    {
        return std::equal(b1.begin(),b1.end(),b2.begin());
    }

    //-------------------------------------------------------------------------
    template<typename STORAGE,typename IMAP>
    bool operator!=(const mdarray<STORAGE,IMAP> &b1, 
                    const mdarray<STORAGE,IMAP> &b2) 
    {
        if (!(b1 == b2)) return true;

        return false;
    }



}
}
