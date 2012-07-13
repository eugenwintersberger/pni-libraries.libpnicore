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
 * Static array template.
 *
 * Created on: 24.05.2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef __STATICARRAY_HPP__
#define __STATICARRAY_HPP__

#include "Types.hpp"
#include "StaticBuffer.hpp"
#include "StaticShape.hpp"
#include "Exceptions.hpp"
#incldue "ArrayViewSelector.hpp"

namespace pni{
namespace utils{

    /*! 
    \ingroup data_classes
    \brief static array 

    Static arrays are multidimensional arrays which can be used to represent
    arrays whose size is fixed at compile time. Thus, the memory requirement for
    such an array should be sufficiently small (basically not more than the
    buffer required to store the data). This is quite usefull in the case where
    many arrays (think about matrices) must be stored. In such a case the memory
    overhead due to administrative data structures can become critical. 

    Lets have a look on how we use such an array 
    \code

    //create a static array of shape 4x5x10 of type double
    StaticArray<double,4,5,10> array;

    //data access is as usuall with the () operator
    double v = array(1,4,8);


    //global assignment works too
    array = 10;

    
    \endcode

    */
    template<typename T,size_t ...DIMS> class StaticArray
    {
        private:
            StaticBuffer<T,SizeType<DIMS...>::size > _data;     //!< static buffer holding the data
            StaticShape<DIMS...> _shape; //!< static shape describing the arrays dimensionality
        public:
            //================public types=====================================
            typedef T value_type; //!< data type of the elements stored in the array
            typedef std::shared_ptr<StaticArray<T,N> > shared_ptr; //!< shared pointer to this type
            typedef std::unique_ptr<StaticArray<T,N> > unique_ptr; //!< unique pointer to this type
            typedef StaticBuffer<T,N>::iterator iterator; //!< iterator
            typedef StaticBuffer<T,N>::const_iterator const_iterator; //!< const iterator
            //===============public members====================================
            static const TypeID type_id = TypeIDMap<T>::type_id;
                
            //=================constructors and destructor=====================
            //! copy constructor from a container type
            template<typename CTYPE> explicit StaticArray(const CTYPE &a)
            {
                check_equal_size(*this,a,"template<typename CTYPE> explicit "
                                         "StaticArray(const CTYPE &a)");

                //copy data
                size_t cnt = 0;
                for(auto v: a) (*this)[cnt++] = v;
            }

            //-----------------------------------------------------------------
            //! construct from a scalar value
            template<typename U> explicit StaticArray(const U &v)
            {
                *this = v;
            }

            //==============assignment operators===============================
            //! assignment operator of a constant
            template<typename U>
            StaticArray<T,DIMS...> &operator=(const &U value)
            {
                for(T &v: *this) v = value;
            }

            //-----------------------------------------------------------------
            /*! 
            \brief assignment from a container
            
            Assign data from a general container type to the array. 
            \throws SizeMissmatchError if the container and the array size do
            not match
            \tparam CTYPE container type
            \param c instance of type CTYPE
            */
            template<typename CTYPE>
            StaticArray<T,DIMS...> &operator=(const CTYPE &c)
            {
                if(this == &c) return *this;
                
                check_equal_size(*this,c,"template<typename CTYPE> "
                                 "StaticArray<T,DIMS...> &operator=(const "
                                 "CTYPE &c)");

                size_t i = 0;
                for(auto v: c) (*this)[i++] = v;
                return *this;
            }


            //-----------------------------------------------------------------
            //!assignment operator for a StaticArray
            StaticArray<T,DIMS...> &operator=(const StaticArray<T,DIMS...> &a)
            {
                if(this == &a) return *this;
                this->_data = a._data;
                return *this;
            }
                

            //============operators and methods for data access================
            /*! 
            \brief access data element 

            Method returning a reference to an array element identified by a 
            multidimensional array index which is passed to the method as an
            argument list. As the method returns a reference to the element read
            write access is provided to the element.
            \code
            StaticArray<Float64,3,4> array;
            Float64 value = array(1,3);
            array(1,3) = 3.4;
            \endcode
            \throws ShapeMissmatchError if number of indices do not match the
            array rank
            \param indices list of array indices
            \return reference to the array element
            */
            template<typename ...ITYPES> T &operator()(ITYPES ...indices)
            {
                return this->_data[this->_shape.offset(indices...)];
            }

            //-----------------------------------------------------------------
            /*!
            \brief return data value

            Method returning the value of an array element (read only data
            access). The element is identified by its multidimensional index
            passed to the method as an argument list. 
            \code
            StaticArray<Float64,3,4> array;
            Float64 value = array(1,3);
            \endcode
            As the method returns the value of the element it cannot be used for
            write access.
            \throws ShapeMissmatchError if the number of indices dos not match
            the rank of the array.
            \param indices element index
            \return value of the array element
            */
            template<typename ...ITYPES> T operator(ITYPES ...indices) const
            {
                return this->_data[this->_shape.offset(indices...)];
            }

            //-----------------------------------------------------------------
            /*! 
            \brief get element reference

            Returns a reference to an element determined by its multidimensional
            index. The indices are stored in a container of type CTYPE. Every
            container providing the [] operators for data access and a forward
            iterator are allowed. 
            \throws ShapeMissmatchError if container size and array rank do not
            match
            \tparam CTYPE container type
            \param c container with indices
            \return reference to the element
            */
            template<typename CTYPE> T &operator(const CTYPE &c)
            {
                return this->_data[this->_shape.offset(c)];
            }

            //-----------------------------------------------------------------
            /*! 
            \brief get element value

            Return the value of an array element determined by its
            multidimensional index. The index is provided as a container of type
            CTYPE. Every container type implementing the [] operator and an STL
            compliant forward iterator is allowed. 
            \throws ShapeMissmatchError if container size and array rank do not
            match
            \tparam CTYPE container type
            \param c container with indices
            \return value of the array element
            */
            template<typename CTYPE> T operator(const CTYPE &c) const
            {
                return this->_data[this->_shape.offset(c)];
            }

            //-----------------------------------------------------------------
            /*!
            \brief reference to element
    
            Return a reference to an array element determined by its linear
            index i. 
            \param i linear index of the element
            \return reference to element
            */
            T &operator[](size_t i) { return this->_data[i]; }

            //-----------------------------------------------------------------
            /*! 
            \brief element value

            Return the value of an array element determined by its linear index
            i.
            \param i linear index of the element
            \return element value
            */
            T operator[](size_t i) const { return this->_data[i]; }

            //-----------------------------------------------------------------
            //! get iterator to first element
            iterator begin() { return this->_data.begin(); } 
            
            //-----------------------------------------------------------------
            //! get iterator to last element
            iterator end()   { return this->_data.end(); }

            //-----------------------------------------------------------------
            //! get const iterator to first element
            const_iterator begin() const { return this->_data.begin(); }

            //-----------------------------------------------------------------
            //! get const iterator to last element
            const_iterator end() const   { return this->_data.end(): }

            //=======================inquery methods===========================
            //! get number of elements
            size_t size() const { return this->_shape.size(); }

            //-----------------------------------------------------------------
            //! get number of dimensions
            size_t rank() const { return this->_shape.rank(); }
           
            //-----------------------------------------------------------------
            /*!
            \brief get array shape

            Returns the number of elements a long each dimension in a container. 
            The container must implement the [] operator for data access as well
            as a simple forward iterator.
            \code
            StaticArray<UInt16,100,100> array;
            auto shape = array.shape<std::vector<size_t> >();
            \endcode
            \tparam CTYPE container type
            \return instance of CTYPE with shape information
            */
            template<typename CTYPE> CTYPE shape() const
            {
                return this->_shape.shape<CTYPE>();
            }

    };

//end of namespace
}
}

#endif
