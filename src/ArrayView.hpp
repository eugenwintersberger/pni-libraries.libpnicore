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


namespace pni{
namespace utils{
    class SliceManager
    {
        public:
            static size_t get_offset(const size_t &i) { return 0; }
            static size_t get_stride(const size_t &i) { return 1; }
            static size_t get_shape(const size_t &i) { return i; }

            static size_t get_offset(const Slice &s) { return s.first(); }
            static size_t get_stride(const Slice &s) { return s.stride(); }
            static size_t get_shape(const Slice &s) { return size(s); }

    };

    template<typename TUPLE,int N> class ViewExpansion
    {
        private:
            template<typename VT> 
                void extract_values(const VT &v,
                                    std::vector<size_t> &offset,
                                    std::vector<size_t> &stride,
                                    std::vector<size_t> &shape)
                {
                    offset.push_back(SliceManager::get_offset(v));
                    stride.push_back(SliceManager::get_stride(v));
                    shape.push_back(SliceManager::get_shape(v));
                }
        public:
            void expand(const TUPLE &t,
                        std::vector<size_t> &offset,
                        std::vector<size_t> &stride,
                        std::vector<size_t> &shape)
            {
                //do something here
                this->extract_values(std::get<N>(t),offset,stride,shape);
                //call the next instance
                ViewExpansion<TUPLE,N-1>::expand(t,offset,stride,shape);
            }
    };

    template<typename TUPLE> class ViewExpansion<TUPLE,1>
    {
        public:
            void expand(const TUPLE &t,
                        std::vector<size_t> &offset,
                        std::vector<size_t> &stride,
                        std::vector<size_t> &shape)
            {
                this->_extract_values(std::get<1>(t),offset,stride,shape);
            }
    };

    template<typename T,typename ATYPE> class ArrayView
    {
        private:
            ATYPE &_parray; //!< parent array from which to draw data
            Shape _shape;   //!< shape of the selection
            Buffer<size_t> _offset; //!<offset of the view
            Buffer<size_t> _stride; //!<stride of the view

            std::vector<size_t> _index;  //!<a index buffer used for index computation 
            size_t _rank;            //!< rank of the view

            size_t _get_effective_rank(const Shape &s);

        public:
            //=============constructors and destructor=========================
            ArrayView() = delete;

            //-----------------------------------------------------------------
            ArrayView(ATYPE *a):
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
            ArrayView(ATYPE &a,const Shape &shape,
                      const std::initializer_list<size_t> offset,
                      const std::initializer_list<size_t> stride):
                _parray(a),
                _shape(shape),
                _offset(offset),
                _stride(stride),
                _index(shape.rank()),
                _rank(_get_effective_rank(shape))
            { 
                //wee need to check if all the lists and shapes do match the 
                //rank of the array

            
            }



            //====================assignment operators=========================


            //==================public member functions========================
            template<template<typename,typename> class CONT,typename IT,typename A>
            T &operator()(const CONT<IT,A> &index)
            {
                //compute the index whith full dimensionality
                size_t j=0;
                for(size_t i=0;i<this->_shape.rank();i++)
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

                //we can use now this new index to access the data from the 
                //original array
                return this->_parray(this->_index);

            }

            T &operator()(const std::initializer_list<size_t> &l)
            {
                return (*this)(std::vector<size_t>(l));
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
                std::vector<size_t> sv;
                for(size_t i=0;i<_shape.rank();i++)
                    if(_shape[i]!=1) sv.push_back(_shape[i]);

                return Shape(sv);
            }
    
    };

    //============implementation of private member functions====================
    template<typename T,typename ATYPE>
    size_t ArrayView<T,ATYPE>::_get_effective_rank(const Shape &s)
    {
        size_t rank=0;
        for(size_t i=0;i<s.rank();i++)
            if(s[i]!=1) rank++;

        return rank;
    }

//end of namespace
}
}

#endif
