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
 * Created on: Jul 23,2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */


#pragma once

#include "Types.hpp"
#include "Iterator.hpp"
#include "ArrayViewSelector.hpp"
#include "ArrayView.hpp"
#include "InplaceArithmetics.hpp"
#include "Scalar.hpp"
#include "math/Add.hpp"
#include "math/Sub.hpp"
#include "math/Div.hpp"
#include "math/Mult.hpp"

namespace pni{
namespace core{
    
    /*! 
    \ingroup numeric_array_classes
    \brief numeric array facade

    This template is a facade for other array types adding numerical
    capabilities to the array. 
    \tparam ATYPE representation of a multidimensional array
    \tparam IPA inplace arithmetics type

    */
    template<typename ATYPE,template<typename> class IPA=InplaceArithmetics> 
        class NumArray
    {
        //need to do here a compiletime check if types are equal
        private:
            ATYPE _array; //!< array with data

            //----------------------private methods----------------------------
            /*! 
            \brief get array view

            Returns an instance of ArrayView if one of the indices is a Slice
            type. 
            \param view dummy parameter with the view type to select the proper
            private member function
            \param indices list of indices from which to construct the view
            \return array view object
            */
            template<typename ...ITYPES>
            NumArray<ArrayView<NumArray<ATYPE,IPA> > ,IPA>
            _get_data(NumArray<ArrayView<NumArray<ATYPE,IPA> >,IPA> &view,ITYPES ...indices)
            {
                typedef ArrayView<NumArray<ATYPE,IPA> > view_t;
                std::vector<Slice> slices{Slice(indices)...};
                ArraySelection s = ArraySelection::create(slices);

                view_t tmp(*this,s);

                return NumArray<view_t,IPA>(tmp);
            }

            //-----------------------------------------------------------------
            /*!
            \brief get element reference

            Returns a reference to the element determined by indices if this
            list does not contain an instance of Slice. 
            \param v dummy variable to select the proper function template
            \param indices list of index values determining the element to
            return
            \return reference to the element
            */
            template<typename ...ITYPES> typename ATYPE::value_type 
                &_get_data(typename ATYPE::value_type v,ITYPES ...indices)
            {
                return this->_array(indices...);
            }

            //-----------------------------------------------------------------
            /*!
            \brief get element value

            Return the value of the element determined by indices if this list
            does not contain an instance of Slice.
            \tparam ITYPES index types
            \param v dummy variable to select the proper function template
            \param indices list of indices identifiying the requrested element
            \return value determined by the indices
            */
            template<typename ...ITYPES> typename ATYPE::value_type 
                _get_data(typename ATYPE::value_type v,ITYPES ...indices) const
            {
                return this->_array(indices...);
            }

            //-----------------------------------------------------------------
            /*!
            \brief get array view 

            Get an array view whose shape is determined by the container c.
            \tparam CTYPE container template
            \tparam OTS template arguments to CTYPE
            \param view dummy variable to determine the function
            \param c container with view parameters
            \return array view
            */
            template<template<typename ...> class CTYPE,typename ...OTS>
            NumArray<ArrayView<NumArray<ATYPE,IPA> >,IPA>
            _get_data(NumArray<ArrayView<NumArray<ATYPE,IPA> >,IPA> &view,const CTYPE<OTS...> &c)
            {
                typedef ArrayView<NumArray<ATYPE,IPA> > view_t;

                ArraySelection s = ArraySelection::create(c);

                return NumArray<view_t>(view_t(*this,s));
            }

            //-----------------------------------------------------------------
            /*! 
            \brief get reference to element

            Returns a reference to an array element determined by the values in
            a container.
            \tparam CTYPE container template
            \tparam OTS template arguments of CTYPE
            \param v dummy argument to determine the function
            \param c container with indices
            \return element reference
            */
            template<template<typename ...> class CTYPE,typename ...OTS>
                typename ATYPE::value_type &
                _get_data(typename ATYPE::value_type v,const CTYPE<OTS...> &c)
            {
                return this->_data[this->_imap.offset(c)];
            }
        public:
            //====================public types=================================
            //! element type of the array
            typedef typename ATYPE::value_type value_type;
            //! type of the array
            typedef NumArray<ATYPE> array_type;
            //! type of array storage
            typedef ATYPE storage_type;
            //! type of the view
            typedef ArrayView<typename storage_type::view_type> view_type;
            //! shared smart pointer type to the numeric array
            typedef std::shared_ptr<array_type> shared_ptr;
            //! unique smart pointer type to the numeric array
            typedef std::unique_ptr<array_type> unique_ptr;

            //! iterator type
            typedef typename ATYPE::iterator iterator;
            //! const iterator type
            typedef typename ATYPE::const_iterator const_iterator;
            //! inplace arithmetic type
            typedef IPA<ATYPE> inplace_t;
            
            //=====================public members==============================
            //! type id of the element type
            static const TypeID type_id = TypeIDMap<value_type>::type_id;

            //======================constructors and destructor================
            //! default constructor
            NumArray():_array() {}

            //! construction from an ArrayView
            template<typename VIEWSTORAGE> 
                NumArray(const ArrayView<VIEWSTORAGE> &v):
                    _array(v)
            {}

            //-----------------------------------------------------------------
            //! construct from an arbitary array type
            NumArray(storage_type &&a):_array(std::move(a)) {}

            //-----------------------------------------------------------------
            //! implicit constructor
            template<typename ...ARGTYPES> NumArray(ARGTYPES ...args):
                _array(storage_type(args...))
            {}

            //! list constructor
            NumArray(const std::initializer_list<typename storage_type::value_type> &l):
                _array(storage_type(l))
            {}


            //-----------------------------------------------------------------
            //! copy constructor
            NumArray(const array_type &a):_array(a._array) {}

            //! move constructor
            NumArray(array_type &&a):_array(std::move(a._array)) {}

            //-----------------------------------------------------------------
            //! destructor
            ~NumArray() {} 

            //=================assignment operators===========================
            //! copy assignment
            array_type &operator=(const array_type &a)
            {
                if(this == &a) return *this;
                this->_array = a._array;
                return *this;
            }

            //-----------------------------------------------------------------
            //! move assignment
            array_type &operator=(array_type &&a)
            {
                if(this == &a) return *this;
                this->_array = std::move(a._array);
                return *this;
            }

            //-----------------------------------------------------------------
            //! assignment from a NumArray type
            template<typename AT> array_type &operator=(const NumArray<AT> &a)
            {
                std::copy(a.begin(),a.end(),this->begin());
                return *this;
            }

            //-----------------------------------------------------------------
            //! container assignment
            template<template<typename ...> class CTYPE,typename ...OTS>
            array_type &operator=(const CTYPE<OTS...> &c)
            {
                std::copy(c.begin(),c.end(),this->begin());
                return *this;
            }

            //====================inquery methods=============================
            /*!
            \brief return size

            Returns the number of element stored in the array. 
            \return number of elements
            */
            size_t size() const { return this->_array.size(); }

            //----------------------------------------------------------------
            /*!
            \brief return number of dimensions

            Return the number of dimensions of the arrya. 
            \return number of dimensions
            */
            size_t rank() const { return this->_array.rank(); }

            //-----------------------------------------------------------------
            /*!
            \brief get shape

            Return a container with the number of elements along each dimension
            of the array.
            \return container with shape
            */
            template<typename CTYPE> CTYPE shape() const 
            {
                return this->_array.template shape<CTYPE>();
            }

            //==================accessing data=================================
            /*!
            \brief get element at linear index i

            Return the value of the element at linear index i of the array. This
            operator does not perform any index checking. 
            \param i index of the element
            \return value of the element at linear index i
            */
            value_type operator[](size_t i) const { return this->_array[i]; }

            //-----------------------------------------------------------------
            /*!
            \brief get reference to element at i

            Return a reference to the element at linear index i. This operator
            performs no index checking.
            \param i linear index of the requested element
            \return reference to the requested element
            */
            value_type &operator[](size_t i) { return this->_array[i]; }

            //-----------------------------------------------------------------
            /*!
            \brief get reference to element

            Get a reference to the element at linear index i. This method
            performs index checking and throws an exception if i exceeds the
            total size of the array.
            \throws IndexError if i exceeds the total size of the array
            \param i linear index of the element
            \return reference to the element at linear index i
            */
            value_type &at(size_t i) { return this->_array.at(i); }

            //-----------------------------------------------------------------
            /*!
            \brief get value of element

            Return the value of an element at linear index i. 
            \throws IndexError if i exceeds the total size of the array
            \param i linear index of the element
            \return value at linear index i
            */
            value_type at(size_t i) const { return this->_array.at(i); }

            //-----------------------------------------------------------------
            /*!
            \brief insert element

            Set the value of element at linaer index i to v. 
            \throws IndexError if i exceeds the total size of the array
            \param i linear index where to insert the value
            \param v value to insert
            */
            void insert(size_t i,const value_type &v)
            {
                this->_array.insert(i,v);
            }

            //-----------------------------------------------------------------
            /*!
            \brief return storage reference

            Return a const. reference to the storage reference.
            \return reference to storage.
            */
            const ATYPE &storage() const
            {
                return this->_array;
            }

            //-----------------------------------------------------------------
            /*! 
            \brief return a selection or value

            Returns a non-const reference or a selection. The return value
            depends on the types of the arguments.
            \tparam ITYPES index types
            \param indices instances of ITYPES determining the multidimensional
            index
            \return array view or reference to the array value
            */
            template<typename ...ITYPES>
            typename ArrayViewSelector<array_type,ITYPES...>::reftype
            operator()(ITYPES ...indices)
            {
                typedef ArrayViewSelector<array_type,ITYPES...> sel;
                typedef typename sel::viewtype view_t;

                view_t r = view_t();

                return _get_data(r,indices...);
            }

            //-----------------------------------------------------------------
            /*!
            \brief retrieve data value

            Retrieve data using a multidimensional index passed as argument list
            to the method.
            \tparam ITYPES index types
            \param indices index list
            \return single value or array view
            */
            template<typename ...ITYPES>
            typename ArrayViewSelector<array_type,ITYPES...>::viewtype
            operator()(ITYPES ...indices) const
            {
                typedef ArrayViewSelector<array_type,ITYPES...> sel;
                typename sel::viewtype result = typename sel::viewtype();

                return _get_data(result,indices...);

                //return this->_array(indices...);
            }

            //-----------------------------------------------------------------
            /*!
            \brief access data 
            
            \tparam CTYPE container type
            \tparam OTS template arguments for the container
            \param c container with indices
            \return view or reference to a singel value
            */
            template<template<typename ...> class CTYPE,typename ...OTS>
            typename ArrayViewSelector<array_type,typename CTYPE<OTS...>::value_type>::reftype
            operator()(const CTYPE<OTS...> &c)
            {
                return this->_array(c);
            }

            //-----------------------------------------------------------------
            /*!
            \brief get data

            Returns an array view object or the value of the array element
            addressed by a multidimensional index stored in the container.
            \tparam CTYPE container template
            \tparam OTS template arguments
            \param c container with indices
            \return array view or element value
            */
            template<template<typename ...> class CTYPE,typename ...OTS>
            typename ArrayViewSelector<array_type,typename CTYPE<OTS...>::value_type>::viewtype
            operator()(const CTYPE<OTS...> &c) const
            {
                return this->_array(c);
            }

            //===================iterators=====================================
            //! get iterator to first element
            iterator begin() { return this->_array.begin(); }

            //-----------------------------------------------------------------
            //! get iterator to list +1 element
            iterator end() { return this->_array.end(); }

            //-----------------------------------------------------------------
            //! get const iterator to first element
            const_iterator begin() const { return this->_array.begin(); }

            //-----------------------------------------------------------------
            //! get const iterator to last + 1 element
            const_iterator end() const { return this->_array.end(); }

            //===================unary add=====================================
            /*! 
            \brief unary add with scalar

            Performs an inplace addition of each component of the array with the
            value of v.
            \param v scalar value to add
            \return reference to the modified array
            */
            array_type &operator+=(value_type v)
            {
                IPA<ATYPE>::add(this->_array,v);
                return *this;
            }

            //-----------------------------------------------------------------
            /*! 
            \brief unary add with other array

            Performs an element-wise addition of the arrays values with the
            elements off a. 
            \param a array to divide
            \return reference to the modified array
            */
            array_type &operator+=(const array_type &a)
            {
                IPA<ATYPE>::add(this->_array,a._array);
                return *this;
            }

            //-----------------------------------------------------------------
            /*! 
            \brief unary add with a container type

            Element wise unary addition of the array with the content of a
            general container template CTYPE.
            \tparam CTYPE container template
            \tparam OTS optional template arguments of CTYPE
            \param c instance of CTYPE
            \return reference to the modified array 
            */
            template<template<typename ...> class CTYPE,typename ...OTS>
                array_type &operator+=(const CTYPE<OTS...> &c)
            {
                IPA<ATYPE>::add(this->_array,c);
                return *this;
            }

            //==================unary subtraction==============================
            /*! 
            \brief unary subtraction with a scalar

            Inplace subtraction of every element of the array with v.
            \param v scalar value to subtract
            \return reference to the modified array
            */
            array_type &operator-=(value_type v)
            {
                IPA<ATYPE>::sub(this->_array,v);
                return *this;
            }

            //-----------------------------------------------------------------
            /*! 
            \brief unary subtraction with another array

            Inplace subtraction of every element of the array with the
            corresponding element of a.
            \param a instance of array on the rhs of the operator
            \return reference to the modified array
            */
            array_type &operator-=(const array_type &a)
            {
                IPA<ATYPE>::sub(this->_array,a._array);
                return *this;
            }

            //----------------------------------------------------------------
            /*! 
            \brief unary subtraction with a container

            Inplace subtraction of each element of the array with each element
            of the container of type CTYPE. 
            \tparam CTYPE container template
            \tparam OTS optional template arguments to CTYPE
            \param c container instance
            \return reference to the modified array
            */
            template<template<typename ...> class CTYPE,typename ...OTS>
                array_type &operator-=(const CTYPE<OTS...> &c)
            {
                IPA<ATYPE>::sub(this->_array,c);
                return *this;
            }

            //==================unary multiplication==========================
            /*! 
            \brief unary multiplication with a scalar

            Apply element-wise multiplication of each element of the array with
            v. 
            \param v value to multiply with
            \return reference to the modified array
            \*/
            array_type &operator*=(value_type v)
            {
                IPA<ATYPE>::mult(this->_array,v);
                return *this;
            }

            //-----------------------------------------------------------------
            /*! 
            \brief unary multiplication with an array

            Element wise multiplication of between this array and a on the rhs
            of the operator.
            \param a instance of array to multiply with
            \return reference to the modified instance of the array
            */
            array_type &operator*=(const array_type &a)
            {
                IPA<ATYPE>::mult(this->_array,a._array);
                return *this;
            }

            //----------------------------------------------------------------
            /*! 
            \brief unary multiplication with a general container

            \tparam CTYPE container template
            \tparam OTS template arguments to CTYPE
            \param c instance of CTYPE
            \return reference to the modified version of the array
            */
            template<template<typename ...> class CTYPE,typename ...OTS>
                array_type &operator*=(const CTYPE<OTS...> &c)
            {
                IPA<ATYPE>::mult(this->_array,c);
                return *this;
            }
            
            //==================unary division=================================
            /*! 
            \brief unary division with a scalar

            Performs a inplace division with a scalar.
            \param v scalar left-hand operator
            \return instance of the divided array
            */
            array_type &operator/=(value_type v)
            {
                IPA<ATYPE>::div(this->_array,v);
                return *this;
            }

            //-----------------------------------------------------------------
            /*! 
            \brief unary division with an array
          
            \param a array on the rhs of the operator
            \return reference to the modified version of the array
            */
            array_type &operator/=(const array_type &a)
            {
                IPA<ATYPE>::div(this->_array,a._array);
                return *this;
            }

            //----------------------------------------------------------------
            /*! 
            \brief unary division with a general container

            \tparam CTYPE container template
            \tparam OTS template arguments to CTYPE
            \param c instance of CTYPE
            \return reference to the modified version of the array
            */
            template<template<typename ...> class CTYPE,typename ...OTS>
                array_type &operator/=(const CTYPE<OTS...> &c)
            {
                IPA<ATYPE>::div(this->_array,c);
                return *this;
            }
            
    };

    //===================Multiplication operator================================
    /*!
    \ingroup numeric_array_classes
    \brief multiplication operator

    Expression template operator for the multiplication of two instances of 
    the NumArray template.For this operation to succeed the arrays must have
    equal shape.
    \code
    typedef std::vector<size_t> shape_t;
    shape_t shape{3,4,100};

    NumArray<DArray<Float32> > a(DArray<Float32>(shape));
    NumArray<DArray<Float32> > b(DArray<Float32>(shape));
    NumArray<DArray<Float32> > c(DArray<Float32>(shape));

    std::fill(a.begin(),a.end(),100);
    std::fill(b.begin(),b.end(),200);

    c = a * b;

    \endcode

    \throws ShapeMissmatchError if shapes do not match
    \tparam AT1 storage type of left operand
    \tparam AT2 storage type of right operand
    \param a left operand
    \param b right operand
    \return instance of NumArray with result
    */
    template<typename AT1,typename AT2>
    NumArray<Mult<NumArray<AT1>,NumArray<AT2> > >
    operator*(const NumArray<AT1> &a,const NumArray<AT2> &b)
    {
        typedef Mult<NumArray<AT1>,NumArray<AT2> > op_type;
        check_equal_shape(a,b,EXCEPTION_RECORD);

        return NumArray<op_type>(op_type(a,b));
    }

    //-------------------------------------------------------------------------
    /*! 
    \ingroup numeric_array_classes
    \brief multiplication operator

    Expression template operator for the multiplication of an instance of
    NumArray with a scalar.  
    \code
    typedef std::vector<size_t> shape_t;
    shape_t shape{3,4,100};

    NumArray<DArray<Float32> > a(DArray<Float32>(shape));
    NumArray<DArray<Float32> > c(DArray<Float32>(shape));
    Float32 b = 200;

    std::fill(a.begin(),a.end(),100);
    c = a * b;

    \endcode
    \tparam AT storage type of the NumArray instance
    \param a left operand (array type)
    \param b right operand (scalar)
    \return instance of NumArray with result
    */
    template<typename AT>
    NumArray<Mult<NumArray<AT>,Scalar<typename AT::value_type> > >
    operator*(const NumArray<AT> &a,typename AT::value_type const &b)
    {
        typedef NumArray<AT> atype;
        typedef Scalar<typename AT::value_type> stype;
        typedef Mult<atype,stype> op_type;
        return NumArray<op_type>(op_type(a,stype(b)));
    }

    //-------------------------------------------------------------------------
    /*! 
    \ingroup numeric_array_classes
    \brief multiplication operator

    Expression template operator for the multiplication of an instance of
    NumArray and a scalar.    
    \code
    typedef std::vector<size_t> shape_t;
    shape_t shape{3,4,100};

    NumArray<DArray<Float32> > a(DArray<Float32>(shape));
    NumArray<DArray<Float32> > c(DArray<Float32>(shape));
    Float32 b = 200;

    std::fill(a.begin(),a.end(),100);
    c = b * a;

    \endcode
    \tparam AT storage type for the NumArray instance
    \param a left operand (scalar value)
    \param b right operand (array type)
    \return NumArray instance representing the result
    */
    template<typename AT>
    NumArray<Mult<Scalar<typename AT::value_type>,NumArray<AT> > >
    operator*(typename AT::value_type const &a,const NumArray<AT> &b)
    {
        typedef NumArray<AT> atype;
        typedef Scalar<typename AT::value_type> stype;
        typedef Mult<stype,atype> op_type;
        return NumArray<op_type>(op_type(stype(a),b));
    }


    //======================binary addition operator===========================
    /*!
    \ingroup numeric_array_classes
    \brief addition operator 

    Addition operator between two instances of NumArray using expression
    templates to perform the operation.
    Both arrays must be of same shape.
    
    \code
    typedef std::vector<size_t> shape_t;
    shape_t shape{3,4,100};

    NumArray<DArray<Float32> > a(DArray<Float32>(shape));
    NumArray<DArray<Float32> > b(DArray<Float32>(shape));
    NumArray<DArray<Float32> > c(DArray<Float32>(shape));

    std::fill(a.begin(),a.end(),100);
    std::fill(b.begin(),b.end(),200);

    c = a + b;

    \endcode

    \throws ShapeMissmatchError if array shapes do not coincide
    \tparam AT1 storage type of the left NumArray
    \tparam AT2 storage type of the right NumArray
    \param a left operand
    \param b right operand
    \return instance of NumArray with an expression template as storage type
    */
    template<typename AT1,typename AT2>
    NumArray<Add<NumArray<AT1>,NumArray<AT2> > >
    operator+(const NumArray<AT1> &a,const NumArray<AT2> &b)
    {
        typedef Add<NumArray<AT1>,NumArray<AT2> > op_type;
        return NumArray<op_type>(op_type(a,b));
    }

    //-------------------------------------------------------------------------
    /*! 
    \ingroup numeric_array_classes
    \brief addition operator

    Addition operator between an instance of NumArray and a scalar value.
    \code
    typedef std::vector<size_t> shape_t;
    shape_t shape{3,4,100};

    NumArray<DArray<Float32> > a(DArray<Float32>(shape));
    NumArray<DArray<Float32> > c(DArray<Float32>(shape));
    Float32 b = 200;

    std::fill(a.begin(),a.end(),100);
    c = a + b;

    \endcode
    \tparam AT storage type of the NumArray on the left side
    \param a left operand (NumArray)
    \param b right operand (scalar)
    \return NumArray instance with an expression template storage type
    */
    template<typename AT>
    NumArray<Add<NumArray<AT>,Scalar<typename AT::value_type> > >
    operator+(const NumArray<AT> &a,typename AT::value_type const &b)
    {
        typedef NumArray<AT> atype;
        typedef Scalar<typename AT::value_type> stype;
        typedef Add<atype,stype> op_type;
        return NumArray<op_type>(op_type(a,stype(b)));
    }

    //-------------------------------------------------------------------------
    /*!
    \ingroup numeric_array_classes
    \brief addition operator

    Addition operator between an instance of NumArray and 
    \code
    typedef std::vector<size_t> shape_t;
    shape_t shape{3,4,100};

    NumArray<DArray<Float32> > a(DArray<Float32>(shape));
    NumArray<DArray<Float32> > c(DArray<Float32>(shape));
    Float32 b = 200;

    std::fill(a.begin(),a.end(),100);
    c = b + a;

    \endcode
    \tparam AT storage type of the right operand (NumArray)
    \param a scalar value
    \param b instance of NumArray
    \return instance of NumArray with an expression template
    */
    template<typename AT>
    NumArray<Add<Scalar<typename AT::value_type>,NumArray<AT> > >
    operator+(typename AT::value_type const &a,const NumArray<AT> &b)
    {
        typedef NumArray<AT> atype;
        typedef Scalar<typename AT::value_type> stype;
        typedef Add<stype,atype> op_type;
        return NumArray<op_type>(op_type(stype(a),b));
    }
    
    //=================binary division operator================================
    /*!
    \ingroup numeric_array_classes
    \brief binary division operator 

    Division operator between two instances of NumArray using expression
    templates to perform the operation.
    Both arrays must be of same shape.
    
    \code
    typedef std::vector<size_t> shape_t;
    shape_t shape{3,4,100};

    NumArray<DArray<Float32> > a(DArray<Float32>(shape));
    NumArray<DArray<Float32> > b(DArray<Float32>(shape));
    NumArray<DArray<Float32> > c(DArray<Float32>(shape));

    std::fill(a.begin(),a.end(),100);
    std::fill(b.begin(),b.end(),200);

    c = a / b;

    \endcode

    \throws ShapeMissmatchError if array shapes do not coincide
    \tparam AT1 storage type of the left NumArray
    \tparam AT2 storage type of the right NumArray
    \param a left operand
    \param b right operand
    \return instance of NumArray with an expression template as storage type
    */
    template<typename AT1,typename AT2>
    NumArray<Div<NumArray<AT1>,NumArray<AT2> > >
    operator/(const NumArray<AT1> &a,const NumArray<AT2> &b)
    {
        typedef Div<NumArray<AT1>,NumArray<AT2> > op_type;
        return NumArray<op_type>(op_type(a,b));
    }

    //-------------------------------------------------------------------------
    /*! 
    \ingroup numeric_array_classes
    \brief binary division operator

    Division operator between an instance of NumArray and a scalar value.
    \code
    typedef std::vector<size_t> shape_t;
    shape_t shape{3,4,100};

    NumArray<DArray<Float32> > a(DArray<Float32>(shape));
    NumArray<DArray<Float32> > c(DArray<Float32>(shape));
    Float32 b = 200;

    std::fill(a.begin(),a.end(),100);
    c = a / b;

    \endcode
    \tparam AT storage type of the NumArray on the left side
    \param a left operand (NumArray)
    \param b right operand (scalar)
    \return NumArray instance with an expression template storage type
    */
    template<typename AT>
    NumArray<Div<NumArray<AT>,Scalar<typename AT::value_type> > >
    operator/(const NumArray<AT> &a,typename AT::value_type const &b)
    {
        typedef NumArray<AT> atype;
        typedef Scalar<typename AT::value_type> stype;
        typedef Div<atype,stype> op_type;
        return NumArray<op_type>(op_type(a,stype(b)));
    }

    //-------------------------------------------------------------------------
    /*!
    \ingroup numeric_array_classes
    \brief binary division operator

    Division operator between an instance of NumArray and 
    \code
    typedef std::vector<size_t> shape_t;
    shape_t shape{3,4,100};

    NumArray<DArray<Float32> > a(DArray<Float32>(shape));
    NumArray<DArray<Float32> > c(DArray<Float32>(shape));
    Float32 b = 200;

    std::fill(a.begin(),a.end(),100);
    c = b / a;

    \endcode
    \tparam AT storage type of the right operand (NumArray)
    \param a scalar value
    \param b instance of NumArray
    \return instance of NumArray with an expression template
    */
    template<typename AT>
    NumArray<Div<Scalar<typename AT::value_type>,NumArray<AT> > >
    operator/(typename AT::value_type const &a,const NumArray<AT> &b)
    {
        typedef NumArray<AT> atype;
        typedef Scalar<typename AT::value_type> stype;
        typedef Div<stype,atype> op_type;
        return NumArray<op_type>(op_type(stype(a),b));
    }
   
    //======================binary subtraction operator========================
    /*!
    \ingroup numeric_array_classes
    \brief binary subtraction operator 

    Subtraction operator between two instances of NumArray using expression
    templates to perform the operation.
    Both arrays must be of same shape.
    
    \code
    typedef std::vector<size_t> shape_t;
    shape_t shape{3,4,100};

    NumArray<DArray<Float32> > a(DArray<Float32>(shape));
    NumArray<DArray<Float32> > b(DArray<Float32>(shape));
    NumArray<DArray<Float32> > c(DArray<Float32>(shape));

    std::fill(a.begin(),a.end(),100);
    std::fill(b.begin(),b.end(),200);

    c = a - b;

    \endcode

    \throws ShapeMissmatchError if array shapes do not coincide
    \tparam AT1 storage type of the left NumArray
    \tparam AT2 storage type of the right NumArray
    \param a left operand
    \param b right operand
    \return instance of NumArray with an expression template as storage type
    */
    template<typename AT1,typename AT2>
    NumArray<Sub<NumArray<AT1>,NumArray<AT2> > >
    operator-(const NumArray<AT1> &a,const NumArray<AT2> &b)
    {
        typedef Sub<NumArray<AT1>,NumArray<AT2> > op_type;
        return NumArray<op_type>(op_type(a,b));
    }

    //-------------------------------------------------------------------------
    /*! 
    \ingroup numeric_array_classes
    \brief binary subtraction operator

    Subtraction operator between an instance of NumArray and a scalar value.
    \code
    typedef std::vector<size_t> shape_t;
    shape_t shape{3,4,100};

    NumArray<DArray<Float32> > a(DArray<Float32>(shape));
    NumArray<DArray<Float32> > c(DArray<Float32>(shape));
    Float32 b = 200;

    std::fill(a.begin(),a.end(),100);
    c = a - b;

    \endcode
    \tparam AT storage type of the NumArray on the left side
    \param a left operand (NumArray)
    \param b right operand (scalar)
    \return NumArray instance with an expression template storage type
    */
    template<typename AT>
    NumArray<Sub<NumArray<AT>,Scalar<typename AT::value_type> > >
    operator-(const NumArray<AT> &a,typename AT::value_type const &b)
    {
        typedef NumArray<AT> atype;
        typedef Scalar<typename AT::value_type> stype;
        typedef Sub<atype,stype> op_type;
        return NumArray<op_type>(op_type(a,stype(b)));
    }

    //-------------------------------------------------------------------------
    /*!
    \ingroup numeric_array_classes
    \brief binary subtraction operator

    Subtraction operator between an instance of NumArray and 
    \code
    typedef std::vector<size_t> shape_t;
    shape_t shape{3,4,100};

    NumArray<DArray<Float32> > a(DArray<Float32>(shape));
    NumArray<DArray<Float32> > c(DArray<Float32>(shape));
    Float32 b = 200;

    std::fill(a.begin(),a.end(),100);
    c = b - a;

    \endcode
    \tparam AT storage type of the right operand (NumArray)
    \param a scalar value
    \param b instance of NumArray
    \return instance of NumArray with an expression template
    */
    template<typename AT>
    NumArray<Sub<Scalar<typename AT::value_type>,NumArray<AT> > >
    operator-(typename AT::value_type const &a,const NumArray<AT> &b)
    {
        typedef NumArray<AT> atype;
        typedef Scalar<typename AT::value_type> stype;
        typedef Sub<stype,atype> op_type;
        return NumArray<op_type>(op_type(stype(a),b));
    }


//end of namespace
}
}
