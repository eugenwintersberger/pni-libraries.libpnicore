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


#include "Iterator.hpp"

namespace pni{
namespace utils{
    
    /*! \ingroup data_classes
    \brief provides a view on a part of an array

    The ArrayView class provides a view on the part of an array. No new memory
    is allocated. 
    */
    template<typename T,typename ATYPE> class ArrayView
    {
        private:
            ATYPE &_parray; //!< parent array from which to draw data
            Buffer<size_t> _shape;   //!< shape of the selection
            Buffer<size_t> _offset; //!<offset of the view
            Buffer<size_t> _stride; //!<stride of the view

            mutable std::vector<size_t> _index;  //!<a index buffer used for index computation 
            size_t _rank;            //!< rank of the view

            //-----------------------------------------------------------------
            /*! \brief compute the effective rank

            Computes the effective rank of the view. This excludes all dimension
            in the original array which have more than one element.
            \param s buffer with the shape of the selection
            */
            size_t _get_effective_rank(const Buffer<size_t> &s);
           
            //-----------------------------------------------------------------
            /*! \brief add index to a vector

            Adds the first element of a variadic index template to a vector.
            The method is called recursively until no more indices are left.
            \param index vector where to add the index
            \param i first index to ad
            \param indices residual indices
            */
            template<typename ...ITypes> 
                void _add_index(std::vector<size_t> &index,size_t i,ITypes
                        ...indices)
            {
                index.push_back(i);
                _add_index(index,indices...);
            }

            //-----------------------------------------------------------------
            //! final _add_index method 
            void _add_index(std::vector<size_t> &index) {}
           
            //-----------------------------------------------------------------
            /*! \brief load internal index container

            Loads the internal index container which has the full dimensionality
            of the original array with the content of the index provided by as
            an argument. This index has not necessarily the same rank as the
            original array. 
            \param index view index
            */
            template<template<typename,typename> class CONT,
                     typename IT,
                     typename A
                    >
                void _set_index(const CONT<IT,A> &index) const
            {
                //compute the index whith full dimensionality
                size_t j=0;
                for(size_t i=0;i<this->_shape.size();i++)
                {
                    if(this->_shape[i]!=1)
                    {
                        this->_index[i] = index[j];
                        j++;
                    }
                    else
                        this->_index[i] = 0;
                }

                //now we have to add the offset and multiply the stride
                for(size_t i=0;i<this->_index.size();i++)
                {
                    this->_index[i] =
                        this->_offset[i]+this->_stride[i]*this->_index[i];
                }

            }

        public:
            //====================public types=================================
            typedef T value_type; //!< type of the data values
            typedef std::shared_ptr<ArrayView<T,ATYPE> > shared_ptr; //!< shared pointer type
            typedef std::unique_ptr<ArrayView<T,ATYPE> > unique_ptr; //!< unique pointer type
            typedef Iterator<ArrayView<T,ATYPE>,0> iterator; //!< iterator type
            typedef Iterator<ArrayView<T,ATYPE>,1> const_iterator; //!< const iterator type
            //=============constructors and destructor=========================
            ArrayView() = delete;

            //-----------------------------------------------------------------
            /*! \brief constructor

            This constructor creates a view which includes the entire array.
            \param a reference to the original array
            */
            ArrayView(ATYPE &a):
                _parray(a),
                _shape(a.shape()),
                _offset(a.rank()),
                _stride(a.rank()),
                _index(a.rank()),
                _rank(a.rank())
            {
                //initialize member variables
                _offset = 0;
                _stride = 1;
                _index = 0;
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
            ArrayView(ATYPE &a,const std::vector<size_t> &shape,
                      const std::vector<size_t> offset,
                      const std::vector<size_t> stride):
                _parray(a),
                _shape(shape),
                _offset(offset),
                _stride(stride),
                _index(shape.size()),
                _rank(_get_effective_rank(_shape))
            { 
                //wee need to check if all the lists and shapes do match the 
                //rank of the array

            
            }

            //-----------------------------------------------------------------
            //! copy constructor
            ArrayView(const ArrayView<T,ATYPE> &o):
                _parray(o._parray),
                _shape(o._shape),
                _offset(o._offset),
                _stride(o._stride),
                _index(o._index),
                _rank(o._rank)
            {}

            //-----------------------------------------------------------------
            //! move constructor
            ArrayView(ArrayView<T,ATYPE> &&o):
                _parray(o._parray),
                _shape(std::move(o._shape)),
                _offset(std::move(o._offset)),
                _stride(std::move(o._stride)),
                _index(std::move(o._index)),
                _rank(std::move(o._rank))
            {}
            //====================assignment operators=========================
            //! copy assignment
            ArrayView<T,ATYPE> &operator=(const ArrayView<T,ATYPE> &o)
            {
                if(this == &o) return *this;
                this->_parray = o._parray;
                this->_shape = o._shape;
                this->_offset = o._offset;
                this->_stride = o._stride;
                this->_index = o._index;
                this->_rank = o._rank;
                return *this;
            }

            //-----------------------------------------------------------------
            //! move assignment
            ArrayView<T,ATYPE> &operator=(ArrayView<T,ATYPE> &&o)
            {
                if(this == &o) return *this;
                this->_parray = o._parray;
                this->_shape = std::move(o._shape);
                this->_offset = std::move(o._offset);
                this->_stride = std::move(o._stride);
                this->_index = std::move(o._index);
                this->_rank = std::move(o._rank);
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
            template<template<typename,typename> class CONT,
                     typename IT,
                     typename A
                    >
                T &operator()(const CONT<IT,A> &index)
            {

                //transform the local view index to a global index for the
                //original array
                this->_set_index(index);
                //we can use now this new index to access the data from the 
                //original array
                return this->_parray(this->_index);

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
            template<template<typename,typename> class CONT,
                     typename IT,
                     typename A
                    >
                T operator()(const CONT<IT,A> &index) const
            {
                //transform the local view index to a global index for the
                //original array
                this->_set_index(index);
                //we can use now this new index to access the data from the 
                //original array
                return this->_parray(this->_index);

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
            template<typename ...ITypes> 
                T &operator()(size_t &i,ITypes ...indices)
            {
                //store the use provided indices in a vector
                std::vector<size_t> index;
                index.push_back(i);
                _add_index(index,indices...);

                return (*this)(index);
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
            template<typename ...ITypes> 
                T operator()(size_t &i,ITypes ...indices) const
            {
                std::vector<size_t> index;

                index.push_back(i);
                _add_index(index,indices...);

                return (*this)(index);
            }



            //-----------------------------------------------------------------
            /*! \brief get shape of the view

            This returns the shape of the array view. This shape includes only
            those dimensions where the number of elements along the original
            array is not equal 1. 
            \return Shape object
            */
            Shape shape() const
            {
                std::vector<size_t> b;
                for(size_t i=0;i<this->_shape.size();i++)
                    if(this->_shape[i]!=1) b.push_back(this->_shape[i]);

                return Shape(b);
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
            T &operator[](size_t i)
            {
                Shape s = this->shape();
                auto index = s.template index<std::vector<size_t> >(i);
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
            T operator[](size_t i) const
            {
                Shape s = this->shape();
                auto index = s.template index<std::vector<size_t> >(i);
                return (*this)(index); 
            }

            //-----------------------------------------------------------------
            /*! \brief get size

            Return the total number of elements referenced by this view.
            \return total number of elements
            */
            size_t size() const
            {
                return this->shape().size();
            }

            //-----------------------------------------------------------------
            /*! \brief iterator to first element

            Return an interator to the first element of the array view. 
            \return iterator to the first element
            */
            ArrayView<T,ATYPE>::iterator begin()
            {
                return ArrayView<T,ATYPE>::iterator(this,0);
            }

            //-----------------------------------------------------------------
            /*! \brief iterator to last element

            Return an iterator to the last element of the array view.
            \return iterator to last element
            */
            ArrayView<T,ATYPE>::iterator end() 
            {
                return ArrayView<T,ATYPE>::iterator(this,this->size());
            }
           
            //-----------------------------------------------------------------
            /*! \brief const iterator to first element

            Return an const interator to the first element of the array view. 
            \return iterator to the first element
            */
            ArrayView<T,ATYPE>::const_iterator begin() const
            {
                return ArrayView<T,ATYPE>::const_iterator(this,0);
            }

            //-----------------------------------------------------------------
            /*! \brief const iterator to last element

            Return an const iterator to the last+1 element of the array view.
            The iterator is thus invalid.
            \return iterator to last element
            */
            ArrayView<T,ATYPE>::const_iterator end() const
            {
                return ArrayView<T,ATYPE>::const_iterator(this,this->size());
            }
    };

    //============implementation of private member functions====================
    template<typename T,typename ATYPE>
    size_t ArrayView<T,ATYPE>::_get_effective_rank(const Buffer<size_t> &s)
    {
        size_t rank=0;
        for(size_t i=0;i<s.size();i++)
            if(s[i]!=1) rank++;

        return rank;
    }

//end of namespace
}
}

#endif
