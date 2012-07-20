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
 * Declaration of the ArrayView template
 *
 * Created on: May 14, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */


#ifndef __ARRAYVIEW_HPP__
#define __ARRAYVIEW_HPP__


#include "CIndexMap.hpp"
#include "DBuffer.hpp"
#include "Iterator.hpp"
#include "ArraySelection.hpp"

namespace pni{
namespace utils{
    
    /*! \ingroup data_classes
    \brief provides a view on a part of an array

    The ArrayView class provides a view on the part of an array. No new memory
    is allocated. 
    */
    template<typename ATYPE> class ArrayView
    {
        private:
            //! parent array from which to draw data
            ATYPE *_parray; 
            //! selection object for index transformation 
            ArraySelection _selection;
            //! index map to produce the original selection index
            CIndexMap _imap;

        public:
            //====================public types=================================
            //! type of the data values
            typedef typename ATYPE::value_type value_type;             
            //! type of the view 
            typedef ArrayView<ATYPE> view_type;
            //! shared pointer type
            typedef std::shared_ptr<view_type> shared_ptr;
            //! unique pointer type
            typedef std::unique_ptr<view_type> unique_ptr; 
            //! iterator type
            typedef Iterator<view_type,0> iterator;      
            //! const iterator type
            typedef Iterator<view_type,1> const_iterator; 
            //========================public members===========================
            //! type id of the value_type
            static const size_t type_id = ATYPE::type_id;
            //=============constructors and destructor=========================

            ArrayView():_parray(nullptr),_selection() {}

            //-----------------------------------------------------------------
            /*! \brief constructor

            This constructor creates a view which includes the entire array.
            \param a reference to the original array
            */
            ArrayView(ATYPE &a):
                _parray(&a),
                _selection(),
                _imap()
            {
                std::vector<size_t> shape(a->shape<std::vector<size_t>());
                std::vector<size_t> offset(a->rank());
                std::vector<size_t> stride(a->rank());

                std::fill(offset.begin(),offset.end(),0);
                std::fill(stride.begin(),stride.end(),1);

                this->_selection = ArraySelection(shape,offset,stride);
                this->_imap = CIndexMap(this->_selection.shape());
            }

            //-----------------------------------------------------------------
            /*! \brief constructor

            Constructs a new ArrayView from an existing array and some
            additional information.
            \param a reference to the original array
            \param shape number of elements along each dimension 
            \param offset index offset for the view
            \param stride number of steps between each element along each
            dimension
            */
            ArrayView(ATYPE &a,const ArraySelection &s):
                _parray(&a),
                _selection(s),
                _imap(_selection.shape())
            { 
                //wee need to check if all the lists and shapes do match the 
                //rank of the array
            
            }

            //-----------------------------------------------------------------
            //! copy constructor
            ArrayView(const ArrayView<ATYPE> &o):
                _parray(o._parray),
                _selection(o._selection),
                _imap(o._imap)
            {}

            //-----------------------------------------------------------------
            //! move constructor
            ArrayView(ArrayView<ATYPE> &&o):
                _parray(o._parray),
                _selection(std::move(o._selection)),
                _imap(std::move(o._imap))
            {}
            //====================assignment operators=========================
            //! copy assignment
            ArrayView<ATYPE> &operator=(const ArrayView<ATYPE> &o)
            {
                if(this == &o) return *this;
                this->_parray = o._parray;
                this->_selection = o._selection;
                this->_imap = o._imap;
                return *this;
            }

            //-----------------------------------------------------------------
            //! move assignment
            ArrayView<ATYPE> &operator=(ArrayView<ATYPE> &&o)
            {
                if(this == &o) return *this;
                this->_parray = o._parray;
                this->_selection = std::move(o._selection);
                this->_imap = std::move(o._imap);
                o._parray = nullptr;
                return *this;
            }

            //==================public member functions========================
            /*! \brief access with container index 

            Using a container object to hold the multidimensional indices to
            access view data. 
            \throws ShapeMissmatchError if size of container does not match
            view rank
            \param index container with multidimensional index
            \return reference to value at index
            */
            template<typename CTYPE>
                value_type &operator()(const CTYPE &index)
            {
                return (*(this->_parray))(this->_selection.template
                        index<std::vector<size_t> >(index));
            }

            //-----------------------------------------------------------------
            /*! \brief access with container index 

            Using a container object to hold the multidimensional indices to
            access view data. 
            \throws ShapeMissmatchError if size of container does not match
            view rank
            \param index container with multidimensional index
            \return value at index
            */
            template<typename CTYPE>
                value_type operator()(const CTYPE &index) const
            {
                return (*(this->_parray))(this->_selection.template
                        index<std::vector<size_t> >(index));
            }


            //-----------------------------------------------------------------
            /*! \brief multidimensional access to data

            () operator allows access to the data using a multidimensional
            index represented by the arguments of the operator. 
            \code 
            Array<Float32,Buffer> data({100,200,100});
            auto view = data(Slice(50,75),Slice(0,200),Slice(25,41));
            std::cout<<view(3,34,10)<<std::endl;
            \endcode
            This works essentially the same as for the Array template.
            \return reference to the value at multidimensional index
             */
            template<typename ...ITypes> value_type &
                operator()(ITypes ...indices)
            {
                return (*this)(std::vector<size_t>{indices...});
            }

            //-----------------------------------------------------------------
            /*! \brief multidimensional access to data

            () operator allows access to the data using a multidimensional
            index represented by the arguments of the operator. 
            \code 
            Array<Float32,Buffer> data({100,200,100});
            auto view = data(Slice(50,75),Slice(0,200),Slice(25,41));
            std::cout<<view(3,34,10)<<std::endl;
            \endcode
            This works essentially the same as for the Array template.
            \return value at multidimensional index
             */
            template<typename ...ITypes> value_type 
                operator()(ITypes ...indices) const
            {
                return (*this)(std::vector<size_t>{indices...});
            }



            //-----------------------------------------------------------------
            /*! \brief get shape of the view

            This returns the shape of the array view. This shape includes only
            those dimensions where the number of elements along the original
            array is not equal 1. 
            \return Shape object
            */
            template<typename CTYPE>
            CTYPE shape() const
            {
                CTYPE s(this->rank());
                std::copy(this->_selection.shape().begin(),
                          this->_selection.shape().end(),
                          s.begin());
                return s;
            }

            //-----------------------------------------------------------------
            /*! \brief linearzed access

            Provides access to the linearized data. With this operator
            linear access is provided to the elements of the view.
            \throws MemoryAccessError if some of the involved objects is not
            allocated
            \param i linear index of the element
            \return reference to the value at index i 
            */
            ArrayView<ATYPE>::value_type &operator[](size_t i)
            {
                auto index = this->_imap.template index<std::vector<size_t> >(i);
                return (*this)(index); 
            }

            //-----------------------------------------------------------------
            /*! \brief linearized access

            Provides const access to the linearized data. With this operator
            linear access is provided to the elements of the view.
            \throws MemoryAccessError if some of the involved objects is not
            allocated
            \param i linear index of the element
            \return value at index i 
            */
            ArrayView<ATYPE>::value_type operator[](size_t i) const
            {
                auto index = this->_imap.template index<std::vector<size_t> >(i);
                return (*this)(index); 
            }

            //-----------------------------------------------------------------
            /*! \brief get size

            Return the total number of elements referenced by this view.
            \return total number of elements
            */
            size_t size() const
            {
                return this->_selection.size();
            }

            //-----------------------------------------------------------------
            size_t rank()  const { return this->_selection.rank(); }

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
            const_iterator begin() const
            {
                return const_iterator(this,0);
            }

            //-----------------------------------------------------------------
            /*! \brief const iterator to last element

            Return an const iterator to the last+1 element of the array view.
            The iterator is thus invalid.
            \return iterator to last element
            */
            const_iterator end() const
            {
                return const_iterator(this,this->size());
            }
    };




//end of namespace
}
}

#endif
