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
 * Declaration of the ArrayView template
 *
 * Created on: May 14, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */


#pragma once

#include <memory>
#include <functional>
#include "index_map/index_maps.hpp"
#include "container_iterator.hpp"
#include "array_selection.hpp"

namespace pni{
namespace core{
    
    /*! \ingroup multidim_array_classes
    \brief provides a view on a part of an array

    The ArrayView class provides a view on the part of an array. No new memory
    is allocated. 
    An array view can be obtained from an array using the () operator. 
    \code
    darray<float32> a(std::vector<size_t>{3,4,10});

    //create a (4,10) view from the above array 
    auto view = a(1,slice{0,4},Slice{0,10});

    //the view can now be used like any other array - however, no new memory is
    //allocated.

    //create an array from the view
    darray<float32> roi(view.shape<std::vector<size_t> >(),
                        darray<float32>::storage_type(view));
    \endcode

    
    */
    template<typename ATYPE> class array_view
    {
        public:
            //====================public types=================================
            //! storage type
            typedef ATYPE storage_type;
            //! type of the data values
            typedef typename ATYPE::value_type value_type;             
            //! type of the view 
            typedef array_view<storage_type> array_type;
            //! shared pointer type
            typedef std::shared_ptr<array_type> shared_ptr;
            //! unique pointer type
            typedef std::unique_ptr<array_type> unique_ptr; 
            //! iterator type
            typedef container_iterator<array_type> iterator;      
            //! const iterator type
            typedef container_iterator<const array_type> const_iterator; 
            //! view type
            typedef array_view<array_type> view_type;
            //! index type
            typedef std::vector<size_t> index_type;
            //! inplace arithetic type
            typedef typename ATYPE::inplace_arithmetic inplace_arithmetic;
            //! map type
            typedef index_map<index_type,typename ATYPE::map_type::policy_type> map_type;
            //========================public members===========================
            //! type id of the value_type
            static const size_t type_id = ATYPE::type_id;
        private:
            //! parent array from which to draw data
            std::reference_wrapper<ATYPE> _parray; 
            //! selection object for index transformation 
            array_selection<typename ATYPE::map_type::storage_type> _selection;
            //! local index map - only used internally, this map describes the
            //view not the original array.
            map_type _imap;
            //! local index buffer for index calculations
            mutable index_type _index;

        public:
            //-----------------------------------------------------------------
            /*! \brief constructor

            Constructs a new ArrayView from an existing array and some
            additional information.
            \param a reference to the original array
            \param s selection object defining the description
            dimension
            */
            template<typename INDEXT>
            array_view(storage_type &a,const array_selection<INDEXT> &s):
                _parray(std::ref(a)),
                _selection(s),
                _imap(map_utils<map_type>::create(_selection.template
                            shape<index_type>())),
                _index(a.rank())
            { }

            //-----------------------------------------------------------------
            //! copy constructor
            array_view(const array_type &c):
                _parray(c._parray),_selection(c._selection),
                _imap(c._imap),
                _index(c._index)
            {}

            //-----------------------------------------------------------------
            //! move constructor
            array_view(array_type &&c):
                _parray(std::move(c._parray)),
                _selection(std::move(c._selection)),
                _imap(std::move(c._imap)),
                _index(std::move(c._index))
            {}

            //-----------------------------------------------------------------
            /*!
            \brief copy assignment operator

            */
            array_type &operator=(const array_type &a)
            {
                if(this == &a) return *this;

                _parray = a._parray;
                _selection = a._selection;
                _imap = a._imap;
                _index = a._index;

                return *this;
            }

            array_type &operator=(array_type &&a)
            {
                if(this == &a) return *this;

                _parray = std::move(a._parray);
                _selection = std::move(a._selection);
                _imap = std::move(a._imap);
                _index = std::move(a._index);

                return *this;
            }



            //==================public member functions========================
            /*! \brief access with container index 

            Using a container object to hold the multidimensional indices to
            access view data. 
            \throws shape_mismatch_error if size of container does not match
            view rank
            \param index container with multidimensional index
            \return reference to value at index
            */
            template<typename CTYPE,
                     typename = typename std::enable_if<
                     std::is_unsigned<typename CTYPE::value_type>::value
                     >::type
                    >
            value_type &operator()(const CTYPE &index)
            {
                _selection.index(index,_index);
                return _parray(_index);
            }

            //-----------------------------------------------------------------
            /*! \brief access with container index 

            Using a container object to hold the multidimensional indices to
            access view data. 
            \throws shape_mismatch_error if size of container does not match
            view rank
            \param index container with multidimensional index
            \return value at index
            */
            template<typename CTYPE,
                     typename = typename std::enable_if<
                     std::is_unsigned<typename CTYPE::value_type>::value 
                     >::type
                    >
            value_type operator()(const CTYPE &index) const
            {
                _selection.index(index,_index);
                return _parray(_index);
            }


            //-----------------------------------------------------------------
            /*! \brief multidimensional access to data

            () operator allows access to the data using a multidimensional
            index represented by the arguments of the operator. 
            \code 
            darray<Float32> data({100,200,100});
            auto view = data(slice(50,75),slice(0,200),slice(25,41));
            std::cout<<view(3,34,10)<<std::endl;
            \endcode
            This works essentially the same as for the Array template.
            \tparam ITypes index types
            \param indices instances of ITypes determining the index
            \return reference to the value at multidimensional index
             */
            template<typename ...ITypes> 
            value_type & operator()(ITypes ...indices)
            {
                typedef std::array<size_t,sizeof...(ITypes)> array_t;
                return (*this)(array_t{{size_t(indices)...}});
            }

            //-----------------------------------------------------------------
            /*! \brief multidimensional access to data

            () operator allows access to the data using a multidimensional
            index represented by the arguments of the operator. 
            \code 
            darray<float32> data({100,200,100});
            auto view = data(slice(50,75),slice(0,200),slice(25,41));
            std::cout<<view(3,34,10)<<std::endl;
            \endcode
            This works essentially the same as for the Array template.
            \tparam ITypes index types
            \param indices instances of ITypes determining the multidimensional
            index
            \return value at multidimensional index
             */
            template<typename ...ITypes> 
            value_type operator()(ITypes ...indices) const
            {
                typedef std::array<size_t,sizeof...(ITypes)> array_t;
                return (*this)(array_t{{size_t(indices)...}});
            }

            //-----------------------------------------------------------------
            /*! \brief get shape of the view

            This returns the shape of the array view. This shape includes only
            those dimensions where the number of elements along the original
            array is not equal 1. 
            \return Shape object
            */
            template<typename CTYPE> CTYPE shape() const
            {
                return _selection.template shape<CTYPE>();
            }

            //-----------------------------------------------------------------
            /*! \brief linearzed access

            Provides access to the linearized data. With this operator
            linear access is provided to the elements of the view.
            \throws memory_access_error if some of the involved objects is not
            allocated
            \param i linear index of the element
            \return reference to the value at index i 
            */
            value_type &operator[](size_t i)
            {
#ifdef DEBUG
                check_index(i,size(),EXCEPTION_RECORD);
#endif
                //compute the multidimensional index in the original array for
                //the linear index i in the view
                auto index = _imap.template index<index_type>(i);
                return (*this)(index); 
            }

            //-----------------------------------------------------------------
            /*! \brief linearized access

            Provides const access to the linearized data. With this operator
            linear access is provided to the elements of the view.
            \throws memory_access_error if some of the involved objects is not
            allocated
            \param i linear index of the element
            \return value at index i 
            */
            value_type operator[](size_t i) const
            {
#ifdef DEBUG
                check_index(i,size(),EXCEPTION_RECORD);
#endif
                //compute the multidimensional index in the original array for
                //the linear index i in the view
                auto index = _imap.template index<index_type>(i);
                return (*this)(index); 
            }

            //-----------------------------------------------------------------
            /*!
            \brief get value at index i

            Return a reference to the element at linear index i within the view. 
            Unlike the [] operators this member function will throw an exception
            if the index exceeds the size of the view.

            \throws index_error in case that the index exceeds the size of the
            view
            \param i index at which to get the data
            \return reference to the element at index i
            */
            value_type &at(size_t i) 
            { 
                check_index(i,size(),EXCEPTION_RECORD); 
                return (*this)[i]; 
            }

            //-----------------------------------------------------------------
            /*!
            \brief get value at index i

            Return the value of the element at linear index i within the view. 
            Unlike the [] operators this member function will throw an exception
            if the index exceeds the size of the view.

            \throws index_error in case that the index exceeds the size of the
            view
            \param i index at which to get the data
            \return reference to the element at index i
            */
            value_type at(size_t i) const 
            { 
                check_index(i,size(),EXCEPTION_RECORD);
                return (*this)[i]; 
            }

            //-----------------------------------------------------------------
            void insert(size_t i,const value_type &v) { at(i) = v; }

            //-----------------------------------------------------------------
            value_type &front() { return at(0); }

            //-----------------------------------------------------------------
            value_type front() const { return at(0); }

            //-----------------------------------------------------------------
            value_type &back() { return at(size()-1); }

            //-----------------------------------------------------------------
            value_type back() const { return at(size()-1); }

            //-----------------------------------------------------------------
            /*! \brief get size

            Return the total number of elements referenced by this view. 
            \return total number of elements
            */
            size_t size() const
            {
                return _selection.size();
            }

            //-----------------------------------------------------------------
            //! get rank of the view
            size_t rank()  const { return _selection.rank(); }

            //-----------------------------------------------------------------
            /*! \brief iterator to first element

            Return an interator to the first element of the array view. 
            \return iterator to the first element
            */
            iterator begin() { return iterator(this,0); }

            //-----------------------------------------------------------------
            /*! \brief iterator to last element

            Return an iterator to the last element of the array view.
            \return iterator to last element
            */
            iterator end() { return iterator(this,this->size()); }
           
            //-----------------------------------------------------------------
            /*! \brief const iterator to first element

            Return an const interator to the first element of the array view. 
            \return iterator to the first element
            */
            const_iterator begin() const { return const_iterator(this,0); }

            //-----------------------------------------------------------------
            /*! \brief const iterator to last element

            Return an const iterator to the last+1 element of the array view.
            The iterator is thus invalid.
            \return iterator to last element
            */
            const_iterator end() const { return const_iterator(this,size()); }
            
            //==========implementation of unary arithmetic operators===========
            // these function will be only available if the value types of all
            // involved containers are numeric

            /*!
            \brief unary addition of a scalar

            \code
            array_type a = ...;
            array_type::value_type s = ...;
            auto view = a(0,slice(0,100),slice(3,23));

            view += s;
            \endcode
            \param s the scalar value to add
            \return view reference
            */
            array_type &operator+=(value_type s) 
            { 
                storage_type::inplace_arithmetic::add(*this,s); 
                return *this;
            }

            //-----------------------------------------------------------------
            /*!
            \brief unary addition of an array 

            \code
            array_type1 a = ...;
            array_tyep2 b = ...;
            auto view = a(1,slice(0,100),slice(3,23));

            view += b;
            \endcode

            \tparam RTYPE type of the array to add
            \param v reference to the array to add 
            \return reference to the original view
            */
            template<typename RTYPE> 
            array_type &operator+=(const RTYPE &v) 
            { 
                storage_type::inplace_arithmetic::add(*this,v); 
                return *this;
            }

            //-----------------------------------------------------------------
            /*!
            \brief unary subtraction of a scalar

            \code
            array_type a = ...;
            array_type::value_type s = ...;
            auto view = a(0,slice(0,100),slice(3,23));

            view -= s;
            \endcode
            \param s the scalar value to subtract
            \return view reference
            */
            array_type &operator-=(value_type s) 
            { 
                storage_type::inplace_arithmetic::sub(*this,s); 
                return *this;
            }

            //-----------------------------------------------------------------
            /*!
            \brief unary subtraction of an array

            \code
            array_type1 a = ...;
            array_tyep2 b = ...;

            auto view = a(0,slice(0,100),slice(2,23));

            view -= b;
            \endcode

            \tparam RTYPE type of the array to subtract
            \param v reference to the array to subtract 
            \return reference to the original view
            */
            template<typename RTYPE> 
            array_type &operator-=(const RTYPE &v) 
            { 
                storage_type::inplace_arithmetic::sub(*this,v); 
                return *this;
            }

            //-----------------------------------------------------------------
            /*!
            \brief unary multiplication of a scalar

            \code
            array_type a = ...;
            array_type::value_type s = ...;
            auto view = a(slice(0,100),10,slice(2,23));

            view *= s;
            \endcode
            \param s the scalar value to multiply with
            \return view reference
            */
            array_type &operator*=(value_type s) 
            { 
                storage_type::inplace_arithmetic::mult(*this,s); 
                return *this;
            }

            //-----------------------------------------------------------------
            /*!
            \brief unary multiplication of an array

            \code
            array_type1 a = ...;
            array_tyep2 b = ...;
            auto view = a(slice(0,100),100,slice(2,102));

            view *= b;
            \endcode

            \tparam RTYPE type of the array to multiply 
            \param v reference to the array to multiply 
            \return reference to the original view
            */
            template<typename RTYPE>
            array_type &operator*=(const RTYPE &v) 
            { 
                storage_type::inplace_arithmetic::mult(*this,v); 
                return *this;
            }

            //-----------------------------------------------------------------
            /*!
            \brief unary division of a scalar

            \code
            array_type a = ...;
            array_type::value_type s = ...;
            auto view = a(slice(0,100),slice(2,3),slice(4,10));

            view /= s;
            \endcode
            \param s the scalar value to divide by
            \return array reference
            */
            array_type &operator/=(value_type s) 
            {
                storage_type::inplace_arithmetic::div(*this,s); 
                return *this;
            }

            //-----------------------------------------------------------------
            /*!
            \brief unary division of an array

            \code
            array_type1 a = ...;
            array_tyep2 b = ...;
            auto view = a(slice(0,100),10,10);

            view /= b;
            \endcode

            \tparam RTYPE type of the array to divide by  
            \param v reference to the array to divide by 
            \return reference to the original view
            */
            template<typename RTYPE>
            array_type &operator/=(const RTYPE &v) 
            { 
                storage_type::inplace_arithmetic::div(*this,v); 
                return *this;
            }

            //-----------------------------------------------------------------
            map_type map() const
            {
                return _imap;
            }
    };




//end of namespace
}
}
