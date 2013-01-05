/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 * along with lipniutils.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Created on: Jul 10, 2012
 *     Author: Eugen Wintersberger
 *
 */
#pragma once

#include <iostream>
#include <sstream>

#include "SizeType.hpp"
#include "Exceptions.hpp"
#include "ExceptionUtils.hpp"

namespace pni{
namespace core{


    //=========================================================================
    /*!
    \ingroup index_mapping_classes
    \brief static array shape type

    This type can be used to represent a static array shape. The shape object is
    entirely determined at compile time by its template parameters. 
    For instance, the following code creates a static shape of size 4x10
    \code
    StaticCIndexMap<4,10> im;
    \endcode
    As this type cannot be configured at runtime it is perfectly suited for
    static the creation of n-dimensional static array types like matrices or
    vectors. 
    \tparam DIMS number of elements along each dimension
    */
    template<size_t ...DIMS> class StaticCIndexMap
    {
        private:
            //! static buffer holding the data
            static const size_t _dims[sizeof ...(DIMS)];  

            //===================private classes===============================
            //! \cond NO_API_DOC
            //-------------------internal type computing the stride------------
            //template to compute the stride for a particular dimension
            template<size_t N,size_t CNT,bool DO,size_t ...DDIMS> 
                struct Stride {};

            //no computation - just continue with the next dimension value
            template<size_t N,size_t CNT,size_t d, size_t ...DDIMS> 
                struct Stride<N,CNT,false,d,DDIMS...>
            {
                //stride value
                static const size_t value = 1*Stride<N,CNT+1,((CNT+1)>N),DDIMS...>::value; 
            };

            //perform computation
            template<size_t N,size_t CNT,size_t d,size_t ...DDIMS> 
                struct Stride<N,CNT,true,d,DDIMS...>
            {
                //stride value
                static const size_t value = d*Stride<N,CNT+1,((CNT+1)>N),DDIMS...>::value;
            };

            //break condition for the computation if only one dimension is left
            //and a value should be computed
            template<size_t N,size_t CNT,size_t D> struct Stride<N,CNT,true,D>
            {
                static const size_t value = D; // stride value
            };
    
            //break condition for the computation if only one dimension is left
            //and no value should be computed
            template<size_t N,size_t CNT,size_t D> struct Stride<N,CNT,false,D>
            {
                //!< stride value
                static const size_t value = 1; 
            };

            //----------------internal type computing the offset---------------
            //compute offset
            template<size_t D,bool FINISHED,size_t ...NDIMS> struct Offset
            {
                template<typename CTYPE> 
                    static size_t offset(typename CTYPE::const_iterator c)
                {
                    return Stride<D,0,false,DIMS...>::value*(*c)+
                           Offset<D+1,((D+1)>=(sizeof...(NDIMS))),NDIMS...>::
                           template offset<CTYPE>(++c);
                }
            };

            //break condition for the recursion for offset computation
            template<size_t D,size_t ...NDIMS> struct Offset<D,true,NDIMS...>
            {
                template<typename CTYPE> 
                    static size_t offset(typename CTYPE::const_iterator c)
                {
                   return 0;
                }
            };

            //-----------------internal type for index computation-------------
            template<size_t D,bool ITERATE,size_t ...NDIMS> struct Index
            {
                template<typename CTYPE> 
                    static void index(size_t offset,typename CTYPE::iterator c)
                {
                        size_t t = offset%Stride<D,0,false,NDIMS...>::value;
                        *c = (offset-t)/Stride<D,0,false,NDIMS...>::value;
                        Index<D+1,((D+1)<((sizeof ...(NDIMS))-1)),NDIMS...>::template
                            index<CTYPE>(t,++c);
                }
            };

            template<size_t D,size_t ...NDIMS> struct Index<D,false,NDIMS...>
            {
                template<typename CTYPE> 
                    static void index(size_t offset,typename CTYPE::iterator c)
                {
                        size_t t = offset%Stride<D,0,false,NDIMS...>::value;
                        *c = (offset-t)/Stride<D,0,false,NDIMS...>::value;
                }
            };
            //! \endcond
            //==============private member functions===========================
            /*! 
            \brief compute offset 

            Computes the memory offset to a multidimensional index which is
            passed by the user as a variadic template. This private method is
            called recursively until a break condition is reached.
            \tparam d dimension counter
            \tparam ITYPES index types
            \param i1 actual index whose contribute to the offset is computed
            \param indices the residual indices in the variadic argument list
            \return memory offset
            */
            template<size_t d,typename ...ITYPES> 
            size_t _offset(size_t i1,ITYPES ...indices) const
            {
                //check_index(i1,_dims[d],EXCEPTION_RECORD);
               
                /*
                return StrideCalc<DIMS...>::template value<d>()*i1+
                       _offset<d+1>(indices...);
                */
                return Stride<d,0,false,DIMS...>::value *i1+
                       _offset<d+1>(indices...);
            }

            //-----------------------------------------------------------------
            /*! 
            \brief compute offset - break condition

            The break condition for the recursive offset computation from an
            index passed as a variadic argument list.
            \tparam d index counter
            \param i the last index to process
            \return offset value
            */
            template<size_t d> size_t _offset(size_t i) const 
            { 
                //check_index(i,this->_dims[d],EXCEPTION_RECORD);

                return Stride<d,0,false,DIMS...>::value*i; 
            }

            /*!
            \brief compute offset - break condition

            This special break condition is called in cases where the index map
            has to handle only a 1D array. 
            */
            template<size_t d> size_t _offset() const { return 0; }

        public:
            //! default constructor
#ifdef NOCEXPR
            StaticCIndexMap() {}
#else
            constexpr StaticCIndexMap() { }
#endif
            
            //-----------------------------------------------------------------
            /*! 
            \brief get number of dimensions

            Return the number of dimensions of the shape object.
            \return number of dimensions
            */
            size_t rank() const { return sizeof...(DIMS); }

            //-----------------------------------------------------------------
            /*! 
            \brief get number of elements

            Return the total number of elements described by the shape object.
            \return number of elements
            */
            size_t size() const { return SizeType<DIMS...>::size;}

            //-----------------------------------------------------------------
            /*! 
            \brief get shape

            Return the number of elements along each dimension in a container 
            specified by the user. The container can be each STL or other type
            that conforms to the STL forward iterator interface. 
            This example shows how to use this 
            \code
            StaticCIndexMap<3,4,5,2> map;
            auto map.shape<std::vector<size_t> >();
            \endcode

            \tparam CONTAINER  container type
            \return container with elements along each dimension
            */
            template<typename CONTAINER> CONTAINER shape() const
            {
                CONTAINER c(this->rank());

                size_t index = 0;
#ifdef NOFOREACH
                for(auto iter = c.begin();iter!=c.end();++iter)
                {
                    typename CONTAINER::value_type &v = *iter;
#else
                for(typename CONTAINER::value_type &v: c)
                {
#endif
                    v = this->_dims[index++];
                }

                return c;
            }

            //-----------------------------------------------------------------
            /*! 
            \brief compute offset

            Compute an offset from a multidimensional index passed as a variadic
            argument list. This method is quite comfortable as this example
            shows
            \code
            StaticCIndexMap<3,4,5> map;

            size_t offset = map.offset(1,2,3);
            \endcode
            The method produces a compile time error if the number of indices
            does not match the rank of the shape.

            \tparam ITYPES index types
            \param i1 parameter treated in this incarnation of this function
            \param indices the indices along each dimension
            \return offset value
            */
            template<typename ...ITYPES >
                size_t offset(size_t i1,ITYPES ...indices) const
            {
                //in cases where the number of arguments do not match the rank
                //of the shape this will throw a compile time error
                static_assert((sizeof...(DIMS)) == (sizeof...(indices)+1),
                              "Number of indices does not match shape rank!");

                return Stride<0,0,false,DIMS...>::value*i1+
                       _offset<1>(indices...);
            }

            //-----------------------------------------------------------------
            /*! 
            \brief return offset 

            Return the offset of a multidimensional index pass to the function
            as a container. If the size of the index container is not equal to
            the rank of the shape object a ShapeMissmatchError is thrown.
            \code
            StaticCIndexMap<3,4,5> map;
            std::vector<size_t> index{1,2,3};
            size_t offset = map.offset(index);
            \endcode
            \throws ShapeMissmatchError if rank and container size do not match
            \throws IndexError if one of the indices exceeds the number of
            elements along its dimensions
            \param c container with indices
            \return offset value
            */
            template<template<typename...> class CTYPE,typename ...OTS> 
                size_t offset(const CTYPE<OTS...> &c) const
            {
                if(c.size() != this->rank())
                {
                    std::stringstream ss;
                    ss<<"Size of container ("<<c.size()<<") does not match";
                    ss<<" rank ("<<this->rank()<<")!";
                    throw ShapeMissmatchError(EXCEPTION_RECORD,ss.str());
                }

                size_t index = 0;
#ifdef NOFOREACH
                for(auto iter = c.begin();iter!=c.end();++iter)
                {
                    auto i = *iter;
#else
                for(auto i: c)
                {
#endif
                    if(i>=this->_dims[index++])
                    {
                        std::stringstream ss;
                        ss<<"Index "<<--index<<" is "<<i;
                        ss<<" and exceeds its maximum value";
                        ss<<"of "<<this->_dims[--index]<<"!";
                        throw IndexError(EXCEPTION_RECORD,ss.str());
                    }
                }
                
                return Offset<0,false,DIMS...>::template
                    offset<CTYPE<OTS...> >(c.begin());
            }

            //-----------------------------------------------------------------
            /*! 
            \brief compute the index

            Compute the index belonging to a particular linear memory offset.
            The targeting container is passed as the second argument of the
            method. It is assumed that the size of the container matches the
            rank of the shape.
            \throws ShapeMissmatchError if container size and shape rank do not
            match
            \throws SizeMissmatchError if offset exceeds the total size of the
            shape
            \param offset linear offset 
            \param c target container
            */
            template<template<typename...> class CTYPE,typename ...OTS> 
                void index(size_t offset,CTYPE<OTS...> &c) const
            {
                if(c.size() != this->rank())
                {
                    std::stringstream ss;
                    ss<<"Size of container ("<<c.size()<<") does not match";
                    ss<<" rank ("<<this->rank()<<")!";
                    throw ShapeMissmatchError(EXCEPTION_RECORD,ss.str());
                }

                if(offset >= this->size())
                {
                    std::stringstream ss;
                    ss<<"Offset "<<offset<<" exceeds shape size ";
                    ss<<this->size()<<"!";
                    throw SizeMissmatchError(EXCEPTION_RECORD,ss.str());
                }

                Index<0,true,DIMS...>::template index<CTYPE<OTS...> >(offset,c.begin());
            }

            //-----------------------------------------------------------------
            /*! 
            \brief compute the index from an offset

            Compute the index from an offset and return it in a container. 
            \throws SizeMissmatchError if o exceeds the size of the shape
            \tparam CTYPE container type
            \param o offset value 
            \return the container with the indices
            */
            template<typename CTYPE> CTYPE index(size_t o) const
            {
                CTYPE c(this->rank());

                this->index(o,c);
                return c;
            }

    };

    //ensure that the dimension data is loaded into the buffer
    template<size_t ...DIMS> 
        const size_t StaticCIndexMap<DIMS...>::_dims[sizeof...(DIMS)] = {DIMS...};

//end of namespace
}
}
