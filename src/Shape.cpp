/*
 * Implementation of class ArrayShape
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
 * along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
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

#include<iostream>
#include<string>

#include "Shape.hpp"
#include "Exceptions.hpp"

namespace pni{
namespace utils{

    //===========================private methods================================
    Buffer<size_t> Shape::_compute_dimstrides(const Buffer<size_t> &s)
    {
        Buffer<size_t> ds(s.size());

        //compute the dimension  strides
        for(ssize_t i=ds.size()-1;i>=0;i--){
            if(i==(ssize_t)ds.size()-1){
                ds[(size_t)i] = 1;
                continue;
            }
            ds[(size_t)i] = ds[(size_t)i+1]*s[(size_t)i+1];
        }
        return ds;
    }

    //-------------------------------------------------------------------------
    size_t Shape::_compute_size(const Buffer<size_t> &s){
        size_t size = 1;
        for(size_t i=0;i<s.size();i++) size *= s[i];
        return size;
    }

    //===================constructors and destructors===========================
    //implementation of the default constructor
    Shape::Shape():
        _shape(),
        _dimstrides(0),
        _size(0)
    { }

    //--------------------------------------------------------------------------
    //implementation of the constructor with initializer list
    Shape::Shape(const std::initializer_list<size_t> &list):
        _shape(list),
        _dimstrides(_compute_dimstrides(_shape)),
        _size(_compute_size(_shape))
    { }


    //--------------------------------------------------------------------------
    //implementation of the copy constructor
    Shape::Shape(const Shape &s):
        _shape(s._shape),
        _dimstrides(s._dimstrides),
        _size(s._size)
    { }

    //--------------------------------------------------------------------------
    //implementation of the move constructor
    Shape::Shape(Shape &&o):
        _shape(std::move(o._shape)),
        _dimstrides(std::move(o._dimstrides)),
        _size(std::move(o._size))
    {
        o._size = 0;
    }

    //--------------------------------------------------------------------------
    //implementation of the destructor
    Shape::~Shape(){
        _size = 0;
        _dimstrides.free();
        _shape.free();
    }

    //=============Implementation of the assignment operators===================
    //implementation of the copy assignment
    Shape &Shape::operator=(const Shape &a)
    {
        if(this == &a) return *this;

        _size = a._size;
        _dimstrides = a._dimstrides;
        _shape = a._shape;

        return *this;
    }

    //--------------------------------------------------------------------------
    //implementation of move assignment
    Shape &Shape::operator=(Shape &&o){

        if(this == &o) return *this;
        
        _size = o._size;
        o._size = 0;
        _dimstrides = std::move(o._dimstrides);
        _shape = std::move(o._shape);

        return *this;
    }
    //========methods to access and manipulate the rank of a shape==============

    size_t Shape::rank() const{
        return _shape.size();
    }

    //============methods to access and manipulate dimensions===================
    //implementation of set dimension
    void Shape::dim(const size_t &i,const size_t &d)
    {
        EXCEPTION_SETUP("void Shape::dim(const size_t &i,const size_t &d)");
        if(i>=rank())
        {
            std::stringstream ss;
            ss<<"Dimension index ("<<i<<") exceeds shape rank ("<<rank()<<")!";
            EXCEPTION_INIT(IndexError,ss.str());
            EXCEPTION_THROW();
        }

        _shape[i] = d;

        //like for setDimensions - strides and array size must be adopted
        _dimstrides = _compute_dimstrides(_shape);
        _size = _compute_size(_shape);
    }

    //-------------------------------------------------------------------------
    //implementation of the set dimension by initializer list
    void Shape::dim(const std::initializer_list<size_t> &list){
        EXCEPTION_SETUP("void Shape::dim(std::initializer_list<size_t> list)");

        if(list.size() != rank()){
            EXCEPTION_INIT(SizeMissmatchError,
                    "Initializer list size does not match rank of Shape!");
            EXCEPTION_THROW();
        }
        
        size_t cntr = 0;
#ifdef NOFOREACH
        for(auto iter = list.begin();iter!=list.end();iter++){
            const size_t &i = *iter;
#else
        for(const size_t &i: list){
#endif
            _shape[cntr] = i;
            cntr++;
        }
        _dimstrides = _compute_dimstrides(_shape);
        _size = _compute_size(_shape);
    }
    
    //--------------------------------------------------------------------------
    size_t Shape::offset(const std::initializer_list<size_t> &list) const
    {
        return offset(std::vector<size_t>(list));
    }

    //--------------------------------------------------------------------------
    //implementation of the set dimension method using a vector
    void Shape::dim(const std::vector<size_t> &vector){
        EXCEPTION_SETUP("void Shape::dim(std::vector<size_t> list)");

        if(vector.size() != rank()){
            EXCEPTION_INIT(SizeMissmatchError,
                    "Initializer list size does not match rank of Shape!");
            EXCEPTION_THROW();
        }
        
        size_t cntr = 0;
#ifdef NOFOREACH
        for(auto iter = vector.begin();iter!=vector.end();iter++){
            const size_t &i = *iter;
#else
        for(const size_t &i: vector){
#endif
            _shape[cntr] = i;
            cntr++;
        }
        _dimstrides = _compute_dimstrides(_shape);
        _size = _compute_size(_shape);
    }

    //--------------------------------------------------------------------------
    //implementation of get dimension
    size_t Shape::dim(const size_t &i) const{
        EXCEPTION_SETUP("size_t Shape::dim(const size_t &i) const");

        if(i>=rank())
        {
            std::stringstream ss;
            ss<<"Dimension index ("<<i<<") exceeds shape rank ("<<rank()<<")!";
            EXCEPTION_INIT(IndexError,ss.str());
            EXCEPTION_THROW();
        }

        return _shape[i];
    }

    //================Implementation of comparison operators===================
    //implementation of equality check
    bool operator==(const Shape &a,const Shape &b){
        //check the rank of the two shapes
        if(a.rank() != b.rank()) return false;
        
        //check the sizes of the two shapes
        if(a.size() != b.size()) return false;
        
        //check the shape of the two array shapes
        for(size_t i=0;i<a.rank();i++){
            if(a[i] != b[i]) return false;
        }
        
        return true;
    }

    //--------------------------------------------------------------------------
    //implementation if inequality checkc
    bool operator!=(const Shape &a,const Shape &b){
        if(a==b){
            return false;
        }

        return true;
    }

    //=====================Implementation of output operator====================
    std::ostream &operator<<(std::ostream &o,const Shape &s){
        o<<"Rank = "<<s.rank()<<":";
        o<<"( ";
        for(size_t i=0;i<s.rank();i++) o<<s[i]<<" ";
        o<<")";
        return o;
    }

    //================Implementation of access operators========================
    //implementation of read only access
    const size_t Shape::operator[](size_t i) const{
        return _shape[i];
    }

//end of namespace
}
}

