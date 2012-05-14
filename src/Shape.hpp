/*
 * Declaration of class ArrayShape
 *
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
 * along with lipniutils.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * The ArrayShape object describes the shape of an array object. It provides
 * methods for computing the linear offset from a given index vector and
 * methods for computing such an index starting from a linear offset.
 *
 * Created on: Apr 19, 2011
 *     Author: Eugen Wintersberger
 *
 */

#ifndef __SHAPE_HPP__
#define __SHAPE_HPP__

#include <string>

#include "Exceptions.hpp"
#include "Index.hpp"
#include "Types.hpp"
#include "Buffer.hpp"


namespace pni{
namespace utils{

    /*! \ingroup util_classes
    \brief Shape object

    The Shape class describes the shape of a multidimensional array.
    Such an array has a rank \f$r\f$ (the number of dimensions) and a particular
    number of elements along each dimension.
    In general such an array is stored linearly in memory.
    In particular they are important to access array data stored in a linear,
    contiguous stream of data. In all cases we assume C-ordering.
    This means that the last index in the array varies fastest.
    Each array is stored as a linear sequence of data values. To
    mimic the behavior of a multidimensional array we need to map
    each tuple of indices to a linear memory location. Consider an
    array of \f$M\f$ dimension and \f$N_i\f$ elements along each dimension.
    Furthermore we assume an multidimensional index for an array element
    \f$(i_0,i_1,....,i_{(M-1)})\f$. From this the linear memory location can be
    obtained with
    \f[
        o = \sum_{j=0}^{M-1} i_jS_j
    \f]
    where \f$S_j\f$ is the stride of each dimension which is determined by
    \f[
    S_j = \prod_{k=j}^{M-2} N_{k+1}
    \mbox{ with } S_{M-1} = 1
    \f]
    After an ArrayShape object has been instantiated all its parameters
    can be adjusted dynamically to whatever values are required.
    The class takes care about all kinds of adoptions.
    This might not be true for array classes using this ArrayShape type.
    */
    class Shape{
        private:
            Buffer<size_t> _shape;    //!< the number of values along each dimension
            Buffer<size_t> _dimstrides;  //!< the strides for the offset calculation
            size_t _size;             //!< the total number of elements in the array
           
            //-----------------------------------------------------------------
            /*! compute dimension strides

            compute the stride for each dimension - used internally to recompute
            the stride for each dimension if the shape is changed.
            */
            static Buffer<size_t> _compute_dimstrides(const Buffer<size_t> &s);

            //-----------------------------------------------------------------
            /*! compute total number of elements

            used internally to recompute the number of elements in the array
            once the shape is changed in a way so that the size is changed.
            */
            static size_t _compute_size(const Buffer<size_t> &s);
            
            //-----------------------------------------------------------------
            template<typename ...Ts>
                size_t __offset(size_t d,size_t i1,Ts... is)
            {
                EXCEPTION_SETUP("template<typename ...Ts> size_t __offset"
                                "(size_t d,size_t i1,Ts... is)");
                if(i1>=this->_shape[d])
                {
                    std::stringstream ss;
                    ss<<"Index ("<<i1<<") is exceeds maximum number of ";
                    ss<<" elements ("<<this->_shape[d]<<") along dimension";
                    ss<<" "<<d<<"!";
                    EXCEPTION_INIT(IndexError,ss.str());
                    EXCEPTION_THROW();
                }

                return _dimstrides[d]*i1+__offset(d+1,is...);
            }

            //-----------------------------------------------------------------
            size_t __offset(size_t d)
            {
                return 0;
            }
        public:
            //====================public types ================================
            typedef std::shared_ptr<Shape> shared_ptr;  //!< shared pointer type to a Shape object
            typedef std::unique_ptr<Shape> unique_ptr;  //!< unique pointer type to a Shape  object

            //======================constructors and destructor================
            //! default constructor
            explicit Shape();
            //! copy constructor

            //! Initialize an object of type ArrayShape with the content of an
            //! other ArrayShape object.
            //! \throws MemoryAllocationError if memory allocation fails
            Shape(const Shape &s);
            //! move constructor
            Shape(Shape &&s);

            /*! constructor for initialization list

            An initialization list can be used for the construction of a Shape 
            object. In code this would look somehow like this
            \code
            Shape s={3,4,6};
            \endcode
            \param list initializer list
            */
            Shape(const std::initializer_list<size_t> &list);

            /*! \brief constructor with vector

            Construct a shape object form a vector object
            */
            Shape(const std::vector<size_t> &vector);

            //! destructor
            ~Shape();
            
            //! return the array rank

            //! Returns the number of dimensions in the shape object.
            //! \return array rank
            size_t rank() const;

            //! set a single dimension of the shape object

            //! Use this method to set a single dimension in an array to a new value.
            //! If the index i is larger than the rank of the shape an exception
            //! will be raised.
            //! \throws IndexError if i exceeds the rank of the shape
            //! \param i index of the dimension to set
            //! \param d new number of elements along dimension i
            void dim(const size_t &i,const size_t &d);
            //! get a single dimension of the shape

            //! return the number of elements along dimension i. Raises an exception
            //! if i is larger than the rank of the shape.
            //! \throws IndexError if i exceeds the rank of the shape
            //! \param i index of the dimension
            //! \return the number of elements along dimension i
            size_t dim(const size_t &i) const;
            //! set all dimensions

            //! Set all dimensions using an initializer list
            void dim(const std::initializer_list<size_t> &list);

            /*! \brief set all dimensions from a vector

            Set all dimensions of the shape using a vector object.
            \param vector std::vector from which to set dimensions
            */
            void dim(const std::vector<size_t> &vector);


            //! total number of elements

            //! Returns the total number of elements that can be described by the
            //! shape.
            //! \return total number of elements
            size_t size() const {return _size;}
            
            //! compute element offset

            //! Here the element offset is computed from an initializer list.
            //! This can make reading code much easier. 
           
            /*! \brief compute offset with variadic template

            This version of the offset method uses variadic templates.
            */
            template<typename ...ITypes> size_t offset(size_t i,ITypes ...indices)
            {
                EXCEPTION_SETUP("template<typename ...ITypes> size_t "
                                "offset(size_t i,ITypes ...indices)");

                if(((sizeof...(ITypes))+1)!=rank())
                {
                    std::stringstream ss;
                    ss<<"Shape is of rank ("<<this->rank()<<") but ";
                    ss<<(sizeof...(ITypes))+1<<" indices provided!";
                    EXCEPTION_INIT(ShapeMissmatchError,ss.str());
                    EXCEPTION_THROW();
                }
                
                size_t offset = _dimstrides[0]*i+__offset(1,indices...);
                return offset;
            }

            /*! \brief offset from a general container type
            
            This method permits all kind of container types as valid index
            values. 
            
            */
            template<template<typename,typename> class CONTAINER,typename T,typename A> 
                size_t offset(const CONTAINER<T,A> &c)const;

            /*! \brief offset from an initializer list

            */
            size_t offset(const std::initializer_list<size_t> &list) const;

            //! creates index from offset

            //! Creates an index object that belongs to a particular linear offset.
            //! The Index object that is passed to the method must be allocated (rank != 0)
            //! and have the same rank as the shape object - otherwise an
            //! exception will be thrown.
            //! \throws ShapeMissmatchError if Index and ArrayShape object have different rank
            //! \throws MemoryAccessError if Index of ArrayShape object have rank 0
            //! \param offset offset for which to compute the index
            //! \param i index object where to store the result
            template<typename CONT> 
            void index(const size_t &offset,CONT &i) const;

            template<typename CONT>
                CONT index(const size_t &offset) const;


            //the assignment operator must be a member function
            //and cannot be declared as a friend function
            //! assignment operator

            //! copy assignment operator

            //! \throws MemoryAllocationError if memory allocation for the new Shape fails
            Shape &operator=(const Shape &);
            //! move assignment operator
            Shape &operator=(Shape &&o);
            
            //! equality operator for array shapes

            //! It returns true if the rank and dimension of two arrays are equal, false otherwise
            //! \return boolean value representing shape equality
            friend bool operator==(const Shape &,const Shape &);
            //! inequality operator for array shapes

            //! Returns true if either the rank or one of the dimensions in two shape objects
            //! differ.
            //! \return boolean value
            friend bool operator!=(const Shape &,const Shape &);
            //! [] operator for read access

            //! This operator allows reading access to the array dimensions. You cannot
            //! use this operator to set array dimensions. The reason for this is, that
            //! once a single dimension has been changed we would have to recalculate
            //! strides and recompute the size. However, this cannot be done easily
            //! by operator overloading.
            //! \sa void setDimension(const unsigned int &i,const unsigned int &d)
            const size_t operator[](size_t i) const;

            //! operator for console output
            friend std::ostream &operator<<(std::ostream &o,const Shape &s);
    };

    //-------------------------------------------------------------------------
    //compute an offset form an initializer list
    template<template<typename,typename> class CONTAINER,typename T,typename A>
    size_t Shape::offset(const CONTAINER<T,A> &c) const
    {
        EXCEPTION_SETUP("size_t Shape::"
                "offset(std::initializer_list<size_t> list) const");

        size_t offset = 0;

        if(!_shape.is_allocated()){
            EXCEPTION_INIT(MemoryAccessError,
                    "Shape object is not allocated (rank == 0)!");
            EXCEPTION_THROW();
        }


        if(c.size() != rank()){
            EXCEPTION_INIT(ShapeMissmatchError,
                    "Shape rank and initializer list size do not match!");
            EXCEPTION_THROW();
        }

        size_t cntr = 0;
#ifdef NOFOREACH
        for(auto iter = c.begin();iter!=c.end();iter++){
            const size_t &index = *iter;
#else
        for(const size_t &index: c){
#endif
            if(index >= dim(cntr)){
                EXCEPTION_INIT(IndexError,"Index out of bounds!");
                EXCEPTION_THROW();
            }
            offset += index*_dimstrides[cntr];
            cntr++; //increment list counter
        }

        return offset;

    }

    //-------------------------------------------------------------------------
    template<typename CONT> 
        void Shape::index(const size_t &offset,CONT &i) const
    {
        EXCEPTION_SETUP("template<typename CONT>" 
                        "void Shape::index(const size_t "
                        "&offset,CONT &i) const");

        if(!_shape.is_allocated()){
            EXCEPTION_INIT(MemoryAccessError,
                    "Shape object is not allocated (rank == 0)!");
            EXCEPTION_THROW();
        }

        if(i.size() == 0){
            EXCEPTION_INIT(MemoryAccessError,
                    "Index object is not allocated (rank == 0)!")
        }

        if(i.size() != rank()){
            EXCEPTION_INIT(ShapeMissmatchError,
                    "Shape and Index have different rank!");
            EXCEPTION_THROW();
        }

        if(offset>=size()){
            EXCEPTION_INIT(MemoryAccessError,"Offset is larger than size!");
            EXCEPTION_THROW();
        }

        size_t o,t;
        o = offset;
        for(size_t d = 0;d<rank();d++){
            t = o%_dimstrides[d];
            i[d] = (o-t)/_dimstrides[d];
            o = t;
        }

    }

    //-------------------------------------------------------------------------
    template<typename CONT>
        CONT Shape::index(const size_t &offset) const
    {
        CONT c(this->rank());

        this->index(offset,c);
        return c;

    }

//end of namespace
}
}

#endif
