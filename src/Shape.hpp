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
#include "Types.hpp"
#include "DBuffer.hpp"


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
    class Shape
    {
        private:
            DBuffer<size_t> _shape;    //!< the number of values along each dimension
            DBuffer<size_t> _dimstrides;  //!< the strides for the offset calculation
            size_t _size;             //!< the total number of elements in the array
           
            //-----------------------------------------------------------------
            /*! compute dimension strides

            compute the stride for each dimension - used internally to recompute
            the stride for each dimension if the shape is changed.
            */
            static DBuffer<size_t> _compute_dimstrides(const DBuffer<size_t> &s);

            //-----------------------------------------------------------------
            /*! compute total number of elements

            used internally to recompute the number of elements in the array
            once the shape is changed in a way so that the size is changed.
            */
            static size_t _compute_size(const DBuffer<size_t> &s);
            
            //-----------------------------------------------------------------
            /*! \brief private method computing the offset

            This method computes the linear offset of a point according to its
            multidimensional index. The computation is performed by recursively
            calling the method until no more input arguments (except the first
            one) are available. 
            */
            template<typename ...Ts>
                size_t __offset(size_t d,size_t i1,Ts... is) const
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
            //! break condition for  __offset()
            size_t __offset(size_t d) const
            {
                return 0;
            }

            //-----------------------------------------------------------------
            /*! \brief compute index from offset

            This template method computes the multidimensional index from a
            linear offset. No checks are performed on the container type. It is
            assumed that is was set up correctly. 
            \throws MemoryAccessError if offset is larger than total size of the
            shape
            \param offset linear offset
            \param i container which shall hold the index
            */
            template<typename CONT> void _index(size_t offset,CONT &i) const;
        public:
            //====================public types ================================
            typedef std::shared_ptr<Shape> shared_ptr;  //!< shared pointer type to a Shape object
            typedef std::unique_ptr<Shape> unique_ptr;  //!< unique pointer type to a Shape  object

            //======================constructors and destructor================
            //! default constructor
            explicit Shape();

            //-----------------------------------------------------------------
            /*! copy constructor

            Initialize an object of type ArrayShape with the content of an
            other ArrayShape object.
            \throws MemoryAllocationError if memory allocation fails
            */
            Shape(const Shape &s);

            //-----------------------------------------------------------------
            //! move constructor
            Shape(Shape &&s);

            //-----------------------------------------------------------------
            /*! constructor for initialization list

            An initialization list can be used for the construction of a Shape 
            object. In code this would look somehow like this
            \code
            Shape s={3,4,6};
            \endcode
            \param list initializer list
            */
            Shape(const std::initializer_list<size_t> &list);

            //-----------------------------------------------------------------
            /*! \brief constructor from container

            Construct a shape object form an arbitrary container type.
            The type should follow the standard C++ container convention.
            \code
            std::vector<size_t> v{1,4,12};
            Shape s(v);
            \endcode
            \param c instance of container type CONT
            */
            template<typename CTYPE> 
                explicit Shape(const CTYPE &c):
                _shape(c.size()),
                _dimstrides(c.size()),
                _size(0)
            { 
                std::copy(c.begin(),c.end(),_shape.begin());
                _compute_dimstrides(_shape);
                _compute_size(_shape);
            }

            //-----------------------------------------------------------------
            //! destructor
            ~Shape();
            
            //====================assignment operators=========================
            //! copy assignment operator
            Shape &operator=(const Shape &);
            //! move assignment operator
            Shape &operator=(Shape &&o);
           
            //====================public memeber functions=====================
            /*! \brief return the array rank

            Returns the number of dimensions in the shape object.
            \return array rank
            */
            size_t rank() const { return _shape.size(); }


            //-----------------------------------------------------------------
            /*! get a single dimension of the shape

            return the number of elements along dimension i. Raises an 
            exception if i is larger than the rank of the shape.
            \throws IndexError if i exceeds the rank of the shape
            \param i index of the dimension
            \return the number of elements along dimension i
            */
            size_t dim(const size_t &i) const;

            //-----------------------------------------------------------------
            //! total number of elements

            //! Returns the total number of elements that can be described by the
            //! shape.
            //! \return total number of elements
            size_t size() const {return _size;}
           
            //-----------------------------------------------------------------
            /*! \brief compute linear offset from multidimensional index

            This method computes the linear offset from a point in a
            multidimensional array. The index is represented by the arguments 
            of this method which is implemented as a variadic template. 
            This makes this method quite easy to use:
            \code
            Shape s{3,5,5};
            size_t offset = s.offset(1,3,2);
            \endcode
            If the number of arguments does not match the rank of the Shape
            object an exception will be thrown. 
            \throws ShapeMissmatchError if rank does not match number of arguments 
            \return linear offset of the data
            */
            template<typename ...ITypes> 
                size_t offset(size_t i,ITypes ...indices) const
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

            //------------------------------------------------------------------
            /*! \brief offset from a general container type
            
            This method permits all kind of container types as valid index
            values. The only requirement made to the container is that it
            conforms to the standard container interface.
            \code
            std::vector<size_t> i{1,6,39};
            Shape s(...);
            s.offset(i);
            \endcode
            \throws MemoryAccessError if container size or shape rank are 0
            \throws ShapeMissmatchError if container size and shape rank do not
            match
            \throws IndexError if one of the indices exceeds the number of
            elements in its dimension
            \param c container with indices
            \return linear offset value
            */
            template<template<typename,typename> class CONTAINER,
                     typename T,typename A
                     > 
                size_t offset(const CONTAINER<T,A> &c)const;

            //-----------------------------------------------------------------
            /*! \brief offset from an initializer list

            Compute the linear offset from an initializer list. 
            \code 
            Shape s(100,1024,1024);
            s.offset({10,15,145);
            \endcode
            \throws MemoryAccessError if list length or shape rank is 0
            \throws ShapeMissmatchError if list length and shape rank do not
            match
            \throws IndexError if one of the indices exceeds the number of
            elements in its dimension
            \param list initializer list
            \return linear offset value
            */
            size_t offset(const std::initializer_list<size_t> &list) const;

            //-----------------------------------------------------------------
            /*! \brief computes indices for a linear offset

            Computes the multidimensional indices belonging to a particular
            offset value and stores them in a container of type CONT. 
            The container is assumed to be set up correctly and can hold all the
            index values. Exceptions are thrown if this is not the case.
            \code
            Shape s{100,2048,512};
            std::vector<size_t> index;
            s.index(index);
            \endcode
            \throws ShapeMissmatchError if Index and ArrayShape object have 
            different rank
            \throws MemoryAccessError if Index of Shape object have rank 0
            of the offset exceeds the total size of the shape
            \param offset offset for which to compute the index
            \param i index object where to store the result
            */
            template<typename CONT> void index(size_t offset,CONT &i) const;

            //-----------------------------------------------------------------
            /*! \brief compute indices from linear offset

            Comnputes the multidimensional indices belonging to a particular
            linear offset. The result is stored in a container which allocated
            by the method itself and returned to the caller.
            \code
            Shape s{100,244,2039};
            auto index = s.index<std::vector<size_t> >(100);
            \endcode
            \throws MemoryAccessError if offset is larger than the total size of
            the shape
            \param offset linear offset
            \return container with index values
            */
            template<typename CONT> CONT index(size_t offset) const;

           
            //-----------------------------------------------------------------
            /*! equality operator for array shapes

            It returns true if the rank and dimension of two arrays are equal, 
            false otherwise
            \return boolean value representing shape equality
            */
            friend bool operator==(const Shape &,const Shape &);

            //-----------------------------------------------------------------
            /*! inequality operator for array shapes

            Returns true if either the rank or one of the dimensions in two 
            shape objects differ.
            \return boolean value
            */
            friend bool operator!=(const Shape &,const Shape &);

            //-----------------------------------------------------------------
            /*! \brief number of elements along i

            Return the number of elements along dimension i. This operator
            performs no range check. If i exceeds the rank of the Shape the
            program will most probably terminate with a segmentation fault.
            \param i dimension index
            \return number of elements along i
            */
            size_t operator[](size_t i) const { return _shape[i]; }

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

        if(this->rank() == 0)
        {
            EXCEPTION_INIT(MemoryAccessError,"Shape is of rank 0!");
            EXCEPTION_THROW();
        }

        if(c.size() == 0)
        {
            EXCEPTION_INIT(MemoryAccessError,"Container of size 0!");
            EXCEPTION_THROW();
        }

        if(c.size() != rank())
        {
            std::stringstream ss;
            ss<<"Shape rank ("<<this->rank()<<") and container size (";
            ss<<c.size()<<") do not match!";
            EXCEPTION_INIT(ShapeMissmatchError,ss.str());
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
    template<typename CONT> void Shape::index(size_t offset,CONT &i) const
    {
        EXCEPTION_SETUP("template<typename CONT>" 
                        "void Shape::index(const size_t "
                        "&offset,CONT &i) const");

        if(this->rank() == 0)
        {
            EXCEPTION_INIT(MemoryAccessError,"Shape is of rank 0!");
            EXCEPTION_THROW();
        }

        if(i.size() == 0)
        {
            EXCEPTION_INIT(MemoryAccessError,"Container is of size 0!");
            EXCEPTION_THROW();
        }

        if(i.size() != rank())
        {
            std::stringstream ss;
            ss<<"Shape rank ("<<this->rank()<<") and container size (";
            ss<<i.size()<<") do not match!";
            EXCEPTION_INIT(ShapeMissmatchError,ss.str());
            EXCEPTION_THROW();
        }

        this->_index(offset,i);
    }

    //-------------------------------------------------------------------------
    template<typename CONT> void Shape::_index(size_t offset,CONT &i) const
    {
        EXCEPTION_SETUP("template<typename CONT> CONT Shape::_index(size_t "
                        "offset,CONT &i) const");

        if(offset>=this->size())
        {
            std::stringstream ss;
            ss<<"Offset ("<<offset<<") is larger than shape size ";
            ss<<"("<<this->size()<<")!";
            EXCEPTION_INIT(MemoryAccessError,ss.str());
            EXCEPTION_THROW();
        }

        size_t o,t;
        o = offset;
        for(size_t d = 0;d<rank();d++){
            t = o%this->_dimstrides[d];
            i[d] = (o-t)/this->_dimstrides[d];
            o = t;
        }
    }

    //-------------------------------------------------------------------------
    template<typename CONT> CONT Shape::index(size_t offset) const
    {
        CONT c(this->rank());

        this->_index(offset,c);
        return c;
    }

//end of namespace
}
}

#endif
